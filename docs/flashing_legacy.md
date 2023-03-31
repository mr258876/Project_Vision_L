# 刷入旧版本固件 / Flashing legacy firmware

自`L0.3.000`版本起，为了扩大程序可用空间，设备分区表发生了变化。在刷入`L0.3.000`之前版本的固件时，请按照下表配置`flash download tool`。

Since `L0.3.000`, device partition table had been changed for more flash space. To flash a firmware before `L0.3.000`, please configure `flash download tool` as following:

| 文件名 / filename | 位置 / offset |
| ---- | ---- |
| bootloader.bin | 0x1000 |
| partitions.bin | 0x8000 |
| ota_data_initial.bin | 0xe000 |
| firmware.bin | 0x10000 |
