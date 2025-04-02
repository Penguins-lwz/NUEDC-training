## 工程环境要求

为便于统一教学并沿用此前教程，使用本仓库所有工程应当满足
* 安装的 [**MSPM0-SDK**](https://www.ti.com.cn/tool/cn/MSPM0-SDK) 的版本号为 [V2.03.00.07](https://www.ti.com.cn/tool/cn/download/MSPM0-SDK/2.03.00.07)，已非最新版本
* 安装的 [**SYSCONFIG**](https://www.ti.com.cn/tool/cn/SYSCONFIG) 的版本号为 [V1.22.0.3893](https://www.ti.com.cn/tool/cn/download/SYSCONFIG/1.22.0.3893)，已非最新版本
* 安装以上二者时均使用默认路径 `C:\ti\`

要适配安装在其他路径的、其他版本的 MSPM0-SDK 与 SYSCONFIG，可通过修改 Keil 配置与以下文件内容实现。但此行为将造成无法直接运行本仓库工程，如无强烈需求请遵循前述要求，此处不提供修改原理与方法。
* `<SDK_ROOT>\tools\keil\MSPM0_SDK_syscfg_menu_import.cfg`
* `<PROJECT_ROOT>\MDK-ARM\syscfg_penguins.bat`

## 工程使用说明

本仓库所有工程基于 **LP_MSPM0G3507** 开发板配置，可由 SysConfig 移植至其他开发板。

本仓库所有工程可任意存放工程路径（甚至与 MSPM0-SDK 不在同一磁盘，如 `D:\`）。

本仓库所有工程参考 STM32CubeMX 生成的文件架构：
* `<PROJECT_ROOT>\Core\` 与 `<PROJECT_ROOT>\BSP\` 存放用户代码
* `<PROJECT_ROOT>\MDK-ARM\` 存放 Keil 必要文件，用户可由 `Project.uvprojx` 进入 Keil
* `<PROJECT_ROOT>\MSPM0-SDK\` 存放 SYSCONFIG 配置文件，如修改配置后 SYSCONFIG 要求保存，应当存放于此

本仓库所有工程均已修改启动文件，栈空间扩充至 `0x1000 (4 KB)`。

## 注意事项

* 本仓库配有适配 TI MCU 的批处理文件 `keilkillforti.bat` 以清理编译文件
* 本仓库为避免 GitHub 不跟踪空目录，使用 `.gitkeep` 占位，用户本地部署时可移除
* 除工程 `00_empty_32MHz` 使用片内振荡器（主频 32 MHz）外，其他工程均使用外置晶振（主频 80 MHz）
* 如遇工程可烧录但未按预期工作，请尝试关闭外置晶振，使用片内振荡器直接作为主频
