# The Vision L

↓求个翻译


Do Virtual Gods Hand Out Electronic Visions?

## 版本 / Versions
### 稳定版 / Stable Release
- [L0.2.0](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.2.0)
### 测试版 / Beta Release
- None
### 开发版 / Indev Release
- None

## 支持库 / Referenced Libraries
- 以下库需要手动安装 / Following libraries require manual installation before compile
```
Adafruit BusIO  1.14.1
ArduinoJson     6.19.4
KXTJ3-1057      0.0.1
LovyanGFX       0.4.18
LVGL            8.3.3
OneButton       2.0.3
```
- 以下库通过MIT协议随项目分发 / Following libraries are distributed with this project under MIT license
```
APDS-9930       https://github.com/Depau/APDS9930
LinkedList      https://github.com/ivanseidel/LinkedList
```
- 部分代码参考了以下项目 / Some code refer to following projects
```
RGB565_video    https://github.com/moononournation/RGB565_video
esp32_audio     https://github.com/atomic14/esp32_audio
```

## 中文

该项目为硬件项目[璃月神之眼 Extended](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended)的对应固件。

固件目前支持以下几种硬件：
- [璃月神之眼 Extended by mr258876](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended)
- [神之眼挂件V1.2_ESP32U by 小渣渣](https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u) (实验性)
- [璃月神之眼挂件 by 小渣渣](https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian) (实验性，未测试)

## 开发进度

- 显示图片/视频✅
- 设置菜单✅
- 多语言支持✅
- 从米游社API获取树脂✅

下个大版本中计划的功能：
- 自动更新🚧
- 蓝牙🚧
- 恢复模式(应对ROM不足)🚧
- 综合信息界面(数字时钟/天气/树脂数据)🚧
- 管理界面(远程控制/文件管理)🚧

## 使用方法
### L0.1版本
- 短按两次距离传感器切换元素(切换视频)

### L0.2版本及以上
- 单击按钮将光标移至下一项
- 双击按钮与按钮进行交互，或与无按钮屏幕进行交互(回到菜单)
- 三击按钮将光标移至上一项，或与无按钮屏幕进行第二交互(切换元素/手动更新树脂数据)

### 米游社/HoyoLab cookie设置
- 打开SD卡根目录`Hoyolab.json`，并设定玩家id及米游社/Hoyolab cookie。文件格式参考如下：
```
{
    "uid": "100000000",
    "cookie": "PLACE YOUR COOKIE HERE 请在此处填写cookie值",
    "device_guid": ""
}
```
- `device_guid` 是选填项。其值应为不含短横线的guid，共32位字符。若留空，神之眼将会自动生成该值。
- 对于米游社，请打开米游社并登录，随后将以下代码粘贴至浏览器控制台中获取cookie：
```
let cookie_keys = ['_MHYUUID', 'ltoken', 'ltuid', 'cookie_token', 'account_id'];
var cookie = document.cookie;
var Str_Num = cookie.indexOf('_MHYUUID=');
var cookies = cookie.substring(Str_Num).split('; ');
for(var i = 0; i < cookies.length; i++){
    if(!cookie_keys.includes(cookies[i].split("=")[0])){
        cookies.splice(i--,1);
    }
}
cookie = '"cookie": "' + cookies.join('; ') + '"';
var ask = confirm('按"确认"复制cookie至剪贴板');
if (ask == true) {
  copy(cookie);
  msg = cookie
} else {
  msg = 'Cancel'
}
```

### 自定义元素顺序(自定义视频文件及顺序)
- 打开SD卡根目录`playFiles.json`，并设定视频/图片文件顺序及路径。路径需要以盘符'S'开头。文件格式参考如下：
```
{
    "files": [
        "S:/The_Vision_L/Pyro.mjpeg",
        "S:/水.mjpeg",
        "S:/风.jpg",
    ]
}
```
- 注意：图片格式需为JPG/JPEG，尺寸240\*240且小于12KB，视频格式需为MJPEG，尺寸240\*240且每帧小于12KB。

## 刷入固件
### 刷入预编译固件
0. 建立串口连接。若使用的主板为开发版，使用Type-C接口直接连接电脑即可，无需额外操作；若使用的主板为普通版，则需使用额外USB-串口转换器，并按下图建立有线连接(以CH341A下载器为例)。
![image](/images/serial_conn.png)
1. 移步[乐鑫科技网站]("https://www.espressif.com.cn/zh-hans/support/download/other-tools")并下载`ESP Download Tool(Flash下载工具)`。

