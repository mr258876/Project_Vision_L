# The Vision L

## 🛑 不要在恢复模式中关闭设备
## DO NOT TURN OFF YOUR DEVICE IN RECOVERY MODE

在进行更新时强制关闭设备将导致固件损坏！

Force shutting down in updating will result in firmware corruption!

## 恢复模式 / Recovery Mode

自L0.3.000起，设备分区表中的OTA分区缩减为1个以扩大可用空间，更新操作由恢复模式固件进行。恢复模式固件将读取sd卡根目录中的`update.json`配置文件进行更新。

Since L0.3.000, the two OTA partitions in partition table are reduced to one to increase program available space, and update operation is performed by the recovery firmware. Recovery firmware will read `update.json` in root directory of SD card for updates.