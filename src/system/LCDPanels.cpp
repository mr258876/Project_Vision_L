#include "system/LCDPanels.h"

lgfx::Panel_LCD *_panel;
lgfx::Bus_SPI _bus_instance;

void LCDinit(LGFX_Device *gfx, LCD_panel_t lcd_type, spi_host_device_t spi_host, uint8_t LCD_DC, uint8_t LCD_RST, uint8_t LCD_CS, uint8_t LCD_CLK, uint8_t LCD_MOSI, uint8_t LCD_MISO, bool isSharedSPI, uint32_t LCD_clock_speed)
{
    switch (lcd_type)
    {
    case LCD_ST7789:
        _panel = new lgfx::Panel_ST7789();
        break;
    default:
        _panel = new lgfx::Panel_GC9A01();
        break;
    }

    {                                      // バス制御の設定を行います。        // 设置总线
        auto cfg = _bus_instance.config(); // バス設定用の構造体を取得します。  // 获取总线设置结构体

        // SPIバスの設定  // SPI总线设置
        cfg.spi_host = spi_host; // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
        // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
        // ※ ESP-IDF版本更新后，若使用VSPI_HOST、HSPI_HOST报错，请使用SPI2_HOST、SPI3_HOST代替。
        cfg.spi_mode = 0;                  // SPI通信モードを設定 (0 ~ 3)   // SPI通信模式设置
        cfg.freq_write = LCD_clock_speed;  // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)  // SPI写时钟频率(80MHz除以整数)
        cfg.freq_read = LCD_clock_speed;   // 受信時のSPIクロック // SPI读时钟频率
        cfg.spi_3wire = true;              // 受信をMOSIピンで行う場合はtrueを設定  // 使用MOSI pin进行读操作时设定为true
        cfg.use_lock = true;               // トランザクションロックを使用する場合はtrueを設定  // 使用事务锁
        cfg.dma_channel = SPI_DMA_CH_AUTO; // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=2ch / SPI_DMA_CH_AUTO=自動設定) // 指定DMA通道
        // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
        // ※ ESP-IDF版本更新后，推荐使用SPI_DMA_CH_AUTO自动设置DMA通道。不推荐手动指定。
        cfg.pin_sclk = LCD_CLK;                    // SPIのSCLKピン番号を設定   // SPI CLK引脚
        cfg.pin_mosi = LCD_MOSI;                   // SPIのMOSIピン番号を設定   // SPI MOSI引脚
        cfg.pin_miso = (LCD_MISO ? LCD_MISO : -1); // SPIのMISOピン番号を設定 (-1 = disable)  // SPI MISO引脚(-1禁用)
        cfg.pin_dc = LCD_DC;                       // SPIのD/Cピン番号を設定  (-1 = disable)  // SPI 数据/指令引脚(-1禁用)
                                                   // SDカードと共通のSPIバスを使う場合、MISOは省略せず必ず設定してください。
                                                   // 屏幕与SD卡共用一个SPI总线时，必须指定MISO引脚。

        _bus_instance.config(cfg);      // 設定値をバスに反映します。   // 应用总线设置
        _panel->setBus(&_bus_instance); // バスをパネルにセットします。 // 为屏幕指定总线
    }

    {                                // 表示パネル制御の設定を行います。    // 设置屏幕
        auto cfg = _panel->config(); // 表示パネル設定用の構造体を取得します。  //获取屏幕设置构造体

        cfg.pin_cs = LCD_CS;   // CSが接続されているピン番号   (-1 = disable)   // 片选引脚
        cfg.pin_rst = LCD_RST; // RSTが接続されているピン番号  (-1 = disable)   // 重置引脚
        cfg.pin_busy = -1;     // BUSYが接続されているピン番号 (-1 = disable)   // busy信号引脚

        // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

        cfg.panel_width = 240;        // 実際に表示可能な幅   // 水平分辨率
        cfg.panel_height = 240;       // 実際に表示可能な高さ // 垂直分辨率
        cfg.offset_x = 0;             // パネルのX方向オフセット量  // X方向偏移量
        cfg.offset_y = 0;             // パネルのY方向オフセット量  // Y方向偏移量
        cfg.offset_rotation = 0;      // 回転方向の値のオフセット 0~7 (4~7は上下反転) // 屏幕旋转方向(4-7为垂直翻转)
        cfg.dummy_read_pixel = 8;     // ピクセル読出し前のダミーリードのビット数     // 读取显存前的dummy bit数
        cfg.dummy_read_bits = 1;      // ピクセル以外のデータ読出し前のダミーリードのビット数 // 读取其他数据前的dummy bit数
        cfg.readable = false;         // データ読出しが可能な場合 trueに設定    // 启用读操作
        cfg.invert = true;            // パネルの明暗が反転してしまう場合 trueに設定  // 反色
        cfg.rgb_order = false;        // パネルの赤と青が入れ替わってしまう場合 trueに設定  // 像素使用RGB顺序
        cfg.dlen_16bit = false;       // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定 // 一次写入16 bit数据
        cfg.bus_shared = isSharedSPI; // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います) // 与SD卡共享总线

        _panel->config(cfg); // 应用屏幕设置
    }

    gfx->setPanel(_panel);
}

int brightness_nit_level_curve_ST7789(float nit)
{
    float lev = (nit - 1.067061) / 1.979675;    // 506.93 nit max by measure
    int res = round(lev);
    res = (res < 1 ? 1 : res);
    res = (res > 255 ? 255 : res);
    return res;
}

int brightness_nit_level_curve_GC9A01(float nit)
{
    float lev = nit / 1.568627; // typical 400 nit
    int res = round(lev);
    res = (res < 1 ? 1 : res);
    res = (res > 255 ? 255 : res);
    return res;
}