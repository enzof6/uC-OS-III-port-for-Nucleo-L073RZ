# uC-OS-III-port-for-Nucleo-L073RZ

This project is just a simple blink led program developed in uC/OS III RTOS which was downloaded from the Micrium website https://www.micrium.com/download/stm32l476rg_nucleo_blinky/ and ported over to the Nucleo-L073RZ board and is ready to use in Atollic TureStudio. This port has only been tested as is and an addition test with two LED's blinking at different times. 

Just to be clear there may be unforeseen problems with the port but as Micrium has not provided a port for this board it may help others to get started. Micrium have also been sent this port for inclusion in there download section but as of now it has not yet been made available.

Other projects at https://digitalelectronicsprojects.wordpress.com/

1. Download project and unzip.
2. After unzipping copy and paste the "Micrium_STM32L073RZ_Nucleo_Blinky" folder to the root of the c:\ drive.
3. Navigate to "Micrium_STM32L073RZ_Nucleo_Blinky/STM32L073RZ_Nucleo/ST/STM32L073RZ_Nucleo/Blinky/OS3/TrueSTUDIO/" and you will see a folder and two files. Edit the names of all three so they include a dot at the start of all three. (i.e. ".settings",".cproject",".project") This is so as i was unable to commit the files and folder with . prefixes to GitHub. 
4. Open project in Atollic TrueStudio and enjoy.

# BLINKY EXAMPLE FOR THE ST STM32L073RZ-Nucleo.

This example project demonstrates how to create a kernel task which blinks an LED.

MICRIUM PRODUCT VERSIONS
- uC/OS-III v3.06.02
- uC/CPU    v1.31.02
- uC/LIB    v1.38.02

IDE/COMPILER VERSIONS
- TrueSTUDIO for STM32/GNU v9.0.1

HARDWARE SETUP
- Connect USB Mini-B cable to CN1 to provide power.

WORKSPACE LOCATIONS
- ST/STM32L073RZ_Nucleo/Blinky/OS3/TrueSTUDIO/

USAGE INSTRUCTIONS

TrueSTUDIO
- Import the workspace in TrueSTUDIO and make sure the "Copy projects into workspace" Options box is UNCHECKED.
- Press 'CTRL + B' to build the project and create a Debug session by selecting the Blinky workspace and pressing F11.
- Once the debug session has started, press F8 to run/resume the example.
- The project creates a task which blinks an LED every 1 second.
- Now modify the call to OSTimeDlyHMSM() in StartupTask() to increase or decrease the frequency at which the LED blinks.
- Build and run again to see the change.

Modified Micrium's Blinky example project for STM32L476RG-Nucleo and ported it for STM32L073RZ-Nucleo.
