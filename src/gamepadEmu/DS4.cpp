#include "gamepadEmu/DS4.h"

const uint8_t ds4_bt_rdesc_default[] = {
    0x05, 0x01,       // Usage Page (Generic Desktop Ctrls)
    0x09, 0x05,       // Usage (Game Pad)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x01,       //   Report ID (1)
    0x09, 0x30,       //   Usage (X)
    0x09, 0x31,       //   Usage (Y)
    0x09, 0x32,       //   Usage (Z)
    0x09, 0x35,       //   Usage (Rz)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x04,       //   Report Count (4)
    0x81, 0x02,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x39,       //   Usage (Hat switch)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x07,       //   Logical Maximum (7)
    0x75, 0x04,       //   Report Size (4)
    0x95, 0x01,       //   Report Count (1)
    0x81, 0x42,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
    0x05, 0x09,       //   Usage Page (Button)
    0x19, 0x01,       //   Usage Minimum (0x01)
    0x29, 0x0E,       //   Usage Maximum (0x0E)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x01,       //   Logical Maximum (1)
    0x75, 0x01,       //   Report Size (1)
    0x95, 0x0E,       //   Report Count (14)
    0x81, 0x02,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x06,       //   Report Size (6)
    0x95, 0x01,       //   Report Count (1)
    0x81, 0x01,       //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,       //   Usage Page (Generic Desktop Ctrls)
    0x09, 0x33,       //   Usage (Rx)
    0x09, 0x34,       //   Usage (Ry)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x02,       //   Report Count (2)
    0x81, 0x02,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x04, 0xFF, //   Usage Page (Vendor Defined 0xFF04)
    0x85, 0x02,       //   Report ID (2)
    0x09, 0x24,       //   Usage (0x24)
    0x95, 0x24,       //   Report Count (36)
    0xB1, 0x02,       //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0xA3,       //   Report ID (163)
    0x09, 0x25,       //   Usage (0x25)
    0x95, 0x30,       //   Report Count (48)
    0xB1, 0x02,       //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x05,       //   Report ID (5)
    0x09, 0x26,       //   Usage (0x26)
    0x95, 0x28,       //   Report Count (40)
    0xB1, 0x02,       //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x06, 0x00, 0xFF, //   Usage Page (Vendor Defined 0xFF00)
    0x85, 0x11,       //   Report ID (17)
    0x09, 0x20,       //   Usage (0x20)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x4D,       //   Report Count (77)
    0x81, 0x02,       //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x21,       //   Usage (0x21)
    0x91, 0x02,       //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             // End Collection

    // 128 bytes
};

const uint8_t ds4_bt_ft05[] = {
    0xA3, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x5F, 0xE1, 0xF5

    // 42 bytes
};

const uint8_t ds4_bt_ftA3[] = {
    0xA3, 0xA3, 0x41, 0x75, 0x67, 0x20, 0x20, 0x33, 0x20, 0x32, 0x30, 0x31, 0x33, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x37, 0x3A, 0x30, 0x31, 0x3A, 0x31, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x31, 0x03, 0x00, 0x00, 0x00, 0x49, 0x00, 0x05, 0x00, 0x00, 0x80,
    0x03, 0x00

    // 50 bytes
};

void __ds4_loop(void *parameter)
{
  DS4 *gpe = (DS4 *)parameter;

  while (true)
  {
    // Send HID report
    gpe->__hid_input_report_send();
    vTaskDelay(20);
  }
  vTaskDelete(NULL);
}

