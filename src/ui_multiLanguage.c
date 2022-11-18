#include "ui_multiLanguage.h"
#include "lvgl.h"

int curr_lang = 0;

/* Version */
const char *info_visionVersion = "L0.2.0-Indev22B181";

const char *zh_Hans[] = {
    "The Vision L",                                                         // 0 The Vision L
    "神之眼L",                                                              // 1 The Vision L (Localized)
    "正在启动",                                                             // 2 Booting up
    "请稍候...",                                                            // 3 Please wait...
    "正在检查硬件...",                                                      // 4 Checking hardware...
    "正在检查文件...",                                                      // 5 Checking files...
    "正在升级...",                                                          // 6 Updating...
    "请不要关闭电源\n或拔出SD卡",                                           // 7 Do not power off or take out SD card
    LV_SYMBOL_WARNING " 发现如下问题,启动已终止:",                          // 8 (space) Boot process was terminated due to following issues:
    "距离传感器初始化失败\n",                                               // 9 Proximity sensor initialize failed
    "加速度计初始化失败\n",                                                 // 10 Accel meter initialize filed
    "SD卡无法读取\n",                                                       // 11 Unable to read SD card
    "未检测到SD卡\n",                                                       // 12 SD card not detected
    "没有可播放的文件",                                                     // 13 No video or picture detected
    "连接至网络...",                                                        // 14 Connecting to network...
    LV_SYMBOL_WARNING " 获取数据失败:",                                     // 15 Failed to get data:
    "升级文件错误\n",                                                       // 16 Invalid update file
    "升级程序启动失败\n",                                                   // 17 Unable to start update process
    LV_SYMBOL_WARNING " 更新失败",                                          // 18 (space) Update Failed!
    "请通过串口手动更新固件",                                               // 19 Please update via serial manually
    "无法连接至网络\n",                                                     // 20 Unable to connect to network
    "同步时间失败\n",                                                       // 21 Unable to sync time
    "网络响应异常\n",                                                       // 22 Unexpected Hoyoverse response
    "未配置cookie\n",                                                       // 23 Cookie not configured
    "菜单",                                                                 // 24 Menu
    "神之眼",                                                               // 25 The Vision
    "树脂",                                                                 // 26 Daily Note
    "时钟",                                                                 // 27 Clock
    "设置",                                                                 // 28 Settings
    LV_SYMBOL_WIFI,                                                         // 29 Network
    LV_SYMBOL_LIST,                                                         // 30 Regular
    "i",                                                                    // 31 About
    "网络配置",                                                             // 32 Network configurations
    "使用微信扫描QR码\n进行网络配置",                                       // 33 Configure network through Wechat
    "http://iot.espressif.cn/configWXDeviceWiFi.html",                      // 34 Network configure QR code URL
    "神之眼的部分功能\n依赖网络。\n\n使用微信\n扫描右侧\nQR码配\n置网络。", // 35 Some functions of the Vision depend on network. Scan the QR code through Wechat to configure.
    "常规设置",                                                             // 36 Regular settings
    "自动亮度",                                                             // 37 Auto brightness
    "自动旋转",                                                             // 38 Auto rotate
    "关于",                                                                 // 39 About
    "Project Vision L",                                                     // 40 Project Vision L
    "@mr258876",                                                            // 41 @mr258876
    "如果您喜欢本项目，\n请在github上\nstar本项目！",                       // 42 If you like this project, please star on github!
    "%d分钟前更新",                                                         // 43 Updated %d min ago
    LV_SYMBOL_REFRESH "正在更新...",                                        // 44 Updating...
    "数据未初始化",                                                         // 45 Data uninitialized
    "%d天",                                                                 // 46 %d Day
    "%d小时",                                                               // 47 %d Hour
    "%d分钟",                                                               // 48 %d Min
    "已就绪",                                                               // 49 Ready
    "未解锁",                                                               // 50 Not unlocked
    "语言",                                                                 // 51 Language
    "ENG\n中文",                                                            // 52 Language List
    "错误1034：\n请使用米游社app查看体力后重试\n",                          // 53 Please use Hoyolab app to check your resin and then try again (ERR 1034)
    LV_SYMBOL_WARNING " 错误：",                                            // 54 Error
    "未同步时间\n",                                                         // 55 Time not synchronized
};

