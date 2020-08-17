# HAR-Nucleo

This project is providing a step-by-step guide to run human activity recognition on any STM32 nucleo boards based on a Cortex M4 or M7. In addition, you will need an arduino extension shield "X-Nucleo-IKS01A3" which corresponds to motions MEMS sensors.



## Hardware requirements

![NUCLEO-L476RG - STM32 Nucleo-64 development board with STM32L476RG ...](Img/STM32Nucleo.jpg)

A Nucleo board, in this example I will use a STM32L476-Nucleo

![X-NUCLEO-IKS01A2 - Motion MEMS and environmental sensor expansion ...](Img/X-Nucleo-IKS01A3.jpg)

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

![3-1](Img/3-1.png)

2. Enter your board part number *(make sure you select a nucleo board)*

   ![3-2](Img\3-2.png)

   

3. Give a name to your project and click on "next"

   

   <img src="Img\3-3.png" alt="3-3" style="zoom: 50%;" />

   

4. Check that you will use the latest STM32Cube FW *(for L4 it's 1.16)*. Then click on "finish" to complete project creation. If you got a window saying if you want to initialize the peripheral by default ? click on "no".

   In fact, CubeMX tool can help you to initialize a new project, but during this workshop, you will learn to do it by yourself.

   

   <img src="Img\3-4.png" alt="3-4" style="zoom: 100%;" />



## HW & SW configurations with STM32CubeMX

As mentioned before, STM32CubeMX is a project configuration tool, you can set all the HW and SW components which will be used by your STM32 board. You can also find a standalone version of this tool which can generate project for other IDE *(Keil & IAR)*.

1. We will start by tuning the MCU clock at this highest value. Click on "Clock Configuration".

   ![4-1](Img\4-1.png)

2. Increase the HCLK at highest value depend on your Nucleo board (80 MHz for Nucleo L476 and 180 MHz for a F446 Nucleo)

![4-2](Img\4-2.png)



3. 
   In this part, we will initialize the USART in order to enable a communication between the PC and the STM32. First, let's check in the user manual of your nucleo board about the USART used to support virtual COM port between PC & STM32.
   - Nucleo-64
     - *https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf*
   - Nucleo-144
     * *https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-stmicroelectronics.pdf*

As you can find in the user manual, the USART2 (pin PA2 & PA3 of the MCU) is connected to ST-Link to support virtual COM port.![4-3](Img\4-3.png)



So, we need to enable USART2 and assign his pins on PA2 and PA3 of the STM32. This can be done on CubeMX as follow:

![4-3-2](Img\4-3-2.png)

4. Install and enable SW packages: **X-Cube-AI** & **X-Cube-MEMS1**

   ![4-4](Img\4-4.png) 

   Click on **"From Local..."** to **select your zip folder which you downloaded from ST website** during the SW prerequisites. Once you have selected the zip folder, click on **"Install Now"**.

![4-4-2](Img\4-4-2.png)

![4-4-3](C:\Users\nasirm\Documents\backup\Moussa_Doc\Demo\Motions\HAR-Nucleo\Img\4-4-3.png)

You need to do this operation for both packages **X-Cube-AI** & **X-Cube-MEMS1**

Now, that your SW packages are installed, the next step is to enable them as SW components in your project.

![4-4-4](Img\4-4-4.png)



5. In this part, the peripheral I2C is used as communication interface between the motion sensor and the MCU. We will initialize this peripheral following the pins mapping of Nucleo board and the motion mems shield.

   Check out how the I2C is available on the IKS01A3 expansion shield user manual

   - *https://www.st.com/resource/en/user_manual/dm00601501-getting-started-with-the-xnucleoiks01a3-motion-mems-and-environmental-sensor-expansion-board-for-stm32-nucleo-stmicroelectronics.pdf*

![5-1](Img\5-1.png)

​		Now, check which STM32 PINs are available on the PINs P9 & P10 of the connector CN5.

- Nucleo-64

  - *https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf*

- Nucleo-144

  - *https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-stmicroelectronics.pdf*

  ![5-2](Img\5-2.png)

  From the information collected on these user manual, in STM32CubeMX, we have to enable **I2C1 on PB8 and PB9 of the MCU**.

  

6. Configure your **I2C1 peripheral** in your project, go on tab **"Connectivity"**

![6-1](Img\6-1.png)

7. In this section, we will enable the **"interruption mode"** 

   Check out how the external interrupt mode is available on the IKS01A3 expansion shield user manual *(for the LSM6DSO sensor)*

   - *https://www.st.com/resource/en/user_manual/dm00601501-getting-started-with-the-xnucleoiks01a3-motion-mems-and-environmental-sensor-expansion-board-for-stm32-nucleo-stmicroelectronics.pdf*

![7-1](Img\7-1.png)

​	Check in the Nucleo user manual, which GPIO is available on the PIN5 of the connector CN9.

- Nucleo-64
  - *https://www.st.com/resource/en/user_manual/dm00105823-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf*
- Nucleo-144
  - *https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-stmicroelectronics.pdf*



![7-2](Img\7-2.png)



Now, go back to your project and enable the **GPIO PB5** in **"GPIO_EXTI5"** *(15)*. Configure it on **"System Core"**, click on **GPIO** and verify the right mode **"external interrupt mode with rising edge trigger detection"**.

![7-3](Img\7-3.png)



Finally, click on **NVIC** tab and enable the interrupt controller on **EXTI line[9:5] interrupts** *(16)*

![7-4](Img\7-4.png)

8. In this last part, you will configure the SW libraries: X-Cube-AI & X-Cube-MEMS1. As reminder, X-Cube-MEMS1 is a high-level library which will provide the **functions to use the motion sensor**, and X-Cube-AI is the high-level library which will provide the **functions to run neural network model** on STM32.

   Click on **"Additional software"** and start with **X-Cube-MEMS1** *(17)*, at this stage, you first need to **check "Board Extension MEMS"** to enable the library for the expansion shield. Then, click on **"Platform Setting"** and select I2C1 *(18)*.



![8-1](Img\8-1.png)



​	X-Cube-AI is our converter tool to map neural network on STM32 in an optimized way. You will need a pre-trained model file to use this tool. Please find in this git repository, a pre-trained model ***"Utilities/AI_resources/cnn_gmp.h5"***. This model has been trained using Keras framework.

You can upload this model into your project as follow:

![8-2](Img\8-2.png)



At this stage, all the HW & SW configurations are done. You can generate the software code and start using it.

![8-3](Img\8-3.png)





## Write your application code to use the sensor

In this part, we will handle the software library **X-Cube-MEMS1** generated in the previous section with **STM32CubeMX**. In fact, this library offers several functions to configure your sensor (frequency rate, value scaling, mode...)

Let's first have a look to the code generated:

![9-1](Img\9-1.png) 

You can notice that in the **main.c** file, there are some section with **"USER CODE BEGIN..."** and **"USER CODE END..."**, you should write your code between these sections. Because, when you will need to regenerate some code from **STM3CubeMX**, only the **user code** written between these sections will be saved.

1. You can start by building the project to make sure that generated code is not raising any compilation error(s).



![9-2](Img\9-2.png)