DS4::DS4(BLEServer *pS)
{
  pServer = pS;
  hid = new NimBLEHIDDevice(pServer);

  send_buf = (uint8_t *)malloc(128);

  bt_cb = new BT_DS4_cb();
  bt_cb->gamepad = this;
  bt_feat05_cb = new BT_DS4_FEAT05_cb();
  bt_feat05_cb->gamepad = this;

  pServer->setCallbacks(bt_cb);

  // inputMutex = xSemaphoreCreateMutex();
  hid_send_full_report = false;

  input01 = hid->inputReport(0x01);
  input11 = hid->inputReport(0x11);
  output11 = hid->outputReport(0x11);
  feature05 = hid->featureReport(0x05);
  featureA3 = hid->featureReport(0xA3);

  feature05->setCallbacks(bt_feat05_cb);

  // hid->manufacturer()->setValue("Sony");

  // hid->pnp(0x10, 0x054c, 0x05c4, 0x0110);  // <-On PC it will be 0x4c05, 0xc405 due to big-endian
  hid->pnp(0x0002, 0x4c05, 0xc405, 0x0001);
  hid->hidInfo(0x00, 0x01);

//   security = new NimBLESecurity();
//   security->setAuthenticationMode(BLE_SM_PAIR_AUTHREQ_BOND);

  hid->reportMap((uint8_t *)ds4_bt_rdesc_default, sizeof(ds4_bt_rdesc_default));
  hid->startServices();

//   advertising = NimBLEDevice::getAdvertising();
//   advertising->setAppearance(HID_GAMEPAD);
//   advertising->addServiceUUID(hid->hidService()->getUUID());
//   advertising->setScanResponse(false);
//   advertising->start();
}

DS4::~DS4()
{
}

void DS4::start()
{
  feature05->setValue((uint8_t *)ds4_bt_ft05, sizeof(ds4_bt_ft05));
  featureA3->setValue((uint8_t *)ds4_bt_ftA3, sizeof(ds4_bt_ftA3));

  __hid_set_use_full_report(false);
  __hid_input_report_init();
  // xTaskCreatePinnedToCore(__ds4_loop, "__ds4_loop", 4096, this, 1, &this->loopHandle, 1);
  ESP_LOGI(DS4_LOG_TAG, "report start.");
}

void DS4::stop()
{
  // vTaskDelete(this->loopHandle);
  ESP_LOGI(DS4_LOG_TAG, "report stop.");
}

void DS4::sendReport()
{
  if (is_connected)
    __hid_input_report_send();
}

void DS4::__hid_input_report_init()
{
  memset(&input_minimal, 0, sizeof(ds4_input_report_minimal));
  memset(&input_motion, 0, sizeof(ds4_input_report_motion));
  memset(&input_touch, 0, sizeof(ds4_input_report_touch));
  input_motion.power = 9;
  input_motion.is_charging = 1;
  input_minimal.x = 0x80;
  input_minimal.y = 0x80;
  input_minimal.rx = 0x80;
  input_minimal.ry = 0x80;
}

void DS4::__hid_input_report_send()
{
  if (this->hid_send_full_report)
    {
      this->__hid_input_full_report_prepare(this->send_buf);
      this->input11->notify(this->send_buf, DS4_INPUT_REPORT_BT_SIZE);
    }
    else
    {
      this->__hid_input_minimal_report_prepare(this->send_buf);
      this->input01->notify(this->send_buf, DS4_INPUT_REPORT_MINIMAL_BT_SIZE);
    }
}

void DS4::__hid_set_use_full_report(bool use_full_report)
{
  // if (use_full_report)
  // {
  //   hid->reportMap((uint8_t *)ds4_bt_rdesc_full, sizeof(ds4_bt_rdesc_full));
  // }
  // else
  // {
  //   hid->reportMap((uint8_t *)ds4_bt_rdesc_default, sizeof(ds4_bt_rdesc_default));
  // }
  hid_send_full_report = use_full_report;
  ESP_LOGI(DS4_LOG_TAG, "hid_send_full_report set to: %d", hid_send_full_report);
}

