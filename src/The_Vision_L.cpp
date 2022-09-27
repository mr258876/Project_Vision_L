#pragma GCC optimize("O3")

#include "conf.h"
#include "rtos_externs.h"

#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <Update.h>

#include <lvgl.h>
#include "lv_fs_fatfs.h"
#include "ui.h"

#include <Preferences.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#include "MjpegClass.h"

#if defined(_CONFIG_PROX_LIGHT_USE_APDS9960_)
#include "APDS9960.h"
#elif defined(_CONFIG_PROX_LIGHT_USE_APDS9930_)
#include "APDS9930.h"
#endif

#include <OneButton.h>
#include <kxtj3-1057.h>
#undef getName

#include <WiFi.h>

// Freertos
#include "rtc_wdt.h"

// LCD screen
class LGFX_PANEL : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7789 _panel_instance;

  lgfx::Bus_SPI _bus_instance;

public:
  LGFX_PANEL(void)
  {
    {                                    // バス制御の設定を行います。        // 设置总线
      auto cfg = _bus_instance.config(); // バス設定用の構造体を取得します。  // 获取总线设置结构体

      // SPIバスの設定  // SPI总线设置
      cfg.spi_host = VSPI_HOST; // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
      // ※ ESP-IDF版本更新后，若使用VSPI_HOST、HSPI_HOST报错，请使用SPI2_HOST、SPI3_HOST代替。
      cfg.spi_mode = 0;                  // SPI通信モードを設定 (0 ~ 3)   // SPI通信模式设置
      cfg.freq_write = 80000000;         // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)  // SPI写时钟频率(80MHz除以整数)
      cfg.freq_read = 80000000;          // 受信時のSPIクロック // SPI读时钟频率
      cfg.spi_3wire = true;              // 受信をMOSIピンで行う場合はtrueを設定  // 使用MOSI pin进行读操作时设定为true
      cfg.use_lock = true;               // トランザクションロックを使用する場合はtrueを設定  // 使用事务锁
      cfg.dma_channel = SPI_DMA_CH_AUTO; // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=2ch / SPI_DMA_CH_AUTO=自動設定) // 指定DMA通道
      // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
      // ※ ESP-IDF版本更新后，推荐使用SPI_DMA_CH_AUTO自动设置DMA通道。不推荐手动指定。
      cfg.pin_sclk = LCD_CLK;  // SPIのSCLKピン番号を設定   // SPI CLK引脚
      cfg.pin_mosi = LCD_MOSI; // SPIのMOSIピン番号を設定   // SPI MOSI引脚
      cfg.pin_miso = -1;       // SPIのMISOピン番号を設定 (-1 = disable)  // SPI MISO引脚(-1禁用)
      cfg.pin_dc = LCD_DC;     // SPIのD/Cピン番号を設定  (-1 = disable)  // SPI 数据/指令引脚(-1禁用)
                               // SDカードと共通のSPIバスを使う場合、MISOは省略せず必ず設定してください。
                               // 屏幕与SD卡共用一个SPI总线时，必须指定MISO引脚。

      _bus_instance.config(cfg);              // 設定値をバスに反映します。   // 应用总线设置
      _panel_instance.setBus(&_bus_instance); // バスをパネルにセットします。 // 为屏幕指定总线
    }

    {                                      // 表示パネル制御の設定を行います。    // 设置屏幕
      auto cfg = _panel_instance.config(); // 表示パネル設定用の構造体を取得します。  //获取屏幕设置构造体

      cfg.pin_cs = LCD_CS;   // CSが接続されているピン番号   (-1 = disable)   // 片选引脚
      cfg.pin_rst = LCD_RST; // RSTが接続されているピン番号  (-1 = disable)   // 重置引脚
      cfg.pin_busy = -1;     // BUSYが接続されているピン番号 (-1 = disable)   // busy信号引脚

      // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

      cfg.panel_width = 240;    // 実際に表示可能な幅   // 水平分辨率
      cfg.panel_height = 240;   // 実際に表示可能な高さ // 垂直分辨率
      cfg.offset_x = 0;         // パネルのX方向オフセット量  // X方向偏移量
      cfg.offset_y = 0;         // パネルのY方向オフセット量  // Y方向偏移量
      cfg.offset_rotation = 0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転) // 屏幕旋转方向(4-7为垂直翻转)
      cfg.dummy_read_pixel = 8; // ピクセル読出し前のダミーリードのビット数     // 读取显存前的dummy bit数
      cfg.dummy_read_bits = 1;  // ピクセル以外のデータ読出し前のダミーリードのビット数 // 读取其他数据前的dummy bit数
      cfg.readable = false;     // データ読出しが可能な場合 trueに設定    // 启用读操作
      cfg.invert = true;        // パネルの明暗が反転してしまう場合 trueに設定  // 反色
      cfg.rgb_order = false;    // パネルの赤と青が入れ替わってしまう場合 trueに設定  // 像素使用RGB顺序
      cfg.dlen_16bit = false;   // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定 // 一次写入16 bit数据
      cfg.bus_shared = false;   // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います) // 与SD卡共享总线

      _panel_instance.config(cfg); // 应用屏幕设置
    }

    setPanel(&_panel_instance); // 使用するパネルをセットします。 // 设置屏幕
  }
};
static LGFX_PANEL gfx;

