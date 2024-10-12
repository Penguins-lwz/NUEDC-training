# README

* 本测试例程适配自制开发板 [*@ Penguins V3.1*](https://github.com/Penguins-lwz/NUEDC-training/blob/main/Hardware_Project/G474VET6_V3.1.eprj) 及其板载 [金逸晨 TFTLCD 显示屏](https://item.taobao.com/item.htm?id=680586598490&skuId=5055154567363)

## 实验现象
* 上电后，板载白色电源指示灯亮起
* 显示屏依 **红、橙、黄、绿、蓝、紫、白** 顺序以 200 ms 间隔刷屏，结束后使用已导入的 4 种字号显示字符串 ***"Penguins"***
* 串口 (Type-C) 依次发送字符串 ***"G474VET6 UART1 Connected.\n"***，***"Continuous sending test.\n"***
* 可使用 VOFA+ 发送字符串，MCU 将在其前增补字符串 ***"RxMsg: "*** 后立即发回
* 引脚 PA4 输出频率 10 kHz，偏置 1.5 V，幅值 1.2 V 的正弦波
* 引脚 PA5 输出频率 10 kHz，偏置 1.5 V，幅值 0.6 V 的正弦波，较 PA4 滞后 1/4 个周期
* 除复位按键 RST 外，4 个可编程按键均支持以 400 ms 为分界的短按/长按分辨
* 对按键 KEY1 ~ KEY3，分别控制 **红、绿、蓝** LED，短按点亮、长按熄灭
* 对按键 KEY4，按下后开启经引脚 PA0 与 PA1 、采样率 1 MHz 的双路 ADC 采样，并经串口打印采样值

## 说明
* 本例程默认使用 **硬件 SPI** 驱动显示屏，修改为 **软件 SPI** 的方法如下：
    * 在 CubeMX 中，关闭 **SPI4** 外设，将 **PE2** 与 **PE6** 配置为 **默认低电平的高速输出引脚**，分别命名为 **LCD_SCL** 与 **LCD_SDA**
    * 在 *lcd.h* 文件中，修改 **LCD_USE_HARDWARE** 的宏定义值为 **0**
* 使用 **软件 SPI** 驱动显示屏时，在变色刷屏时将可明显看出屏幕刷新过程
