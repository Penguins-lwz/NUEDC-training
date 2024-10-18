# README

* 本文件夹包含用于在 STM32 导入 [**CMSIS-DSP Version 1.16.2**](https://arm-software.github.io/CMSIS-DSP/latest/index.html) 的必要文件
* 注意：以上链接将在版本更新时自动链接至最新版本

## 获取方式(Access to CMSIS-DSP)

> CMSIS-DSP is actively maintained in the [**CMSIS-DSP GitHub repository**](https://github.com/ARM-software/CMSIS-DSP) and is released as a standalone [**CMSIS-DSP pack**](https://www.keil.arm.com/packs/cmsis-dsp-arm/versions/) in the [CMSIS-Pack format](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/index.html).
> 
> CMSIS-DSP 在 [**CMSIS-DSP GitHub 仓库**](https://github.com/ARM-software/CMSIS-DSP) 中得到了积极维护，也作为独立的 [**CMSIS-DSP 包**](https://www.keil.arm.com/packs/cmsis-dsp-arm/versions/) 以 [CMSIS-Pack 格式](https://open-cmsis-pack.github.io/Open-CMSIS-Pack-Spec/main/html/index.html) 发布。

* 自上述 GitHub 仓库下载，或自上述 CMSIS-DSP 包下载并安装，均可获得与本文件同目录的必要文件夹
    * `.\Include`
    * `.\PrivateInclude`
    * `.\Source`

## 导入方式

* 使用 CubeMX 新建工程，建议分配栈空间 (Stack Size) 不少于 4 KB (0x1000)
* 将本 CMSIS-DSP 文件夹复制至工程目录 `<ProjectName>\Drivers`
* 在 Keil 中新建 Groups，命名为 **Drivers/CMSIS-DSP**，导入 `.\Source` 中与文件夹名相同的 .c 文件
* 在 Options for Target 中，导入 `.\Drivers\CMSIS-DSP\Include` 与 `.\Drivers\CMSIS-DSP\PrivateInclude`
* 在 main.h 导入头文件 `#include "arm_math.h"`，如需使用 FFT 继续导入头文件 `#include "arm_const_structs.h"`

## 使用指南

* 有关各函数的详细介绍，请参见 [**API Reference**](https://arm-software.github.io/CMSIS-DSP/latest/modules.html)

| 文件名 | 主要功能 |
| ---- | ---- |
| **CommonTables.c** | **结构体与数表**，如 FFT 结构体、FFT 旋转因子、位反转、倒数 |
| **BasicMathFunctions.c** | **基本数学函数**，如加、减、乘、绝对值、点积、取反、偏移、尺度、位移、按位与、按位或、按位非、按位异或、裁剪 |
| **FastMathFunctions.c** | **快速近似函数**，如正弦、余弦、反正切、平方根、自然指数、自然对数、定点除法 |
| **ComplexMathFunctions.c** | **复数数学函数**，如共轭、取模、模平方、复数与实数的积、复数与复数的积 |
| **FilteringFunctions.c** | **滤波函数**，如卷积、相关、FIR 滤波、IIR 滤波 |
| **MatrixFunctions.c** | **矩阵函数**，如初始化、转置、求逆、尺度、矩阵加法、矩阵减法、矩阵乘法 |
| **TransformFunctions.c** | **变换函数**，如实数 FFT，复数 FFT |
| **ControllerFunctions.c** | **控制函数**，如正余弦、矢量旋转 |
| **StatisticsFunctions.c** | **统计函数**，如最大值、最小值、最大绝对值、最小绝对值、均值、方差、算术和、平方和、均方根、均方根误差 |
| **InterpolationFunctions.c** | **插值函数**，如线性插值、双线性插值、三次样条插值 |
| **WindowFunctions.c** | **窗口函数**，如汉宁窗、汉明窗、布莱克曼窗 |
| **SupportFunctions.c** | **辅助函数** |
| **SVMFunctions.c** | **向量机函数** |
| **BayesFunctions.c** | **贝叶斯函数** |
| **DistanceFunctions.c** | **相似度函数** |
| **QuaternionMathFunctions.c** | **四元数数学函数** |
