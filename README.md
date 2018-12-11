# uC-OS-III-port-for-Nucleo-L073RZ

This project is just a simple blink led program developed in uC/OS III RTOS which was downloaded from the Micrium website https://www.micrium.com/download/stm32l476rg_nucleo_blinky/ and ported over to the Nucleo-L073RZ board and is ready to use in Atollic TureStudio. This port has only been tested as is and an addition test with two LED's blinking at different times. 

Just to be clear there may be unforeseen problems with the port but as Micrium has not provided a port for this board it may help others to get started. Micrium have also been sent this port for inclusion in there download section but as of now it has not yet been made available.

1. Download project and unzip.
2. After unzipping copy and paste the "Micrium_STM32L073RZ_Nucleo_Blinky" folder to the root of the c:\ drive.
3. Navigate to "Micrium_STM32L073RZ_Nucleo_Blinky/STM32L073RZ_Nucleo/ST/STM32L073RZ_Nucleo/Blinky/OS3/TrueSTUDIO/" and you will see a folder and two files. Edit the names of all three so they include a dot at the start of all three. (i.e. ".settings",".cproject",".project") This is so as i was unable to commit the files and folder with . prefixes to GitHub. 
4. Open project in Atollic TrueStudio and enjoy.
