# fingerprint-guard

如果需要启动时关闭LED：

如果你使用BM2166圆形指纹模块，请使用本项目中的库以便可以控制LED颜色。

如果你使用AS608指纹模块，请先尝试使用Arduino的Adafruit指纹库看能否启动关闭LED。如果不能：
```
//Adafruit_Fingerprint.h line 77
#define FINGERPRINT_AURALEDCONFIG 0x3C //!< Aura LED control
```
请根据指纹模块的用户手册把0x3C改为要求的指令码。