## STM32F10X StdPeriph CMake Project

本项目适配了STM32F10X固件库，针对CMSIS v6驱动和GCC编译器进行了适配，并优化了链接和生成烧录文件的脚本配置。项目已在STM32F103C6T6和GCC版本14.1.0上测试成功。

### 当前使用的固件版本
- STM32F10X外设库 v3.6.0
- CMSIS驱动 v6.1.0

由于ST提供的版本较旧，本项目使用了较新的CMSIS v6，理论上支持相近版本。

### 不同型号设备的配置
请在`stm32f10x.h`中设置设备型号，并在`CMakeLists.txt`中设置相应的启动文件。同时，需要在链接脚本`STM32F10x.ld`中修改相应参数。


## STM32F10X StdPeriph CMake Project

This project adapts the STM32F10X firmware library, making it compatible with CMSIS v6 drivers and the GCC compiler. It also optimizes the scripts for linking and generating flash files. The project has been successfully tested on the STM32F103C6T6 and GCC version 14.1.0.

### Current Firmware Versions
- STM32F10X Peripheral Library v3.6.0
- CMSIS Driver v6.1.0

Since the version provided by ST is outdated, this project uses the newer CMSIS v6, which theoretically supports similar versions.

### Configuration for Different Device Models
Set the device model in `stm32f10x.h`, and configure the corresponding startup file in `CMakeLists.txt`. Additionally, modify the relevant parameters in the linker script `STM32F10x.ld`.
