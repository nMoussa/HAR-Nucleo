# HAR-Nucleo

This project is providing a step-by-step guide to run human activity recognition on any STM32 nucleo boards based on a Cortex M4 or M7. In addition, you will need an arduino extension shield "X-Nucleo-IKS01A3" which corresponds to motions MEMS sensors.



## Hardware requirements

![NUCLEO-L476RG - STM32 Nucleo-64 development board with STM32L476RG ...](file:///C:/Users/nasirm/AppData/Local/Temp/msohtmlclip1/01/clip_image001.jpg)

A Nucleo board, in this example I will use a STM32L476-Nucleo

![X-NUCLEO-IKS01A2 - Motion MEMS and environmental sensor expansion ...](file:///C:/Users/nasirm/AppData/Local/Temp/msohtmlclip1/01/clip_image001.jpg)

A motions MEMS shield X-Nucleo-IKS01A3

and finally an USB micro cable



## Software requirements

- STM32CubeIDE 1.4.0
  - Eclipse based IDE to write, build and run embedded C code on STM32 (license-free)
  - https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-ides/stm32cubeide.html#overview](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-ides/stm32cubeide.html
- X-Cube-AI 5.1.2
  - Converter tool to map Neural Networks on STM32 in an optimized way
  - https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-ai.html#overview](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-ai.html
- X-Cube-MEMS1 8.0.0
  - Library to use ST motion sensors
  - https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-mems1.html#overview](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-mems1.html
- STM32F4Cube FW
  - Back-end library to use STM32 HAL & BSP (depend on your Nucleo board, the example uses F4)

## Start & configure your project with STM32CubeIDE

STM32CubeIDE is based on eclipse, it's using GNU C/C++ compiler and GDB debugger. It supports ST-Link which is the main HW interface to flash and debug embedded C code on STM32.

It also includes STM32CubeMX which is a project generation tool for STM32. In fact, this tool provides a friendly graphical interface to initialize MCU HW peripherals, clock, pinout and middleware.  A FW is then generated and ready to use.

In this section, we will get familiar with CubeIDE & CubeMX tools.



1. Launch STM32CubeIDE 1.14.0 software and start with a new STM32 Project as described below:

![3-1](C:\Users\nasirm\Documents\backup\Moussa_Doc\Demo\Motions\HAR-Nucleo\Img\3-1.png)