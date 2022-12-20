#include "lvgl.h"
#include "ui/ui_multiLanguage.h"

int curr_lang = 0;

/* Version */
char info_appVersion[32];

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
    "没有可播放的文件",                                                     // 13 Playlist is empty
    "连接至网络...",                                                        // 14 Connecting to network...
    LV_SYMBOL_WARNING " 获取数据失败:",                                     // 15 Failed to get data:
    "升级文件错误\n",                                                       // 16 Invalid update file
    "升级程序启动失败\n",                                                   // 17 Unable to start update process
    LV_SYMBOL_WARNING " 更新失败",                                          // 18 (space) Update Failed!
    "请通过串口手动更新固件",                                               // 19 Please update via serial manually
    "无法连接至网络\n",                                                     // 20 Unable to connect to network
    "同步时间失败\n",                                                       // 21 Unable to sync time
    "米游社：响应异常",                                                     // 22 Unexpected Hoyoverse response
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
    "请在github上\nstar本项目！",                                           // 42 If you like this project, please star on github!
    "%d分钟前更新",                                                         // 43 Updated %d min ago
    LV_SYMBOL_REFRESH "正在更新...",                                        // 44 Updating...
    "数据未初始化",                                                         // 45 Data uninitialized
    "%d天",                                                                 // 46 %d Day
    "%d小时",                                                               // 47 %d Hour
    "%d分钟",                                                               // 48 %d Min
    "已就绪",                                                               // 49 Ready
    "未解锁",                                                               // 50 Not unlocked
    "语言",                                                                 // 51 Language
    "EN\n中文",                                                             // 52 Language List
    "米游社：请使用米游社app查看体力后重试(1034)\n",                        // 53 Please use Hoyolab app to check your resin and then try again (ERR 1034)
    LV_SYMBOL_WARNING " 错误",                                              // 54 Error
    "未同步时间\n",                                                         // 55 Time not synchronized
    "错误代码：",                                                           // 56 Error code:
    "SPIFFS分区初始化失败\n",                                               // 57 SPIFFS partition init failed
    "配网模式",                                                             // 58 Pairing mode
    "Wifi已关闭",                                                           // 59 Wifi disabled
    "已连接至%s",                                                           // 60 Connected to %s
    "正在尝试连接...",                                                      // 61 Trying to connect...
    "无可用无线网络",                                                       // 62 No Wifi avaliable
    "已断开连接",                                                           // 63 Wifi connect failed
    "IP地址：",                                                             // 64 IP address
    "MAC地址：",                                                            // 65 MAC address
    "硬件版本：%d",                                                         // 66 HW version:
    "请检查SD卡，\n然后重试。",                                             // 67 Please check SD card, and retry.
    LV_SYMBOL_HOME,                                                         // 68 Vision utility icon
    "神之眼实用程序",                                                       // 69 The Vision Utility
    "启用实用程序",                                                         // 70 Eneble utility
    "实用程序正在启动...",                                                  // 71 Utility booting...
    "错误：\n未连接到无线网络，\n实用程序无法启动。",                       // 72 Error: Utility is unavaliable without network.
    "实用程序未启用。",                                                     // 73 Utility disabled.
    "实用程序正在关闭...",                                                  // 74 Utility stoping...
    "周日",                                                                 // 75 Sun(day)
    "周一",                                                                 // 76 Mon(day)
    "周二",                                                                 // 77 Tue(sday)
    "周三",                                                                 // 78 Wed(nesday)
    "周四",                                                                 // 79 Thu(rsday)
    "周五",                                                                 // 80 Fri(day)
    "周六",                                                                 // 81 Sat(urday)
    "%d年\n%d月%d日",                                                       // 82 Date format string
    "一月",                                                                 // 83 Jan(naury)
    "二月",                                                                 // 84 Feb(ruary)
    "三月",                                                                 // 85 Mar(ch)
    "四月",                                                                 // 86 Apr(il)
    "五月",                                                                 // 87 May
    "六月",                                                                 // 88 Jun(e)
    "七月",                                                                 // 89 Jul(y)
    "八月",                                                                 // 90 Aug(ust)
    "九月",                                                                 // 91 May
    "十月",                                                                 // 92 Jun(e)
    "十一月",                                                               // 93 Jul(y)
    "十二月",                                                               // 94 Aug(ust)
    "正在对时...",                                                          // 95 Obtaining time...
    "查询树脂...",                                                          // 96 Querying Resin...
    "查询天气...",                                                          // 97 Querying Weather...
    "正在下载文件...",                                                      // 98 Downloading Files...
    "系统文件缺失，部分功能不可用\n",                                       // 99 Sys file missing, some features disabled.
    "关键性文件缺失，请参阅帮助文档\n",                                     // 100 Critial file missing, see help document.
    "播放列表配置错误，请参阅帮助文档\n",                                   // 101 Playlist config wrong, see help document.
    "配置文件错误，请参阅帮助文档\n",                                       // 102 Errors in config file, see help document.
    "天气：未配置城市\n",                                                   // 103 Weather: City not configured
    "天气：内存不足",                                                       // 104 Weather: Out of memory
    "天气：HTTP请求失败",                                                   // 105 Weather: HTTP request failed
    "天气：HTTP读取失败",                                                   // 106 Weather: HTTP read failed
    "天气：JSON解析失败",                                                   // 107 Weather: JSON parsing failed
    "天气：响应异常",                                                       // 108 Weather: Unexpected response
    "请检查播放列表，\n然后重试。",                                         // 109 Please check playlist, and retry.
};