/* LVGL Stuff */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
unsigned long startup_time;

/* Things of files */
const PROGMEM String fileNames[] = {
    "S:/The Vision L/video/Pyro.mjpeg",
    "S:/The Vision L/video/Hydro.mjpeg",
    "S:/The Vision L/video/Anemo.mjpeg",
    "S:/The Vision L/video/Electro.mjpeg",
    "S:/The Vision L/video/Dendro.mjpeg",
    "S:/The Vision L/video/Cryo.mjpeg",
    "S:/The Vision L/video/Geo.mjpeg"};
uint8_t *vFileReadBuf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);

/* Mjpeg decoder & Image Buffers */
static MjpegClass mjpeg;
uint8_t *imgBufs[IMG_BUF_CHUNKS];
bool mjpegInited = false;

/* Proximity sensor Object */
PROX_LIGHT_METER apds;
uint16_t r, g, b, c;
OneButton proxButton(PROX_INT, true);
OneButton pwrButton(BUTTON_PIN, true);

/* Accelmeter Object */
#define LOW_POWER
KXTJ3 acc(0x0E);
int rotation = 0;

/* NVS */
Preferences prefs;

/* Booleans for whether the sensors enabled. */
bool useProx;
bool useAcc;
bool useAutoBrightness;

bool checkSDFiles(String *errMsg);
void screenAdjustLoop(void *parameter);
void wifiConfigure(void *parameter);
void playVideo(void *parameter);
void LVGLloop(void *parameter);
void getDailyNote(void *parameter);
bool connectWiFi();
void cb_switchToVideoScreen();
void mjpegInit();

void onChangeVideo();

/* Display flushing */
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  if (xSemaphoreTake(LCDMutex, portMAX_DELAY) == pdTRUE)
  {
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.startWrite();
    gfx.writePixels((uint16_t *)&color_p->full, w * h);
    gfx.endWrite();
    xSemaphoreGive(LCDMutex);
  }

  lv_disp_flush_ready(disp);
}

/* Serial Debug Output */
void serialPrint(const char *str)
{
  Serial.print(str);
}

/* Setup Function */
void setup()
{
  // Disable watchdog write protect to feed manually
  rtc_wdt_protect_off();

  // SD card Pull-Ups
  pinMode(DAT0, INPUT_PULLUP);
  pinMode(DAT1, INPUT_PULLUP);
  pinMode(DAT2, INPUT_PULLUP);
  pinMode(DAT3, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(CMD, INPUT_PULLUP);

  // Enable Serial output
  Serial.begin(115200);

  // Disable Wifi
  WiFi.mode(WIFI_OFF);

  // Init NVS
  prefs.begin("Project_Vision", false);
  // Video file
  if (prefs.getUInt("currFileId", 255) > 6)
  {
    prefs.putUInt("currFileId", 0);
  }
  // Screen Rotation
  if (prefs.getUInt("currScreenDir", 255) > 3)
  {
    prefs.putUInt("currScreenDir", 0);
  }

// SD card init
#ifdef _CONFIG_SD_USE_SPI_
  SPIClass SDSPI = SPIClass(HSPI);
  SDSPI.begin(14, 2, 15, 13);
  SD.begin(13, SDSPI, 80000000);
#endif
#ifdef _CONFIG_SD_USE_SDMMC_1BIT_
  SD_MMC.begin("/sdcard", true);
#endif
#ifdef _CONFIG_SD_USE_SDMMC_4BIT_
  SD_MMC.begin();
#endif

  // Audio Output
  pinMode(AUDIO_OUT, INPUT_PULLDOWN);

  // Init Display
  gfx.init();
  gfx.setColorDepth(16);
  gfx.setSwapBytes(false);
  gfx.fillScreen(TFT_BLACK);

  ledcAttachPin(LCD_BL, 1);     // assign TFT_BL pin to channel 1
  ledcSetup(1, 12000, 8);       // 12 kHz PWM, 8-bit resolution
  ledcWrite(1, LCD_BRIGHTNESS); // brightness 0 - 255

  lv_init();
  lv_log_register_print_cb(serialPrint);

  screenWidth = gfx.width();
  screenHeight = gfx.height();

  if (!vFileReadBuf)
  {
    LV_LOG_ERROR("Video file buffer allocate failed!");
  }

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 32, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (!disp_draw_buf)
  {
    LV_LOG_ERROR("LVGL disp_draw_buf allocate failed!");
  }
  else
  {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 32);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 0;

    lv_disp_drv_register(&disp_drv);

    /* Initialize input device driver */
    // lv_indev_button_encoder_init();

    /* Initialize file system */
    lv_fs_fatfs_init();

    ui_init();

    xTaskCreatePinnedToCore(LVGLloop,        //任务函数
                            "LVGLloop",      //任务名称
                            4096,            //任务堆栈大小
                            NULL,            //任务参数
                            1,               //任务优先级
                            &LVGLloopHandle, //任务句柄
                            1);              //执行任务核心

    LV_LOG_INFO("LVGL booted.");
  }
}

