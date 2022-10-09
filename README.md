# The Vision L

↓求个翻译


Do Virtual Gods Hand Out Electronic Visions?

## 版本 / Versions
### 稳定版 / Stable Release
- [L0.1.1](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.1.1)
### 测试版 / Beta Release
- None
### 开发版 / Indev Release
- [L0.2.0-Indev22A092](https://github.com/mr258876/Project_Vision_L/releases/tag/L0.2.0-Indev22A092)

## 支持库 / Referenced Libraries
```
Adafruit BusIO  1.13.2
ArduinoJson 6.19.4
KXTJ3-1057  0.0.1
LovyanGFX   0.4.18
LVGL        8.3.2
OneButton   2.0.3
APDS-9930   https://github.com/Depau/APDS9930
LinkedList  https://github.com/ivanseidel/LinkedList
```

## 中文

该项目为硬件项目[璃月神之眼 Extended]("https://oshwhub.com/mr_258876/li-yue-shen-zhi-yan-gua-jian-extended")的对应固件。

## 开发进度

- 显示图片/视频✅
- 设置菜单/管理界面🔲
- 多语言支持🚧
- 从米游社API获取树脂🚧

## 使用方法
### 切换元素(切换视频)
- 短按两次距离传感器

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


<!-- ## English -->