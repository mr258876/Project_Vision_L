#include "conf.h"
#include "rtos_externs.h"

#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <Update.h>

#include <lvgl.h>
#include "lv_fs_fatfs.h"
#include "ui.h"

#include <ArduinoJson.h>
#include "LinkedList.h"
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
#include <esp_now.h>

#include "Hoyoverse.h"

// Freertos
#include "rtc_wdt.h"

////////////////////////
//
//  Typedef
//
////////////////////////
typedef enum
{
  VISION_HW_OK = 0,
  VISION_HW_SENSOR_ERR,
  VISION_HW_SD_ERR
} vision_hw_result_t;

typedef enum
{
  VISION_NO_UPDATE = 0,     // No update file
  VISION_UPDATE_BAD_FILE,   // not a updateable file
  VISION_UPDATE_START_FAIL, // Update start failed
  VISION_UPDATE_STARTED,    // Update started
  VISION_UPDATE_OK          // Update finished (probably never gonna to use)
} vision_update_result_t;

////////////////////////
//
//  Variables
//
////////////////////////
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
static LinkedList<String> filePaths;
uint8_t fileCount = 0;
uint8_t *vFileReadBuf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);

/* Mjpeg decoder & Image Buffers */
static MjpegClass mjpeg;
uint8_t *imgBufs[MEM_BUF_CHUNKS];
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

/* Hoyolab Client */
HoyoverseClient hyc;
Notedata nd;
const PROGMEM char *cookie = "HOYOLABCOOKIE";
const PROGMEM char *uid = "GENSHINID";
bool inResinScreen = false;

/* Booleans for whether the sensors enabled. */
bool useProx;
bool useAcc;
bool useAutoBrightness;

////////////////////////
//
//  Function Declartions
//
////////////////////////
bool checkSDFiles(String *errMsg);
vision_update_result_t updateFromSD(String *errMsg);
vision_hw_result_t checkHardware(String *errMsg);
void screenAdjustLoop(void *parameter);
void wifiConfigure();
void playVideo(void *parameter);
bool getDailyNote(Notedata *nd, String *errMsg);
void showDailyNote(Notedata *nd);
void resinCalcLoop(void *parameter);
void showDailyNoteLoop(void *parameter);
bool connectWiFi();
void cb_switchToVideoScreen();
void mjpegInit();
void leaveVideoScreen(void *parameter);
void leaveResinScreen(void *parameter);
void getDailyNoteFromResinScreen(void *parameter);

void onChangeVideo();
void onSingleClick();
void onDoubleClick();
void onMultiClick();

////////////////////////
//
//  Functions
//
////////////////////////
/* Display flushing */
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  if (xSemaphoreTake(LCDMutex, portMAX_DELAY) == pdTRUE)
  {
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixelsDMA((uint16_t *)&color_p->full, w * h);
    xSemaphoreGive(LCDMutex);
  }

  lv_disp_flush_ready(disp);
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

  // Init NVS
  prefs.begin("Project_Vision", false);

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
    disp_drv.full_refresh = 0;

    lv_disp_drv_register(&disp_drv);

    /* Initialize input device driver */
    // lv_indev_button_encoder_init();

    /* Initialize file system */
    lv_fs_fatfs_init();

    ui_init();

    LV_LOG_INFO("LVGL booted.");

    hyc.begin(cookie, uid);
  }
}

