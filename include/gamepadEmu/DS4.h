#ifndef _DS4_H_
#define _DS4_H_

#include <NimBLEDevice.h>
#include <NimBLEHIDDevice.h>
#include <NimBLE2904.h>
#include <HIDKeyboardTypes.h>
#include <esp_log.h>

#define PS_INPUT_CRC32_SEED 0xA1
#define PS_OUTPUT_CRC32_SEED 0xA2
#define PS_FEATURE_CRC32_SEED 0xA3

#define DS4_INPUT_REPORT_MINIMAL_BT 0x01
#define DS4_INPUT_REPORT_MINIMAL_BT_SIZE 11
#define DS4_INPUT_REPORT_BT 0x11
#define DS4_INPUT_REPORT_BT_SIZE 79
#define DS4_OUTPUT_REPORT_BT 0x11
#define DS4_OUTPUT_REPORT_BT_SIZE 78

#define DS4_FEATURE_REPORT_CALIBRATION_BT 0x05
#define DS4_FEATURE_REPORT_CALIBRATION_BT_SIZE 41
#define DS4_FEATURE_REPORT_FIRMWARE_INFO 0xa3
#define DS4_FEATURE_REPORT_FIRMWARE_INFO_SIZE 49

#define DS4_INPUT_REPORT_COUNTER 0b11111100

/*
 * Status of a ds4 touch point contact.
 * Contact IDs, with highest bit set are 'inactive'
 * and any associated data is then invalid.
 */
#define DS4_TOUCH_POINT_INACTIVE BIT(7)

/* Status field of ds4 input report. */
#define DS4_STATUS0_BATTERY_CAPACITY 0b00001111
#define DS4_STATUS0_CABLE_STATE BIT(4)
/* Battery status within batery_status field. */
#define DS4_BATTERY_STATUS_FULL 11
/* Status1 bit2 contains dongle connection state:
 * 0 = connectd
 * 1 = disconnected
 */
#define DS4_STATUS1_DONGLE_STATE BIT(2)

/* The lower 6 bits of hw_control of the Bluetooth main output report
 * control the interval at which Dualshock 4 reports data:
 * 0x00 - 1ms
 * 0x01 - 1ms
 * 0x02 - 2ms
 * 0x3E - 62ms
 * 0x3F - disabled
 */
#define DS4_OUTPUT_HWCTL_BT_POLL_MASK 0x3F
/* Default to 4ms poll interval, which is same as USB (not adjustable). */
#define DS4_BT_DEFAULT_POLL_INTERVAL_MS 4
#define DS4_OUTPUT_HWCTL_CRC32 0x40
#define DS4_OUTPUT_HWCTL_HID 0x80

/* Flags for ds4 output report. */
#define DS4_OUTPUT_VALID_FLAG0_MOTOR 0x01
#define DS4_OUTPUT_VALID_FLAG0_LED 0x02
#define DS4_OUTPUT_VALID_FLAG0_LED_BLINK 0x04

/* ds4 hardware limits */
#define DS4_ACC_RES_PER_G 8192
#define DS4_ACC_RANGE (4 * DS_ACC_RES_PER_G)
#define DS4_GYRO_RES_PER_DEG_S 1024
#define DS4_GYRO_RANGE (2048 * DS_GYRO_RES_PER_DEG_S)
#define DS4_LIGHTBAR_MAX_BLINK 255 /* 255 centiseconds */
#define DS4_TOUCHPAD_WIDTH 1920
#define DS4_TOUCHPAD_HEIGHT 942

#define DS4_LOG_TAG "GPE_DS4"

typedef struct __packed ds4_touch_point
{
    uint8_t contact; // 7->active low, 6-0-> finger id
    uint8_t x_lo;
    uint8_t x_hi : 4, y_lo : 4;
    uint8_t y_hi;
};
static_assert(sizeof(struct ds4_touch_point) == 4);

typedef struct __packed ds4_touch_report
{
    uint8_t timestamp;                // packet conter
    struct ds4_touch_point points[2]; // coord for 2 fingers
};
static_assert(sizeof(struct ds4_touch_report) == 9);

typedef struct __packed ds4_input_report_touch
{
    uint8_t num_touch_reports;
    struct ds4_touch_report touch[4];
};
static_assert(sizeof(struct ds4_input_report_touch) == 37);

