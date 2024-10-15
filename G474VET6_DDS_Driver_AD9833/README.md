# README

* 本测试例程适配自制开发板 [*@ Penguins V3.1*](https://github.com/Penguins-lwz/NUEDC-training/blob/main/Hardware_Project/G474VET6_V3.1.eprj) 及 [康威科技 AD9833 模块](https://item.taobao.com/item.htm?id=522152798192&skuId=3882125657353)
* 更多信息请查阅 [ADI-AD9833](https://www.analog.com/cn/products/ad9833.html)

## 硬件连接
* 模块供电：2.3 V ~ 5.5 V，可选用 DAP-Link / 开发板 / 外接电源供电，注意共地
* 三线通信：PD6 <-> SYNC，PB3 <-> CLK，PB5 <-> DATA

## 实验现象
* 上电后，开发板板载白色电源指示灯、DDS 模块板载红色电源指示灯亮起
* 对按键 KEY1，按下后板载 LED 全部亮起，DDS 模块发出 1 kHz 正弦波
* 对按键 KEY2，按下后板载 LED 仅红色亮起，DDS 模块发出 1 kHz 三角波
* 对按键 KEY3，按下后板载 LED 仅绿色亮起，DDS 模块发出 1 kHz 矩形波
* 对按键 KEY4，按下后板载 LED 仅蓝色亮起，DDS 模块发出 1 kHz 二分频矩形波（即 500 Hz）

## 说明
* 本例程默认使用 **软件 SPI** 驱动 DDS 模块，驱动代码可修改为 **硬件 SPI**，切换方法参见显示屏切换说明
* 本 DDS 模块使用 SMA 接口，需使用专用信号线接入示波器观察波形
* 本 DDS 模块输出幅值不可调，正弦波与三角波典型峰峰值 600 mV
* 使用本 DDS 模块产生高频信号时，务必提前接入示波器观察波形有无失真、衰减，确认在接受范围内后使用