void mjpegInit()
{
  // Mjpeg初始化
  int fileNo = prefs.getUInt("currFileId", 0);
  if (!mjpeg.setup(filePaths.get(fileNo).c_str(), vFileReadBuf, imgBufs, IMG_BUF_CHUNKS, MEM_BUF_CHUNKS, true, screenWidth, screenHeight))
  {
    LV_LOG_ERROR("Mjpeg decoder init failed!");
  }

  // 划显存
  for (int i = 0; i < MEM_BUF_CHUNKS; ++i)
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
    ui_VideoImageConfs[i].data = (uint8_t *)imgBufs[i % MEM_BUF_CHUNKS];
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
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

////////////////////////
//
//  Hardware Checkup
//
////////////////////////
vision_hw_result_t checkHardware(String *errMsg)
{
  vision_hw_result_t hwErrDetected = VISION_HW_OK;
  // lv_label_set_text(ui_StartupLabel2, "检查距离传感器...");
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

  // lv_label_set_text(ui_StartupLabel2, "检查加速度计...");
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

  // lv_label_set_text(ui_StartupLabel2, "检查SD卡...");
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
  // lv_label_set_text(ui_StartupLabel2, "正在检查文件...");

  File f = SD_CLASS.open(PLAY_FILE_CONF_PATH);
  if (!f || f.isDirectory())
  {
    f.close();
    f = SD_CLASS.open(PLAY_FILE_CONF_PATH, FILE_WRITE, true);
    f.print(PLAY_FILE_DEFAULT_CONF);
    f.close();
    f = SD_CLASS.open(PLAY_FILE_CONF_PATH);
  }

  StaticJsonDocument<0> filter;
  filter.set(true);

  StaticJsonDocument<PLAY_FILE_CONF_BUFFER_SIZE> doc;

  DeserializationError error = deserializeJson(doc, f, DeserializationOption::Filter(filter));

  if (error)
  {
    errMsg->concat(error.c_str());
    LV_LOG_ERROR("deserializeJson() failed:%s", error.c_str());
    return true;
  }

  f.close();

  JsonArray files = doc["files"];

  filePaths.clear();
  for (const char *fp : files)
  {
    lv_fs_res_t _input_op_result;
    lv_fs_file_t _input;
    _input_op_result = lv_fs_open(&_input, fp, LV_FS_MODE_RD);
    if (_input_op_result == LV_FS_RES_OK)
    {
      filePaths.add(String(fp));
    }
    lv_fs_close(&_input);
  }

  doc.clear();

  fileCount = filePaths.size();
  if (fileCount < 1)
  {
    errMsg->concat("没有可播放的文件");
    return true;
  }

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

  xTaskCreatePinnedToCore(screenAdjustLoop, //任务函数
                          "screenAdjLoop",  //任务名称
                          2560,             //任务堆栈大小
                          NULL,             //任务参数
                          1,                //任务优先级
                          NULL,             //任务句柄
                          0);               //执行任务核心

  xTaskCreatePinnedToCore(resinCalcLoop,   //任务函数
                          "resinCalcLoop", //任务名称
                          1024,            //任务堆栈大小
                          NULL,            //任务参数
                          1,               //任务优先级
                          NULL,            //任务句柄
                          0);              //执行任务核心

  switchScreenDelay = 5000;

  xTaskCreatePinnedToCore(switchToVideoScreen,        //任务函数
                          "swToVideoScr",             //任务名称
                          4096,                       //任务堆栈大小
                          (void *)&switchScreenDelay, //任务参数
                          1,                          //任务优先级
                          NULL,                       //任务句柄
                          0);                         //执行任务核心
}

void hardwareSetup(void *parameter)
{
  startup_time = millis();
  vision_hw_result_t hwErr;
  vision_update_result_t updateStatus = VISION_NO_UPDATE;
  bool fileErr = false;
  String errMsg = "";

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, "正在检查硬件...");
    xSemaphoreGive(LVGLMutex);
  }
  hwErr = checkHardware(&errMsg);

  if (hwErr != VISION_HW_SD_ERR)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, "正在检查文件...");
      xSemaphoreGive(LVGLMutex);
    }
    updateStatus = updateFromSD(&errMsg);
    fileErr = checkSDFiles(&errMsg);
  }

  if (updateStatus == VISION_UPDATE_STARTED)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel1, "正在升级...");
      lv_label_set_text(ui_StartupLabel2, "请不要关闭电源\n或拔出SD卡");
      xSemaphoreGive(LVGLMutex);
    }

    vTaskDelete(NULL);
  }

  // 若检查到错误则停止启动
  if (hwErr || fileErr || updateStatus)
  {
    LV_LOG_ERROR("Hardware err Detected!!!");
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 发现如下问题,启动已终止:", errMsg.c_str(), {}, false);
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      xSemaphoreGive(LVGLMutex);
    }

    vTaskDelete(NULL);
  }

  // 检查网络配置
  if (prefs.getUInt("wifiConfigured", 0) == 0)
  {
    // 若无已保存网络则进入配网
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_obj_clean(ui_StartupScreen);

      lv_obj_t *ui_NetConfigureTitle = lv_label_create(ui_StartupScreen);

      lv_obj_set_width(ui_NetConfigureTitle, LV_SIZE_CONTENT);
      lv_obj_set_height(ui_NetConfigureTitle, LV_SIZE_CONTENT);

      lv_obj_set_x(ui_NetConfigureTitle, 25);
      lv_obj_set_y(ui_NetConfigureTitle, 35);

      lv_label_set_text(ui_NetConfigureTitle, "网络配置");

      lv_obj_set_style_text_color(ui_NetConfigureTitle, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_opa(ui_NetConfigureTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(ui_NetConfigureTitle, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

      lv_obj_t *ui_NetConfigureLabel = lv_label_create(ui_StartupScreen);

      lv_obj_set_width(ui_NetConfigureLabel, LV_SIZE_CONTENT);
      lv_obj_set_height(ui_NetConfigureLabel, LV_SIZE_CONTENT);

      lv_obj_set_x(ui_NetConfigureLabel, 30);
      lv_obj_set_y(ui_NetConfigureLabel, 85);

      lv_label_set_text(ui_NetConfigureLabel,
                        "神之眼的配置及部分功能\n依赖网络。\n\n使用微信\n扫描右侧\nQR码配\n置网络。");

      lv_obj_set_style_text_color(ui_NetConfigureLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_opa(ui_NetConfigureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(ui_NetConfigureLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

      lv_obj_t *qr = lv_qrcode_create(ui_StartupScreen, 100, lv_color_black(), lv_color_white());

      /*Set data*/
      const char *data = "http://iot.espressif.cn/configWXDeviceWiFi.html";
      lv_qrcode_update(qr, data, strlen(data));
      lv_obj_set_x(qr, 105);
      lv_obj_set_y(qr, 110);

      /*Add a border with bg_color*/
      lv_obj_set_style_border_color(qr, lv_color_white(), 0);
      lv_obj_set_style_border_width(qr, 5, 0);
      xSemaphoreGive(LVGLMutex);
    }

    wifiConfigure();

    vTaskDelete(NULL);
  }
  else
  {
    // 若有已保存网络则尝试获取树脂数据
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, "连接至网络...");
      xSemaphoreGive(LVGLMutex);
    }

    if (!getDailyNote(&nd, &errMsg))
    {
      lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 获取数据失败:", errMsg.c_str(), {}, false);
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      vTaskDelay(5000);
      lv_obj_del(mbox);
    }
  }

  pinMode(BUTTON_PIN, INPUT);
  pwrButton.attachClick(onSingleClick);
  pwrButton.attachDoubleClick(onDoubleClick);
  pwrButton.attachMultiClick(onMultiClick);

  cb_switchToVideoScreen();

  vTaskDelete(NULL);
}

void wifiConfigure()
{
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH_AIRKISS);

  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 1); // disable brownout detector

  LV_LOG_WARN("Waiting for Smartconfig...");

  while (!WiFi.smartConfigDone() || WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  LV_LOG_WARN("Smartconfig success!");

  prefs.putString("wifiSSID1", WiFi.SSID());
  prefs.putString("wifiPSWD1", WiFi.psk());
  prefs.putUInt("wifiConfigured", 1);
  WiFi.stopSmartConfig();

  esp_restart();
}

bool connectWiFi()
{
  WiFi.mode(WIFI_STA);
  int wifiCount = WiFi.scanNetworks(false, true, false, 300, 0, prefs.getString("wifiSSID1").c_str());
  WiFi.scanDelete();
  if (wifiCount < 1)
  {
    WiFi.mode(WIFI_OFF);
    return false;
  }

  WiFi.begin();
  unsigned long startConnect_ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(500);
    if (millis() - startConnect_ms > 10000)
    {
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      return false;
    }
  }
  return true;
}