void mjpegInit()
{
  // Mjpeg初始化
  int fileNo = prefs.getUInt("currFileId", 255);
  if (!mjpeg.setup(fileNames[fileNo].c_str(), vFileReadBuf, imgBufs, IMG_BUF_CHUNKS, true, screenWidth, screenHeight))
  {
    LV_LOG_ERROR("Mjpeg decoder init failed!");
  }

  // 划显存
  for (int i = 0; i < IMG_BUF_CHUNKS; ++i)
  {
    imgBufs[i] = (uint8_t *)heap_caps_malloc(LCD_WIDTH * LCD_HEIGHT / IMG_BUF_CHUNKS * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!imgBufs[i])
    {
      LV_LOG_ERROR("Img buf #%d allocate failed!", i);
    }
  }

  // 创建视频块参数
  for (int i = 0; i < IMG_BUF_CHUNKS; ++i)
  {
    ui_VideoImageConfs[i].header.always_zero = 0;
    ui_VideoImageConfs[i].header.w = screenWidth;
    ui_VideoImageConfs[i].header.h = screenHeight / IMG_BUF_CHUNKS;
    ui_VideoImageConfs[i].data_size = screenWidth * screenHeight / IMG_BUF_CHUNKS * LV_COLOR_SIZE / 8;
    ui_VideoImageConfs[i].header.cf = LV_IMG_CF_TRUE_COLOR;
    ui_VideoImageConfs[i].data = (uint8_t *)imgBufs[i % IMG_BUF_CHUNKS];
  }

  // Create task of video playing
  xTaskCreatePinnedToCore(playVideo,        //任务函数
                          "playVideo",      //任务名称
                          2048,             //任务堆栈大小
                          NULL,             //任务参数
                          2,                //任务优先级
                          &playVideoHandle, //任务句柄
                          0);               //执行任务核心
}

