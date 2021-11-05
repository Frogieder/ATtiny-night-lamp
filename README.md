# ATtiny night lamp

## This project is still in development!
Even though this project is mostly functional at this point, yet some changes are still going to be made. The code is what's going to change the most, but the schematic might get changed too if it's necessary. 

## About the project

This repo contains all the files needed to make a night lamp powered by ATtiny.
Compatible MCUs are:
* ATtiny13
* ATtiny25
* ATtiny45
* ATtiny85
* possibly some other MCUs with minor and/or major tweaks

### Features:

* 4 LEDs to light up your room so you can find a way to your bed
* a switch to fully disable the lamp
* capacitive touch sensor to manually control the lamp
* low power operation, MCU sleeps when the LEDs are off
* photoresistor to automatically turn the lamp on when it's dark
* PWM controller to slowly fade out the LEDs


# Make your own

**Beware, this project is still in active development and anything, including the circuit and the code may change**

## PCB
The folder 'schematics-boards' contains Eagle files, so you can export files in any format you need. You will need MMBF170 library downloaded in '~/EAGLE/libraries/MMBF170.lbr'. There is also a pdf (outdated) which contains exported file you can use if you are going to make the PCB using the photosensitive method. For toner transfer, you will need to mirror the design to be able to make it.

## Construction
### List of components:
* 1x MCU (Attiny85 or some other, discussed above)
* 1x THT photoresistor
* Resistors, 1206 package: 
    * 2x 15k - pulldowns, higher values than usual were chosen to minimize power usage
    * 1x 8M2 - sets the touch sensor sensitivity, higher values -> higher sensitivity
    * 1x 1M - creates volatge divider together with the photoresistor, choose your value based on your photoresistor
    4x 470R - LED current limiting resistor, y'know, not to burn them
* 1x 100nF capacitor
* 4x white LED, ideally with diffuser, or you can add an external one
* 1x THT switch
* 1x MMBF170 MOSFET
* PCB
* some cables
* conductive plate that can be used for the capacitive touch switch
* 4.5V batery

Assembly instructions: 
* Upload the program to the ATtiny
* Solder everything according to .brd file.
* Make the touch switch and attach it to its hole with a cable. 
* Solder the batery wires into the board and attach both the PCB and the touch switch to the batery holder.

To make the instructions clearer, I'll add some photos of my build once it's fully completed. 