void leaveVideoScreen(void *parameter)
{

  // 暂停解码
  if (xSemaphoreTake(MjpegMutex, portMAX_DELAY) == pdTRUE)
  {
    vTaskSuspend(playVideoHandle);
    mjpeg.pause();
    xSemaphoreGive(MjpegMutex);
  }

  // 切换屏幕
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_group_remove_all_objs(ui_group);
    ui_ResinScreen_screen_init();
    showDailyNote(&nd);
    inResinScreen = true;
    lv_scr_load_anim(ui_ResinScreen, LV_SCR_LOAD_ANIM_OUT_RIGHT, 500, 0, true);

    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelay(pdMS_TO_TICKS(500));

  for (int i = 0; i < MEM_BUF_CHUNKS; ++i)
  {
    free(imgBufs[i]);
  }

  // 创建显示数据刷新任务
  xTaskCreatePinnedToCore(showDailyNoteLoop,        //任务函数
                          "showDailyNoteLoop",      //任务名称
                          4096,                     //任务堆栈大小
                          NULL,                     //任务参数
                          1,                        //任务优先级
                          &showDailyNoteLoopHandle, //任务句柄
                          0);                       //执行任务核心

  vTaskDelete(NULL);
}

void leaveResinScreen(void *parameter)
{
  vTaskDelete(showDailyNoteLoopHandle);

  // 划显存
  for (int i = 0; i < MEM_BUF_CHUNKS; ++i)
  {
    imgBufs[i] = (uint8_t *)heap_caps_malloc(LCD_WIDTH * LCD_HEIGHT / IMG_BUF_CHUNKS * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!imgBufs[i])
    {
      LV_LOG_ERROR("Img buf #%d allocate failed!", i);
    }
  }

  // 设置显存地址
  for (int i = 0; i < IMG_BUF_CHUNKS; ++i)
  {
    ui_VideoImageConfs[i].data = (uint8_t *)imgBufs[i % MEM_BUF_CHUNKS];
  }

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_group_remove_all_objs(ui_group);
    ui_VideoScreen_screen_init();

    // 设置视频块参数
    for (int i = 0; i < IMG_BUF_CHUNKS; ++i)
    {
      lv_img_set_src(ui_VideoImages[i], &ui_VideoImageConfs[i]);
    }

    // 恢复解码器工作
    vTaskResume(playVideoHandle);
    mjpeg.resume();

    // 切换屏幕
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_NONE, 500, 0, true);

    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