static int switchScreenDelay = 0;
void switchToVideoScreen(void *delayTime)
{
  // 等待延时
  vTaskDelay(pdMS_TO_TICKS(*((int *)delayTime)));
  ui_VideoScreen_screen_init();

  if (!mjpegInited)
  {
    mjpegInit();
    mjpegInited = true;
  }

  // 设置视频块参数
  for (int i = 0; i < IMG_BUF_CHUNKS; ++i)
  {
    lv_img_set_src(ui_VideoImages[i], &ui_VideoImageConfs[i]);
  }

  // 切换屏幕
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

typedef enum
{
  VISION_HW_OK = 0,
  VISION_HW_SENSOR_ERR,
  VISION_HW_SD_ERR
} vision_hw_result_t;

vision_hw_result_t checkHardware(String *errMsg)
{
  vision_hw_result_t hwErrDetected = VISION_HW_OK;
  lv_label_set_text(ui_StartupLabel2, "检查距离传感器...");
  if (apds.begin())
  {
    apds.enableColor(true);
    apds.enableProximity(true);
    apds.setProximityInterruptThreshold(0, PROX_THRS);
    apds.enableProximityInterrupt();
    pinMode(PROX_INT, INPUT_PULLUP);
    proxButton.attachDoubleClick(onChangeVideo);
    useProx = true;
    useAutoBrightness = true;
  }
  else
  {
    hwErrDetected = VISION_HW_SENSOR_ERR;
    errMsg->concat("距离传感器初始化失败\n");
    useProx = false;
    LV_LOG_ERROR("Prox sensor init failed!");
  }

  lv_label_set_text(ui_StartupLabel2, "检查加速度计...");
  if (acc.begin(ACC_SAMPLE_RATE, ACC_RANGE) == 0)
  {
    useAcc = true;
  }
  else
  {
    hwErrDetected = VISION_HW_SENSOR_ERR;
    errMsg->concat("加速度计初始化失败\n");
    useAcc = false;
    LV_LOG_ERROR("IMU init failed!");
  }

  lv_label_set_text(ui_StartupLabel2, "检查SD卡...");
  switch (SD_CLASS.cardType())
  {
  case CARD_MMC:
  case CARD_SD:
  case CARD_SDHC:
    break;
  case CARD_UNKNOWN:
    hwErrDetected = VISION_HW_SD_ERR;
    errMsg->concat("SD卡无法读取\n");
    LV_LOG_ERROR("Bad SD Card!");
    break;
  default:
    hwErrDetected = VISION_HW_SD_ERR;
    errMsg->concat("未检测到SD卡\n");
    LV_LOG_ERROR("No SD Card!");
  }

  return hwErrDetected;
}

bool checkSDFiles(String *errMsg)
{
  bool fileErrDetected = false;
  lv_label_set_text(ui_StartupLabel2, "正在检查文件...");

  lv_label_set_text(ui_StartupLabel2, "请稍候...");

  // LV_FONT_DECLARE(ui_font_HanyiWenhei16);
  // LV_FONT_DECLARE(ui_font_HanyiWenhei24);

  return fileErrDetected;
}

void cb_switchToVideoScreen()
{
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, "请稍候...");
    xSemaphoreGive(LVGLMutex);
  }

  xTaskCreatePinnedToCore(screenAdjustLoop,   //任务函数
                          "screenAdjustLoop", //任务名称
                          2048,               //任务堆栈大小
                          NULL,               //任务参数
                          1,                  //任务优先级
                          NULL,               //任务句柄
                          0);                 //执行任务核心

  switchScreenDelay = 2500 + startup_time - millis();
  if (switchScreenDelay < 0)
  {
    switchScreenDelay = 0;
  }

  xTaskCreatePinnedToCore(switchToVideoScreen,        //任务函数
                          "switchToVideoScreen",      //任务名称
                          4096,                       //任务堆栈大小
                          (void *)&switchScreenDelay, //任务参数
                          1,                          //任务优先级
                          NULL,                       //任务句柄
                          0);                         //执行任务核心
}

//*****************************/
//  Updating from SD
//
//*****************************/

typedef enum
{
  VISION_NO_UPDATE = 0,     // No update file
  VISION_UPDATE_BAD_FILE,   // not a updateable file
  VISION_UPDATE_START_FAIL, // Update start failed
  VISION_UPDATE_STARTED,    // Update started
  VISION_UPDATE_OK          // Update finished (probably never gonna to use)
} vision_update_result_t;