typedef struct __packed ds4_input_report_minimal
{
    uint8_t x, y;                                                                   // Left joystick x, y.  x=0x00->full left, 0xff->full right,  center=0x80.
    uint8_t rx, ry;                                                                 // Right joystick x, y. y=0x00->full up,   0xff->full down,   center=0x80.
    uint8_t d_pad : 4, squqre : 1, cross : 1, circle : 1, triangle : 1;             // buttons[0]: 7->△, 6->○, 5->X, 4->□. 0-3->Dpad, 0x0=N, 0x1=NE, 0x2=E, 0x3=SE, 0x4=S, 0x5=SW, 0x6=W, 0x7=NW
    uint8_t L1 : 1, R1 : 1, L2 : 1, R2 : 1, share : 1, options : 1, L3 : 1, R3 : 1; // buttons[1]: 7->R3, 6->L3, 5->OPT, 4->SHARE, 3->R2, 2->L2, 1->R1, 0->L1
    uint8_t ps_home : 1, t_pad : 1, packet_counter : 6;                             // buttons[2]: 7-2->Counter counts up by 1 per report, 1->Touch Pad, 0->PS
    uint8_t z, rz;                                                                  // Left, right trigger. 0x00->release, 0xff->full press
};
static_assert(sizeof(struct ds4_input_report_minimal) == 9);

typedef struct __packed ds4_input_report_motion
{
    /* Motion sensors */
    uint16_t sensor_timestamp;  // timestamp in 5.33us when report interval=1ms, increment of this value=188
    uint8_t sensor_temperature; // 0x00 - 0xff
    uint16_t gyro[3];           /* x, y, z */
    uint16_t accel[3];          /* x, y, z */
    uint8_t reserved2[5];       // keep 0x00.

    uint8_t power : 4, is_charging : 1, has_headphone : 1, has_mic : 1, has_accessory : 1; // status[0]: controller status. 7->accessory, 6->headphone, 5->mic, 4->usb cable, 3-0->battery level.
    uint8_t unknown_1 : 1, unknown_2 : 1, dongle_no_controller : 1, unknown_3 : 5;         // status[1]: related to USB wireless dongle. 7-3->keep 0, 2->whether connected to dongle, 1-0->keep 0.
    uint8_t reserved3;                                                                     // just keep 0x00.
};
static_assert(sizeof(struct ds4_input_report_motion) == 23);

class DS4
{
private:
    NimBLEServer *pServer;
    NimBLEHIDDevice *hid;
    NimBLESecurity *security;
    NimBLEAdvertising *advertising;

    bool hid_send_full_report = false;
    NimBLECharacteristic *input01;
    NimBLECharacteristic *input11;
    NimBLECharacteristic *output11;
    NimBLECharacteristic *feature05;
    NimBLECharacteristic *featureA3;

    uint8_t *send_buf;
    bool is_connected = false;

    class BT_DS4_cb : public NimBLEServerCallbacks
    {
    public:
        DS4 *gamepad;

        void onconnect(NimBLEServer *pS)
        {
            // ((BLE2902 *)gamepad->input01->getDescriptorByUUID(BLEUUID((uint16_t)0x2902)))->setNotifications(false);
        }

        void onDisconnect(BLEServer *pS)
        {
            gamepad->is_connected = false;
            if (gamepad->loopHandle)
                gamepad->stop();

            // ((BLE2902 *)gamepad->input01->getDescriptorByUUID(BLEUUID((uint16_t)0x2902)))->setNotifications(false);
            // ((BLE2902 *)gamepad->input11->getDescriptorByUUID(BLEUUID((uint16_t)0x2902)))->setNotifications(false);
        }

        // Request a pass key to be typed in on the host
        uint32_t onPassKeyRequest()
        {
            uint32_t passKey = 236502;
            ESP_LOGE(DS4_LOG_TAG, "The passkey request %d", passKey);
            vTaskDelay(25000);
            return passKey;
        }

        // The host sends a pass key to the ESP32 which needs to be displayed
        // and typed into the host PC
        void onPassKeyNotify(uint32_t pass_key)
        {
            ESP_LOGE(DS4_LOG_TAG, "The passkey Notify number:%d", pass_key);
        }