void getDailyNoteFromResinScreen(void *parameter)
{
  String errMsg = "";
  bool updateRes = false;

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_NoteUpdateTimeLabel, "正在更新...");
    xSemaphoreGive(LVGLMutex);
  }

  updateRes = getDailyNote(&nd, &errMsg);

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    if (updateRes)
    {
      showDailyNote(&nd);
    }
    else
    {
      lv_obj_t *mbox = lv_msgbox_create(ui_ResinScreen, LV_SYMBOL_WARNING " 获取数据失败:", errMsg.c_str(), {}, false);
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      vTaskDelay(5000);
      lv_obj_del(mbox);
    }
    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

void showDailyNote(Notedata *nd)
{
  if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text_fmt(ui_NoteUpdateTimeLabel, "%d分钟前更新", (int)((time(NULL) - nd->_last_update_time) / 60));
    lv_label_set_text_fmt(ui_NoteResinLabel, "%d/%d", nd->resinRemain, nd->resinMax);
    lv_label_set_text_fmt(ui_NoteExpeditionsLabel, "%d/%d", nd->expeditionFinished, nd->expeditionOngoing);

    if (nd->homecoinMax < 1000)
    {
      lv_label_set_text_fmt(ui_NoteHomeCoinLabel, "%d/%d", nd->homecoinRemain, nd->homecoinMax);
    }
    else
    {
      lv_label_set_text_fmt(ui_NoteHomeCoinLabel, "%.1fK/%.1fK", (nd->homecoinRemain / 1000.0), (nd->homecoinMax / 1000.0));
    }

    if (nd->hasTransformer)
    {
      if (nd->transformerRecoverTime > 86400)
      {
        lv_label_set_text_fmt(ui_NoteTransformerLabel, "%d天", (int)(nd->transformerRecoverTime / 86400));
      }
      else if (nd->transformerRecoverTime > 3600)
      {
        lv_label_set_text_fmt(ui_NoteTransformerLabel, "%d小时", (int)(nd->transformerRecoverTime / 3600));
      }
      else if (nd->transformerRecoverTime > 60)
      {
        lv_label_set_text_fmt(ui_NoteTransformerLabel, "%d分钟", (int)(nd->transformerRecoverTime / 60));
      }
      else
      {
        lv_label_set_text(ui_NoteTransformerLabel, "已就绪");
      }
    }
    else
    {
      lv_label_set_text(ui_NoteTransformerLabel, "未解锁");
    }

    xSemaphoreGive(NoteDataMutex);
  }
}

void showDailyNoteLoop(void *parameter)
{
  while (1)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      showDailyNote(&nd);
      xSemaphoreGive(LVGLMutex);
    }
    vTaskDelay(20000);
  }
  vTaskDelete(NULL);
}

//*****************************/
//  Updating from SD
//
//*****************************/
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

  f.close();

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 更新失败", "请通过串口手动更新固件", {}, false);
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(mbox);
    xSemaphoreGive(LVGLMutex);
  }
  return VISION_UPDATE_STARTED;
}

////////////////////
//
//  LVGL Callbacks
//
////////////////////

void cb_hardwareSetup(lv_event_t *e)
{
  xTaskCreatePinnedToCore(hardwareSetup,   //任务函数
                          "hardwareSetup", //任务名称
                          8192,            //任务堆栈大小
                          NULL,            //任务参数
                          1,               //任务优先级
                          NULL,            //任务句柄
                          0);              //执行任务核心
}

void cb_leaveVideoScreen(lv_event_t *e)
{
  // 创建显存释放任务
  xTaskCreatePinnedToCore(leaveVideoScreen,   //任务函数
                          "leaveVideoScreen", //任务名称
                          4096,               //任务堆栈大小
                          NULL,               //任务参数
                          3,                  //任务优先级
                          NULL,               //任务句柄
                          0);                 //执行任务核心
}