2. 打开ESP Download Tool，芯片类型选择`ESP32`，工作模式选择`开发模式`。
![image](/images/flash_step1.png)
3. 按照下图设置刷入的文件、flash地址、flash速度，串口及下载速度按实际情况选择。
![image](/images/flash_step2.png)
4. 点击`下载`按钮。若使用的主板为普通版，还需在按住BOOT键的同时短按EN键。若下载状态一直显示等待上电同步，重复此步骤。
![image](/images/boot_en_button.png)
5. 当状态显示`完成`后，断开串口连接。

### 固件升级
1. 将firmware.bin重命名为update.bin，并放置于SD卡根目录下。
![image](images/update_rename.png)
2. 将SD卡插入神之眼，神之眼会自动开始升级过程。
![image](images/self_updating.png)

### 已知问题
- 使用微信AirKiss协议进行配网时，无法使用密码为空的SSID进行配网
- 在SD卡与屏幕共享SPI总线的设备上，通过SD卡更新固件时画面显示被冻结

### 常见问题解答
#### 为什么获取体力时会出现“错误1034”？
- 受米游社风控策略影响，部分情况米游社api会直接返回错误1034。目前的解决办法为在手机上使用米游社app查询体力并签到，随后神之眼上的树脂功能将恢复正常。

## English

This is the firmware of hardware project [璃月神之眼 Extended](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended).

These following hardwares are also supported:
- [璃月神之眼 Extended by mr258876](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended)
- [神之眼挂件V1.2_ESP32U by 小渣渣](https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u) (Experimental)
- [璃月神之眼挂件 by 小渣渣](https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian) (Experimental, Untested)

## Development Process

- Picture/Video display ✅
- Setting menu ✅
- Multi-language support ✅
- Resin data syncing ✅

Features planned for next major release:
- Automatic update🚧
- Bluetooth 🚧
- Recovery mode (to solve ROM shortage) 🚧
- Integrated information interface (includes digital clock & weather & resin data) 🚧
- Management interface (remote control & file management) 🚧

## How to Use
### For version L0.1
- Short press twice on the distance sensor to switch elements (switch video)

### For version L0.2 or above
- Click power button to move cursor to next item
- Double-click power button to interact with a button item, or to interact with a buttonless screen (go back to menu)
- Triple-click power button to move cursor to previous item, or perform second interaction with a buttonless screen (switch element / manually update resin data)

### HoyoLab cookie settings
- Open `Hoyolab.json` in the root directory of SD card, then set character id and Hoyolab cookie. Example shown as below:
```
{
    "uid": "100000000",
    "cookie": "PLACE YOUR COOKIE HERE 请在此处填写cookie值",
    "device_guid": ""
}
```
- `device_guid` is optional. It should be a random generated guid without dash line, 32 characters in total. The vision will generate one if left blank.

### Customizing element order (custom video file and order)
- Open `playFiles.json`in the root directory of SD card, then set the path and sequence of videos and pictures. The paths need include driver letter 'S'. Example shown as below:
```
{
    "files": [
        "S:/The_Vision_L/Pyro.mjpeg",
        "S:/水.mjpeg",
        "S:/风.jpg",
    ]
}
```
- Note: The format of pictures should be JPG/JPEG, with size 240px\*240px, file size less than 12KB; videos should be MJPEG, size 240px\*240px, less than 12 KB for each frame.

## Flashing Firmware
### Flashing recompiled firmware
0. Setup serial connection with the vision. If using a development version board, just connect the vision with a Type-C wire, no further operations required; otherwise you need a USB-TTL dongle, and setup the connection as shown (e.g. connect using a CH341A downloader).
![image](/images/serial_conn.png)
1. Move to [Espressif Systems](https://www.espressif.com.cn/en/support/download/other-tools) and download `ESP Download Tool (Flash Download Tool)`。

2. Open ESP Download Tool，select `ESP32` for chip type, `development` for work mode.
![image](/images/flash_step1.png)
3. Set the files, flash address, flash speed according to the figure below. Set serial port and download speed according to the actual situation.
![image](/images/flash_step2.png)
4. Click `Download`. If not using a development version board, short press the EN key while holding the BOOT key. If the status always shows `sync`, repeat this step.
![image](/images/boot_en_button.png)
5. Disconnect when the status shows `Finish`.

### Updating Firmware
1. Rename `firmware.bin` to `update.bin` and place it in the SD card root directory.
![image](images/update_rename.png)
2. Insert SD card back in, the vision will start update automatically.
![image](images/self_updating.png)

### Known Issues
- Failure on wifi configuration through Wechat AirKiss protocol using SSID without password
- Screen will get frozen when updating firmware through SD card on devices with SD card and LCD screen sharing same SPI bus

### FAQ
#### Why do I get "Error 1034" when getting resin data?
- Affected by the risk control policy of Hoyoverse, the API directly returns error code 1034 in some cases. Current solution is to use Hoyolab app on your phone and check your resin, then the resin function on the vision should behave normally.