void DS4::__hid_input_minimal_report_prepare(uint8_t *buf)
{
  /* update d pad */
  input_minimal.d_pad = __get_d_pad_dir();

  /* update report count */
  input_minimal.packet_counter += 1;

  memset(buf, 0, 128);
  buf[0] = 0xA1; // data payload header
  buf[1] = 0x01; // report ID
  memcpy(buf + 2, (uint8_t *)&input_minimal, sizeof(ds4_input_report_minimal));
}

void DS4::__hid_input_full_report_prepare(uint8_t *buf)
{
  /* update d pad */
  input_minimal.d_pad = __get_d_pad_dir();

  /* update report count */
  input_minimal.packet_counter += 1;

  input_motion.sensor_timestamp = (esp_timer_get_time() * 3 / 16);

  memset(buf, 0,128);
  buf[0] = 0xA1; // data payload header
  buf[1] = 0x11; // report ID
  buf[2] = 0xC0; // 7:enable HID, 6:enable CRC, 5-0:keep 0
  buf[3] = 0x00; // 7:enable audio, 6-0: keep 0
  memcpy(buf + 4, (uint8_t *)&input_minimal, sizeof(ds4_input_report_minimal));
  memcpy(buf + 13, (uint8_t *)&input_motion, sizeof(ds4_input_report_motion));
  memcpy(buf + 36, (uint8_t *)&input_touch, sizeof(ds4_input_report_touch));

  /* calculate crc32 */
//   uint32_t crc = crc32(buf, DS4_INPUT_REPORT_BT_SIZE - 4, 0xEDB88320, 0xA1);
//   memcpy(buf + (DS4_INPUT_REPORT_BT_SIZE - 4), &crc, sizeof(uint32_t));
}

void DS4::square(bool pressed)
{
  input_minimal.squqre = pressed;
}
void DS4::circle(bool pressed)
{
  input_minimal.circle = pressed;
}
void DS4::triangle(bool pressed)
{
  input_minimal.triangle = pressed;
}
void DS4::cross(bool pressed)
{
  input_minimal.cross = pressed;
}

uint8_t DS4::__get_d_pad_dir()
{
  bool igLR = (__d_left == __d_right);
  bool igUD = (__d_up == __d_down);
  if (igLR && igUD)
    return 8;
  else if (igLR)
    return __d_up ? 0 : 4;
  else if (igUD)
    return __d_left ? 6 : 2;
  else if (__d_up)
    return __d_left ? 7 : 1;
  else
    return __d_left ? 5 : 3;
}

void DS4::up(bool pressed)
{
  __d_up = pressed;
}
void DS4::down(bool pressed)
{
  __d_down = pressed;
}
void DS4::left(bool pressed)
{
  __d_left = pressed;
}
void DS4::right(bool pressed)
{
  __d_right = pressed;
}

void DS4::L1(bool pressed)
{
  input_minimal.L1 = pressed;
}
void DS4::R1(bool pressed)
{
  input_minimal.R1 = pressed;
}
void DS4::L2(bool pressed)
{
  input_minimal.L2 = pressed;
}
void DS4::R2(bool pressed)
{
  input_minimal.R2 = pressed;
}
void DS4::L3(bool pressed)
{
  input_minimal.L3 = pressed;
}
void DS4::R3(bool pressed)
{
  input_minimal.R3 = pressed;
}

void DS4::opt(bool pressed)
{
  input_minimal.options = pressed;
}
void DS4::share(bool pressed)
{
  input_minimal.share = pressed;
}
void DS4::ps(bool pressed)
{
  input_minimal.ps_home = pressed;
}
void DS4::tPad(bool pressed)
{
  input_minimal.t_pad = pressed;
}

void DS4::stickL(uint8_t x, uint8_t y)
{
  input_minimal.x = x;
  input_minimal.y = y;
}
void DS4::stickR(uint8_t x, uint8_t y)
{
  input_minimal.rx = x;
  input_minimal.ry = y;
}
void DS4::triggerL(uint8_t z)
{
  input_minimal.z = z;
}
void DS4::triggerR(uint8_t z)
{
  input_minimal.rz = z;
}