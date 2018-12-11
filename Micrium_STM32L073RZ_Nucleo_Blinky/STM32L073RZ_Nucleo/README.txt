BLINKY EXAMPLE FOR THE ST STM32L073RZ-Nucleo.

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
- ST/STM32L476RG_Nucleo/Blinky/OS3/TrueSTUDIO/

USAGE INSTRUCTIONS

TrueSTUDIO
- Import the workspace in TrueSTUDIO and make sure the "Copy projects into workspace" Options box is UNCHECKED.
- Press 'CTRL + B' to build the project and create a Debug session by selecting the Blinky workspace and pressing F11.
- Once the debug session has started, press F8 to run/resume the example.
- The project creates a task which blinks an LED every 1 second.
- Now modify the call to OSTimeDlyHMSM() in StartupTask() to increase or decrease the frequency at which the LED blinks.
- Build and run again to see the change.

Modified Micrium's Blinky example project for STM32L476RG-Nucleo and ported it for STM32L073RZ-Nucleo. 
Done by Darren Sherin University of Limerick Ireland on 10/10/2018. Email 16129008@studentmail.ul.ie.