const char *en_US[] = {
    "",                                                                             // 0 The Vision L
    "The Vision L",                                                                 // 1 The Vision L (Localized)
    "Booting up",                                                                   // 2 Booting up
    "Please wait...",                                                               // 3 Please wait...
    "Checking hardware...",                                                         // 4 Checking hardware...
    "Checking files...",                                                            // 5 Checking files...
    "Updating...",                                                                  // 6 Updating...
    "Do not power off\nor take out SD card",                                        // 7 Do not power off or take out SD card
    LV_SYMBOL_WARNING " Boot process terminated:",                                  // 8 (space) Boot process was terminated due to following issues:
    "Proximity sensor initialize failed\n",                                         // 9 Proximity sensor initialize failed
    "Accel meter initialize filed\n",                                               // 10 Accel meter initialize filed
    "Unable to read SD card\n",                                                     // 11 Unable to read SD card
    "SD card not detected\n",                                                       // 12 SD card not detected
    "Playlist is empty",                                                            // 13 Playlist is empty
    "Connecting network...",                                                        // 14 Connecting network...
    LV_SYMBOL_WARNING " Failed to get data:",                                       // 15 Failed to get data:
    "Invalid update file\n",                                                        // 16 Invalid update file
    "Unable to start update process\n",                                             // 17 Unable to start update process
    LV_SYMBOL_WARNING " Update Failed!",                                            // 18 (space) Update Failed!
    "Please update via serial manually",                                            // 19 Please update via serial manually
    "Unable to connect to network\n",                                               // 20 Unable to connect to network
    "Unable to sync time\n",                                                        // 21 Unable to sync time
    "Hoyolab: Unexpected response",                                                 // 22 Unexpected Hoyoverse response
    "Cookie not configured\n",                                                      // 23 Cookie not configured
    "Menu",                                                                         // 24 Menu
    "Vision",                                                                       // 25 The Vision
    "Resin",                                                                        // 26 Daily Note (Resin)
    "Clock",                                                                        // 27 Clock
    "Settings",                                                                     // 28 Settings
    LV_SYMBOL_WIFI,                                                                 // 29 Network
    LV_SYMBOL_LIST,                                                                 // 30 Regular
    "i",                                                                            // 31 About
    "Network config",                                                               // 32 Network configurations
    "Configure network\nthrough ESP-TOUCH App.",                                    // 33 Configure network through Wechat
    "https://www.espressif.com.cn/en/products/software/esp-touch/resources",        // 34 Network configure QR code URL
    "Please configure network\nthrough ESP-TOUCH App.",                             // 35 Some functions of the Vision depend on network. Scan the QR code through Wechat to configure.
    "Regular settings",                                                             // 36 Regular settings
    "Auto brightness",                                                              // 37 Auto brightness
    "Auto rotate",                                                                  // 38 Auto rotate
    "About",                                                                        // 39 About
    "Project Vision L",                                                             // 40 Project Vision L
    "@mr258876",                                                                    // 41 @mr258876
    "Please star this\nproject on github!",                                         // 42 If you like this project, please star on github!
    "Updated %d min ago",                                                           // 43 Updated %d min ago
    LV_SYMBOL_REFRESH "Updating...",                                                // 44 Updating...
    "Data uninitialized",                                                           // 45 Data uninitialized
    "%dDay",                                                                        // 46 %d Day
    "%dHour",                                                                       // 47 %d Hour
    "%dMin",                                                                        // 48 %d Min
    "Ready",                                                                        // 49 Ready
    "Not obtained",                                                                 // 50 Not obtained
    "Language",                                                                     // 51 Language
    "EN\n中文",                                                                     // 52 Language List
    "Hoyolab: Please use Hoyolab app to check resin, and then try again (1034).\n", // 53 Please use Hoyolab app to check your resin and then try again (ERR 1034)
    LV_SYMBOL_WARNING " Error",                                                     // 54 Error
    "Time not synchronized\n",                                                      // 55 Time not synchronized
    "Error code:",                                                                  // 56 Error code:
    "SPIFFS partition init failed\n",                                               // 57 SPIFFS partition init failed
    "Pairing mode",                                                                 // 58 Pairing mode
    "Wifi disabled",                                                                // 59 Wifi disabled
    "Connected to %s",                                                              // 60 Connected to %s
    "Connecting...",                                                                // 61 Connecting...
    "No Wifi avaliable",                                                            // 62 No Wifi avaliable
    "Wifi disconnected",                                                            // 63 Wifi disconnected
    "IP address:",                                                                  // 64 IP address:
    "MAC address:",                                                                 // 65 MAC address:
    "HW version: %d",                                                               // 66 HW version
    "Please\ncheck\nSD card,\nand retry.",                                          // 67 Please check SD card, and retry.
    LV_SYMBOL_HOME,                                                                 // 68 Vision utility icon
    "The Vision Utility",                                                           // 69 The Vision Utility
    "Enable Utility",                                                               // 70 Eneble utility
    "Starting utility...",                                                          // 71 Utility booting...
    "Error:\nUtility is\nunavaliable\nwithout network.",                            // 72 Error: Utility is unavaliable without network.
    "Utility disabled.",                                                            // 73 Utility disabled.
    "Stoping utility...",                                                           // 74 Utility disabled.
    "Mon",                                                                          // 75 Mon(day)
    "Tue",                                                                          // 76 Tue(sday)
    "Wed",                                                                          // 77 Wed(nesday)
    "Thu",                                                                          // 78 Thu(rsday)
    "Fri",                                                                          // 79 Fri(day)
    "Sat",                                                                          // 80 Sat(urday)
    "Sun",                                                                          // 81 Sun(day)
    "%s %d,\n%d",                                                                   // 82 Date format string
    "Jan",                                                                          // 83 Jan(naury)
    "Feb",                                                                          // 84 Feb(ruary)
    "Mar",                                                                          // 85 Mar(ch)
    "Apr",                                                                          // 86 Apr(il)
    "May",                                                                          // 87 May
    "Jun",                                                                          // 88 Jun(e)
    "Jul",                                                                          // 89 Jul(y)
    "Aug",                                                                          // 90 Aug(ust)
    "Sep",                                                                          // 91 Sep(tember)
    "Oct",                                                                          // 92 Oct(ober)
    "Nov",                                                                          // 93 Nov(ember)
    "Dec",                                                                          // 94 Dec(ember)
    "Obtaining time...",                                                            // 95 Obtaining time...
    "Querying Resin...",                                                            // 96 Querying Resin...
    "Querying Weather...",                                                          // 97 Querying Weather...
    "Downloading Files...",                                                         // 98 Downloading Files...
    "Sys file missing, some features disabled.\n",                                  // 99 Sys file missing, some function disabled.
    "Critial file missing, see help document.\n",                                   // 100 Critial file missing, see help document.
    "Playlist config wrong, see help document.\n",                                  // 101 Playlist config wrong, see help document.
    "Errors in config file, see help document.\n",                                  // 102 Errors in config file, see help document.
    "Weather: City not configured\n",                                               // 103 Weather: City not configured
    "Weather: Out of memory\n",                                                     // 104 Weather: Out of memory
    "Weather: HTTP request failed\n",                                               // 105 Weather: HTTP request failed
    "Weather: HTTP read failed\n",                                                  // 106 Weather: HTTP read failed
    "Weather: JSON parsing failed\n",                                               // 107 Weather: JSON parsing failed
    "Weather: Unexpected response",                                                 // 108 Weather: Unexpected response
    "Please\ncheck\nplaylist,\nand retry.",                                         // 109 Please check playlist, and retry.
};

const char **lang[] = {
    en_US,
    zh_Hans};