void performUpdateFromSD(void *parameter)
{
  File f = SD_CLASS.open(UPDATE_FILE_PATH);

  LV_LOG_INFO("Start update...");
  Update.writeStream(f);

  if (Update.end())
  {
    if (Update.isFinished())
    {
      LV_LOG_INFO("Update finished!");
      f.close();
      SD_CLASS.remove(UPDATE_FILE_PATH);
      esp_restart();
    }
  }

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY))
  {
    lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 更新失败", "请通过串口手动更新固件", {}, false);
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(mbox);
    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

vision_update_result_t updateFromSD(String *errMsg)
{
  File f = SD_CLASS.open(UPDATE_FILE_PATH);
  if (!f)
  {
    f.close();
    return VISION_NO_UPDATE;
  }

  if (f.isDirectory() || f.size() < 1024)
  {
    f.close();
    errMsg->concat("升级文件错误\n");
    return VISION_UPDATE_BAD_FILE;
  }

  size_t fSize = f.size();

  if (!Update.begin(fSize))
  {
    f.close();
    errMsg->concat("升级程序启动失败\n");
    return VISION_UPDATE_START_FAIL;
  }

  f.close();
  xTaskCreatePinnedToCore(performUpdateFromSD,   //任务函数
                          "performUpdateFromSD", //任务名称
                          8192,                  //任务堆栈大小
                          NULL,                  //任务参数
                          0,                     //任务优先级
                          NULL,                  //任务句柄
                          0);                    //执行任务核心
  return VISION_UPDATE_STARTED;
}

////////////////////
//
//  LVGL Callbacks
//
////////////////////

void hardwareSetup(lv_event_t *e)
{
  startup_time = millis();
  vision_hw_result_t hwErr;
  vision_update_result_t updateStatus = VISION_NO_UPDATE;
  bool fileErr = false;
  String errMsg = "";

  hwErr = checkHardware(&errMsg);

  if (hwErr != VISION_HW_SD_ERR)
  {
    updateStatus = updateFromSD(&errMsg);
    fileErr = checkSDFiles(&errMsg);
  }

  if (updateStatus == VISION_UPDATE_STARTED)
  {
    lv_label_set_text(ui_StartupLabel1, "正在升级...");
    lv_label_set_text(ui_StartupLabel2, "请不要关闭电源\n或拔出SD卡");
    return;
  }

  if (hwErr || fileErr || updateStatus)
  {
    // Serial.println("Err Detected!!!");
    lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 发现如下问题,启动已终止:", errMsg.c_str(), {}, false);
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_msgbox_start_auto_close(mbox, 10000);
    lv_obj_center(mbox);

    return;
  }

  cb_switchToVideoScreen();
}

////////////////////
//
//  Loop Function
//
////////////////////

void screenAdjustLoop(void *parameter)
{
  float accX = 0;
  float accY = 0;
  while (1)
  {
    pwrButton.tick();

    if (useProx)
    {
      proxButton.tick();
      if (!digitalRead(PROX_INT))
      {
        if (apds.readProximity() < PROX_THRS)
        {
          apds.clearInterrupt();
        }
      }

      if (useAutoBrightness)
      {
        apds.getColorData(&r, &g, &b, &c);
        int light = (c / 2) > 191 ? 191 : (c / 2);
        light += 64;
        ledcWrite(1, light);
      }
    }

    if (useAcc)
    {
      accX = acc.axisAccel(X);
      accY = acc.axisAccel(Y);
      int toRotate = rotation;
      if (accX >= ACC_THRES && accY >= ACC_THRES)
      {
        toRotate = 3;
      }
      else if (accX >= ACC_THRES && accY < -ACC_THRES)
      {
        toRotate = 2;
      }
      else if (accX < -ACC_THRES && accY >= ACC_THRES)
      {
        toRotate = 0;
      }
      else if (accX < -ACC_THRES && accY < -ACC_THRES)
      {
        toRotate = 1;
      }

      if (toRotate != rotation)
      {
        if (xSemaphoreTake(LCDMutex, portMAX_DELAY) == pdTRUE)
        {
          gfx.setRotation(toRotate);
          rotation = toRotate;
          lv_obj_invalidate(lv_scr_act());
          xSemaphoreGive(LCDMutex);
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(30));
  }
}

unsigned long vfile_ms;
unsigned long vfile_frame_start_ms;
unsigned long vfile_frame_end_ms;
void playVideo(void *parameter)
{
  LV_LOG_INFO("MJPEG video start");
  vfile_ms = millis();
  while (1)
  {
    vfile_frame_start_ms = millis();
    rtc_wdt_feed(); // Feed watchdog manually
    if (xSemaphoreTake(MjpegReadMutex, portMAX_DELAY) == pdTRUE)
    {
      if (mjpeg.readMjpegBuf())
      {
        xSemaphoreGive(MjpegReadMutex);
        mjpeg.drawJpg();
      }
      else
      {
        xSemaphoreGive(MjpegReadMutex);
        if (!mjpeg.reload())
        {
          LV_LOG_ERROR("Unable to reload video file!");
          break;
        }
        LV_LOG_WARN("Video actual play time:%ds", (int)((millis() - vfile_ms) / 1000));
        vfile_ms = millis();
      }
    }

    vfile_frame_end_ms = millis();
    if ((vfile_frame_end_ms - vfile_frame_start_ms) < (1000 / VIDEO_FPS))
    {
      vTaskDelay(pdMS_TO_TICKS(1000 / VIDEO_FPS + vfile_frame_start_ms - vfile_frame_end_ms));
    }
  }
  vTaskDelete(NULL);
}

uint8_t CPU_RunInfo[512];
unsigned long last_log_ms = millis();
void LVGLloop(void *parameter)
{
  while (1)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_timer_handler(); /* let the GUI do its work */
      xSemaphoreGive(LVGLMutex);
    }
  }
}

void loop()
{
  vTaskDelete(NULL);
}

void onChangeVideo()
{
  int fileNo = prefs.getUInt("currFileId", 255);
  if (fileNo >= 6)
  {
    fileNo = 0;
  }
  else
  {
    fileNo += 1;
  }

  if (xSemaphoreTake(MjpegReadMutex, portMAX_DELAY) == pdTRUE)
  {
    if (mjpeg.switchFile(fileNames[fileNo].c_str()))
    {
      prefs.putUInt("currFileId", fileNo);
    }
    xSemaphoreGive(MjpegReadMutex);
  }
}