        // CB on a completed authentication (not depending on status)
        void onAuthenticationComplete(ble_gap_conn_desc *conn_desc)
        {
            // ESP_LOGI(DS4_LOG_TAG, "remote BD_ADDR:");
            // esp_log_buffer_hex(DS4_LOG_TAG, conn_desc->peer_id_addr, sizeof(conn_desc->peer_id_addr));
            // ESP_LOGI(DS4_LOG_TAG, "address type = %d", conn_desc.addr_type);

            gamepad->start();
            gamepad->is_connected = true;
            ESP_LOGI(DS4_LOG_TAG, "conn handle = %d", conn_desc->conn_handle);
        }

        // You need to confirm the given pin
        bool onConfirmPIN(uint32_t pin)
        {
            ESP_LOGE(DS4_LOG_TAG, "Confirm pin: %d", pin);
            return true;
        }
    };

    class BT_DS4_FEAT05_cb : public NimBLECharacteristicCallbacks
    {
    public:
        DS4 *gamepad;

        void onRead(NimBLECharacteristic *pCharacteristic)
        {
            gamepad->__hid_set_use_full_report(true);
        }
    };

    BT_DS4_cb *bt_cb;
    BT_DS4_FEAT05_cb *bt_feat05_cb;

    ds4_input_report_minimal input_minimal;
    ds4_input_report_motion input_motion;
    ds4_input_report_touch input_touch;

    TaskHandle_t loopHandle;
    // SemaphoreHandle_t inputMutex;
    friend void __ds4_loop(void *parameter);

    bool __d_up;
    bool __d_down;
    bool __d_left;
    bool __d_right;
    uint8_t __get_d_pad_dir();

    void __hid_input_report_init();
    void __hid_input_report_send();
    void __hid_input_minimal_report_prepare(uint8_t *buf);
    void __hid_input_full_report_prepare(uint8_t *buf);
    void __hid_set_use_full_report(bool use_full_report);

    static uint32_t ps_calc_crc32(uint8_t seed, uint8_t *data, size_t len);
    static uint32_t crc32_le(uint32_t crc, unsigned char const *p, size_t len);

public:
    DS4(BLEServer *server);
    ~DS4();

    void start();
    void stop();

    void sendReport();

    void square(bool pressed);
    void circle(bool pressed);
    void triangle(bool pressed);
    void cross(bool pressed);

    void up(bool pressed);
    void down(bool pressed);
    void left(bool pressed);
    void right(bool pressed);

    void L1(bool pressed);
    void R1(bool pressed);
    void L2(bool pressed);
    void R2(bool pressed);
    void L3(bool pressed);
    void R3(bool pressed);

    void opt(bool pressed);
    void share(bool pressed);
    void ps(bool pressed);
    void tPad(bool pressed);

    inline bool square() { return input_minimal.squqre; };
    inline bool circle() { return input_minimal.circle; };
    inline bool triangle() { return input_minimal.triangle; };
    inline bool cross() { return input_minimal.cross; };

    inline bool up() { return __d_up; };
    inline bool down() { return __d_down; };
    inline bool left() { return __d_left; };
    inline bool right() { return __d_right; };

    inline bool L1() { return input_minimal.L1; };
    inline bool R1() { return input_minimal.R1; };
    inline bool L2() { return input_minimal.L2; };
    inline bool R2() { return input_minimal.R2; };
    inline bool L3() { return input_minimal.L3; };
    inline bool R3() { return input_minimal.R3; };

    inline bool opt() { return input_minimal.options; };
    inline bool share() { return input_minimal.share; };
    inline bool ps() { return input_minimal.ps_home; };
    inline bool tPad() { return input_minimal.t_pad; };

    /*
    @brief Set left stick value.
    @param x: uint8_t, 0=full left, 127=center, 255=full right
    @param y: uint8_t, 0=full left, 127=center, 255=full right
    */
    void stickL(uint8_t x, uint8_t y);
    /*
    @brief Set right stick value.
    @param x: uint8_t, 0=full left, 127=center, 255=full right
    @param y: uint8_t, 0=full left, 127=center, 255=full right
    */
    void stickR(uint8_t x, uint8_t y);
    /*
    @brief Set left trigger value.
    @param z: uint8_t, 0=release 255=full press
    */
    void triggerL(uint8_t z);
    /*
    @brief Set right trigger value.
    @param z: uint8_t, 0=release 255=full press
    */
    void triggerR(uint8_t z);
};

#endif