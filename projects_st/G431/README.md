## 工程使用说明

本目录所有工程的开发环境为
* **STM32CubeMX V6.13.0**
* **STM32CubeG4 Firmware Package V1.6.1**
* 蓝桥杯嵌入式赛道用 [**CT117E-M4 开发板 V1.2**](https://item.taobao.com/item.htm?id=634196587834&skuId=4927684543021)

本目录所有工程的 LCD 与 I2C 驱动来自 [**第十六届蓝桥杯省赛资源数据包（电子赛）**](https://dasai.lanqiao.cn/notices/1096)，竞赛时将提供。

## 注意事项

* 大赛官方推荐使用 **STM32CubeMX V6.14.0**，但使用此版本生成工程可能出现 Keil 默认使用 **ST** 提供的 **分散加载文件 (\*.sct)**，可能造成下载程序后无法运行。此问题已提交至 [**ST 社区**](https://community.st.com/t5/stm32cubemx-mcus/stm32cubemx-v6-14-0-scatter-file-issue-with-stm32g474-project/td-p/780632)，笔者建议在新版本发布前使用历史版本。竞赛时如遇此现象，可于 Keil 的魔术棒 (Options for Target) 菜单修改配置，即使用 **Linker** 页 `Use Memory Layout from Target Dialog` 选项
* 资源数据包提供的 I2C 驱动可能存在对 E2PROM 连续读写错误的问题，笔者建议将 `void I2CStop(void)` 函数末尾等待时间延长至 1000 倍以上，即将最后一处 `delay1(DELAY_TIME);` 修改为 `delay1(DELAY_TIME * 1000);`