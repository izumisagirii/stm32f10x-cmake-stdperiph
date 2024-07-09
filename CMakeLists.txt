cmake_minimum_required(VERSION 3.20)
project(STM32Project C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -O2 -Os")

include_directories(
    ${CMAKE_SOURCE_DIR}/CMSIS/CM3/CoreSupport
    ${CMAKE_SOURCE_DIR}/CMSIS/CM3/DeviceSupport/ST/STM32F10x
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/inc
    ${CMAKE_SOURCE_DIR}/src
)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if(supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO/LTO not supported: ${error}")
endif()

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/blink.c

    # ${CMAKE_SOURCE_DIR}/CMSIS/CM3/CoreSupport/core_cm3.c
    ${CMAKE_SOURCE_DIR}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/misc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
    ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
)

# 启动文件
set(STARTUP ${CMAKE_SOURCE_DIR}/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(STM32Project ${SOURCES} ${STARTUP})

# 链接器脚本
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F10x_StdPeriph_Driver/STM32F10x.ld)

target_link_options(STM32Project PRIVATE -T ${LINKER_SCRIPT})

# target_link_options(STM32Project PRIVATE -T ${LINKER_SCRIPT} -Wl,--gc-sections)

# 链接 Newlib 库
target_link_libraries(STM32Project PRIVATE -lc -lgcc -lnosys)

# 生成二进制文件
add_custom_command(TARGET STM32Project POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/STM32Project ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/out.bin
)

# 生成HEX文件
add_custom_command(TARGET STM32Project POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/STM32Project ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/out.hex
)

# 打印大小信息
add_custom_command(TARGET STM32Project POST_BUILD
    COMMAND ${SIZE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/STM32Project
    COMMAND ${SIZE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/out.hex
)