void cb_changeVideo(lv_event_t *e)
{
  onChangeVideo();
}

void cb_leaveResinScreen(lv_event_t *e)
{
  xTaskCreatePinnedToCore(leaveResinScreen, //任务函数
                          "leaveResinScr",  //任务名称
                          4096,             //任务堆栈大小
                          NULL,             //任务参数
                          3,                //任务优先级
                          NULL,             //任务句柄
                          0);               //执行任务核心
}

void cb_getDailyNoteFromResinScreen(lv_event_t *e)
{
  xTaskCreatePinnedToCore(getDailyNoteFromResinScreen, //任务函数
                          "getDailyNoteFRS",           //任务名称
                          8192,                        //任务堆栈大小
                          NULL,                        //任务参数
                          1,                           //任务优先级
                          NULL,                        //任务句柄
                          0);                          //执行任务核心
}

////////////////////
//
//  Loop Functions
//
////////////////////
void loop()
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

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

//********************//
//  Video Play Loop
//
//********************//
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
    if (xSemaphoreTake(MjpegMutex, portMAX_DELAY) == pdTRUE)
    {
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
      xSemaphoreGive(MjpegMutex);
    }

    vfile_frame_end_ms = millis();
    if ((vfile_frame_end_ms - vfile_frame_start_ms) < (1000 / VIDEO_FPS))
    {
      vTaskDelay(pdMS_TO_TICKS(1000 / VIDEO_FPS + vfile_frame_start_ms - vfile_frame_end_ms));
    }
    // LV_LOG_WARN("Current FPS:%d", (int)(1000 / (vfile_frame_end_ms - vfile_frame_start_ms)));
  }
  vTaskDelete(NULL);
}

////////////////////////
//
//  Resin Functions
//
////////////////////////
bool getDailyNote(Notedata *nd, String *errMsg)
{
  if (!connectWiFi())
  {
    errMsg->concat("无法连接至网络\n");
    return false;
  }

  bool res = true;

  configTime(GMTOFFSET, DAYLIGHTOFFSET, "pool.ntp.org");

  struct tm timeinfo;
  unsigned long ntp_start_ms = millis();
  while (!getLocalTime(&timeinfo))
  {
    vTaskDelay(100);
    if (millis() - ntp_start_ms > 10000)
    {
      LV_LOG_ERROR("Failed to obtain time");
      res = false;
      errMsg->concat("同步时间失败\n");
      break;
    }
  }

  if (getLocalTime(&timeinfo))
  {
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
      if (!hyc.syncDailyNote(nd))
      {
        errMsg->concat("网络响应异常\n");
      }

      xSemaphoreGive(NoteDataMutex);
    }
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  return res;
}

void resinCalcLoop(void *parameter)
{
  while (1)
  {
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
      HoyoverseClient::updateDailyNote(&nd);

      xSemaphoreGive(NoteDataMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(20000));
  }
  vTaskDelete(NULL);
}

void onChangeVideo()
{
  int fileNo = prefs.getUInt("currFileId", 0);
  if (fileNo + 1 < fileCount)
  {
    fileNo += 1;
  }
  else
  {
    fileNo = 0;
  }

  if (xSemaphoreTake(MjpegReadMutex, portMAX_DELAY) == pdTRUE)
  {
    if (mjpeg.switchFile(filePaths.get(fileNo).c_str()))
    {
      vfile_ms = millis();
      prefs.putUInt("currFileId", fileNo);
    }
    xSemaphoreGive(MjpegReadMutex);
  }
}

////////////////////////
//
//  Button Callbacks
//
////////////////////////
bool inEditMode = false;
void onSingleClick()
{
  if (inEditMode)
  {
    lv_group_send_data(ui_group, LV_KEY_DOWN);
  }
  else
  {
    lv_group_send_data(ui_group, LV_KEY_NEXT);
  }
}

void onDoubleClick()
{
  lv_group_send_data(ui_group, LV_KEY_ENTER);

  if (inEditMode)
  {
    inEditMode = false;
    lv_obj_clear_state(lv_group_get_focused(ui_group), LV_STATE_PRESSED);
    return;
  }

  if (lv_obj_is_editable(lv_group_get_focused(ui_group)))
  {
    inEditMode = true;
    lv_obj_add_state(lv_group_get_focused(ui_group), LV_STATE_PRESSED);
    return;
  }
}

void onMultiClick()
{
  if (inEditMode)
  {
    lv_group_send_data(ui_group, LV_KEY_UP);
  }
  else
  {
    lv_group_send_data(ui_group, LV_KEY_PREV);
  }
}