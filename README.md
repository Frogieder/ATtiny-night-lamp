# ATtiny night lamp

## This project is still in development!
I don't recommmend making it until this message gets removed. At this point the code isn't functional, the board may get changed and there are no instructions on how to make it. If you still want to make it, I'd recommend to wait a few weeks/months until I make the first usable version. After that there shouldn't be any changes in the schematic, so it should be safe to make.

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

### Planned features:

* photoresistor to automatically turn the lamp on when it's dark
* PWM controller to slowly fade the LEDs out instead of simply switching them off
* making the thing actually work :P

For full TO-DO list check source-code/main.c

# Make your own

**Beware, this project is still in active development and anything, including the circuit and the code may change**

The folder 'schematics-boards' contains Eagle files, so you can export files in any format you need. You will need MMBF170 library downloaded in '~/EAGLE/libraries/MMBF170.lbr'. There is also a pdf which contains exported file you can use if you are going to make the PCB using the photosensitive method. For toner transfer, you will need to mirror the design to be able to make it. 
