# The Vision L

↓求个翻译


Do Virtual Gods Hand Out Electronic Visions?

## 版本 / Versions
### 稳定版 / Stable Release
- [L0.1.1](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.1.1)
### 测试版 / Beta Release
- [L0.2.0-Beta1](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.2.0-Beta1)
### 开发版 / Indev Release
- [L0.2.0-Indev22A292](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.2.0-Indev22A292)

## 支持库 / Referenced Libraries
```
Adafruit BusIO  1.13.2
ArduinoJson     6.19.4
KXTJ3-1057      0.0.1
LovyanGFX       0.4.18
LVGL            8.3.2
OneButton       2.0.3
APDS-9930       https://github.com/Depau/APDS9930
LinkedList      https://github.com/ivanseidel/LinkedList
RGB565_video    https://github.com/moononournation/RGB565_video
```

## 中文

该项目为硬件项目[璃月神之眼 Extended]("https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended")的对应固件。

固件目前支持以下几种硬件：
- [璃月神之眼 Extended by mr258876]("https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended")
- [神之眼挂件V1.2_ESP32U by 小渣渣](https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u)
- [璃月神之眼挂件 by 小渣渣](https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian) (未测试)

## 开发进度

- 显示图片/视频✅
- 设置菜单/管理界面🔲
- 多语言支持✅
- 从米游社API获取树脂✅

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
    "cookie": "PLACE YOUR COOKIE HERE 请在此处填写cookie值"
}
```
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
1. 移步[乐鑫科技网站]("https://www.espressif.com.cn/zh-hans/support/download/other-tools")并下载ESP Download Tool(Flash下载工具)。

2. 打开ESP Download Tool，芯片类型选择ESP32，工作模式选择开发模式。
![image](/images/flash_step1.png)
3. 按照下图设置刷入的文件、flash地址、flash速度，串口及下载速度按实际情况选择。
![image](/images/flash_step2.png)
4. 点击下载按钮。若使用的主板为普通版，还需在按住BOOT键的同时短按EN键。若下载状态一直显示等待上电同步，重复此步骤。
![image](/images/boot_en_button.png)
5. 当状态显示完成后，断开串口连接。

### 固件升级
1. 将firmware.bin重命名为update.bin，并放置于SD卡根目录下。
![image](images/update_rename.png)
2. 将SD卡插入神之眼，神之眼会自动开始升级过程。
![image](images/self_updating.png)


## English

This is the firmware of hardware project [璃月神之眼 Extended]("https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended").

These following hardwares are also supported:
- [璃月神之眼 Extended by mr258876]("https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended")
- [神之眼挂件V1.2_ESP32U by 小渣渣](https://oshwhub.com/Myzhazha/shen-zhi-yan-gua-jian-v1-2_esp32u)
- [璃月神之眼挂件 by 小渣渣](https://oshwhub.com/Myzhazha/li-yue-shen-zhi-yan-gua-jian) (Untested)

## Development Process

- Picture/Video display✅
- Setting menu🔲
- Multi-language support✅
- Resin data syncing✅