const char *en_US[] = {
    "",                                                                            // 0 The Vision L
    "The Vision L",                                                                // 1 The Vision L (Localized)
    "Booting up",                                                                  // 2 Booting up
    "Please wait...",                                                              // 3 Please wait...
    "Checking hardware...",                                                        // 4 Checking hardware...
    "Checking files...",                                                           // 5 Checking files...
    "Updating...",                                                                 // 6 Updating...
    "Do not power off\nor take out SD card",                                       // 7 Do not power off or take out SD card
    LV_SYMBOL_WARNING " Boot process terminated:",                                 // 8 (space) Boot process was terminated due to following issues:
    "Proximity sensor initialize failed\n",                                        // 9 Proximity sensor initialize failed
    "Accel meter initialize filed\n",                                              // 10 Accel meter initialize filed
    "Unable to read SD card\n",                                                    // 11 Unable to read SD card
    "SD card not detected\n",                                                      // 12 SD card not detected
    "No video or picture detected",                                                // 13 No video or picture detected
    "Connecting network...",                                                       // 14 Connecting network...
    LV_SYMBOL_WARNING " Failed to get data:",                                      // 15 Failed to get data:
    "Invalid update file\n",                                                       // 16 Invalid update file
    "Unable to start update process\n",                                            // 17 Unable to start update process
    LV_SYMBOL_WARNING " Update Failed!",                                           // 18 (space) Update Failed!
    "Please update via serial manually",                                           // 19 Please update via serial manually
    "Unable to connect to network\n",                                              // 20 Unable to connect to network
    "Unable to sync time\n",                                                       // 21 Unable to sync time
    "Abnormal network response\n",                                                 // 22 Unexpected Hoyoverse response
    "Cookie not configured\n",                                                     // 23 Cookie not configured
    "Menu",                                                                        // 24 Menu
    "Vision",                                                                      // 25 The Vision
    "Resin",                                                                       // 26 Daily Note (Resin)
    "Clock",                                                                       // 27 Clock
    "Settings",                                                                    // 28 Settings
    LV_SYMBOL_WIFI,                                                                // 29 Network
    LV_SYMBOL_LIST,                                                                // 30 Regular
    "i",                                                                           // 31 About
    "Network config",                                                              // 32 Network configurations
    "Configure network\nthrough Wechat:",                                          // 33 Configure network through Wechat
    "http://iot.espressif.cn/configWXDeviceWiFi.html",                             // 34 Network configure QR code URL
    "神之眼的部分功能\n依赖网络。\n\n使用微信\n扫描右侧\nQR码配\n置网络。",        // 35 Some functions of the Vision depend on network. Scan the QR code through Wechat to configure.
    "Regular settings",                                                            // 36 Regular settings
    "Auto brightness",                                                             // 37 Auto brightness
    "Auto rotate",                                                                 // 38 Auto rotate
    "About",                                                                       // 39 About
    "Project Vision L",                                                            // 40 Project Vision L
    "@mr258876",                                                                   // 41 @mr258876
    "If you like this\nproject, please\nstar on github!",                          // 42 If you like this project, please star on github!
    "Updated %d min ago",                                                          // 43 Updated %d min ago
    LV_SYMBOL_REFRESH "Updating...",                                               // 44 Updating...
    "Data uninitialized",                                                          // 45 Data uninitialized
    "%dDay",                                                                       // 46 %d Day
    "%dHour",                                                                      // 47 %d Hour
    "%dMin",                                                                       // 48 %d Min
    "Ready",                                                                       // 49 Ready
    "Not obtained",                                                                // 50 Not obtained
    "Language",                                                                    // 51 Language
    "ENG\n中文",                                                                   // 52 Language List
    "Error 1034:\nPlease use Hoyolab app\nto check resin,\nand then try again.\n", // 53 Please use Hoyolab app to check your resin and then try again (ERR 1034)
    LV_SYMBOL_WARNING " Error:",                                                   // 54 Error
    "Time not synchronized\n",                                                     // 55 Time not synchronized
};

const char **lang[] = {
    en_US,
    zh_Hans};