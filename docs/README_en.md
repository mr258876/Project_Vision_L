# The Vision L

🌐 | [中文](README.md) | **English**

Do virtual gods hand out electronic visions?

![image](/docs/images/perview.jpg)

## English

[中文](#中文)

This is the firmware of hardware project [璃月神之眼 Extended](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended).

These following hardwares are also supported:
- [璃月神之眼 Extended by mr258876](https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended)
- [神之眼挂件V1.2_ESP32U by 小渣渣](https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u)
- [璃月神之眼挂件 by 小渣渣](https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian) (Experimental, Untested)
- [神之眼挂件V1.1 by 小渣渣](https://oshwhub.com/Myzhazha/esp32_pico-d4-video) (Experimental, Untested)

## Development Process

- Picture/Video display ✅
- Setting menu ✅
- Multi-language support ✅
- Resin data syncing ✅
- Auto update✅
- Digital clock (with weather) ✅
- Management interface (with remote control & file management) ✅
- Recovery mode (to solve ROM shortage) ✅

Features planned for next major release:
- Bluetooth 🚧

## How to Use
### For version L0.1
- Short press twice on the distance sensor to switch elements (switch video)

### For version L0.2 or above
- Click power button to move cursor to next item
- Double-click power button to interact with a button item, or to interact with a buttonless screen (go back to menu)
- Triple-click power button to move cursor to previous item, or perform second interaction with a buttonless screen (switch element / update resin data manually / switch between digital clock & analog clock)

### HoyoLab cookie settings
- Open `Hoyolab.json` in SD card root directory, then set character id and Hoyolab cookie. Example shown as below:
```
{
    "uid": "100000000",
    "cookie": "PLACE YOUR COOKIE HERE 请在此处填写cookie值",
    "device_guid": ""
}
```
- `device_guid` is optional. It should be a random generated guid without dash line, 32 characters in total. The vision will generate one if left blank.

### Customizing element order (Playlist)
- Open `playFiles.json`in SD card root directory, then set the path and sequence of videos and pictures. The paths need include driver letter 'S'. Example shown as below:
```
{
    "files": [
        "S:/The_Vision_L/Pyro.mjpeg",
        "S:/水.mjpeg",
        "S:/风.jpg",
    ]
}
```
- You can put as many videos/pictures as you want in your playlist. You can even put multiple paths pointing to the same video/picture in your playlist to play repeatedly.
```
{
    "files": [
        "S:/水.mjpeg",
        "S:/风.jpg",
        "S:/风.jpg",
        "S:/水.mjpeg"
    ]
}
```
- Note: The format of pictures should be JPG/JPEG, with size 240px\*240px, file size less than 12KB; videos should be MJPEG, size 240px\*240px, less than 12 KB for each frame.
- Note: Extra commas are not acceptable in JSON syntax. When you are sure about the paths but still getting errors, check whether there is any extra comma at the end of the list.
- You could find the element videos at [mr258876/Genshin-Vision-Videos](https://github.com/mr258876/Genshin-Vision-Videos).

### Weather location configuration
- Open `Weather.json` in SD card root directory, set the city name, latitude & longitude, and weather service provider. Example shown as below:
```
{
    "city":"Shenzhen",
    "latitude":22.547,
    "longitude":114.085947,
    "provider":1
}
```
- Note: Only `city` entry is in string. Do not quote the other three values.
- Only `Openmeteo` avaliable as weather provider for now, please keep `provider` as `0`.
- You can check the coordinates of your location [here](https://open-meteo.com/en/docs/geocoding-api).

### 网络配置
⚠注意：请务必使用2.4G频率wifi进行配置，ESP32不支持5G频率wifi网络。

⚠注意：使用[EspTouch](#使用esptouch方式进行配置)方式进行配置时，仅能将神之眼连接至手机当前连接的wifi网络，无法将神之眼连接至移动热点。若需连接至移动热点，请使用[蓝牙方式](#使用蓝牙方式进行配置)进行配置。

#### 使用EspTouch方式进行配置
0. 请确认您的手机已经连接至无线网络。如果您的手机为安卓8.0系统或以上，由于系统权限策略限制，请在扫描二维码前开启设备位置信息功能，否则将无法正确配置wifi SSID。
   
1. 安装`EspTouch`应用程序
   
    | [安卓](https://github.com/EspressifApp/EsptouchForAndroid/releases/download/v2.3.2/esptouch-v2.3.2.apk) | [iOS](https://apps.apple.com/cn/app/espressif-esptouch/id1071176700) |

2. 在神之眼上进入设置菜单，选择`网络配置->配网模式`并进入，使设备进入配网状态。
   
3. 打开`EspTouch`应用，选择`ESP Touch`，随后按提示输入密码进行配置。

#### 使用蓝牙进行配置
TBD

## Flashing Firmware
### Flashing recompiled firmware
0. Setup serial connection with the vision. If using a development version board, just connect the vision with a Type-C wire, no further operations required; otherwise you need a USB-TTL dongle, and setup the connection as shown (e.g. connect using a CH341A downloader).</br>
![image](/docs/images/serial_conn.png)</br>
1. Move to [Espressif Systems](https://www.espressif.com.cn/en/support/download/other-tools) and download `ESP Download Tool (Flash Download Tool)`。</br>

2. Open ESP Download Tool，select `ESP32` for chip type, `development` for work mode.</br>
![image](/docs/images/flash_step1.png)</br>
3. Set the files, flash address, flash speed according to the figure below. Set serial port and download speed according to the actual situation.</br>
![image](/docs/images/flash_step2.png)</br>
4. Click `Download`. If not using a development version board, short press the EN key while holding the BOOT key. If the status always shows `sync`, repeat this step.</br>
![image](/docs/images/boot_en_button.png)</br>
5. Disconnect when the status shows `Finish`.</br>

### Updating Firmware
1. Rename `firmware.bin` to `update.bin` and place it in the SD card root directory.</br>
![image](/docs/images/update_rename.png)</br>
2. Insert SD card back in, the vision will start update automatically.</br>
![image](/docs/images/self_updating.png)</br>

### Known Issues
- Failure on wifi configuration through Wechat AirKiss protocol using SSID without password

### FAQ
#### Why do I get "Error 1034" when getting resin data?
- Affected by the risk control policy of Hoyoverse, the API directly returns error code 1034 in some cases. Current solution is to use Hoyolab app on your phone and check your resin, then the resin function on the vision should behave normally.
#### How to control the Vision through APIs?
- Please reference to [API Refernece Manual](apiReference.md) for more details about the management APIs.

### Compilation considerations
If you encounter errors during compilation, please:
- Confirm the referenced libraries are installed and library paths are configured correctly
- Remove SD/SDMMC libraries from Arduino Library Manager
- Remove the Adafruit Zero DMA library
Then try recompile. If problem still exists, bring up an issue for help.