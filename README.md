# OpenScoreBoard
This repo contains the source code to create a digital scoreboard by multiplexing through 6 LED Strips fashioned in the form of seven segment dispays. To use this, you must wire the PIC Microcontroller to multiplex! This will not work with addressable LEDs!

Note: This code is written for a very specific hardware setup, and some coding conventions in this repo will seem trivial, not to mentiuon that this code is specifically for a microcontroller. Standard software conventions are out the window...as they should be in hardware

## What it Does
When programmed into a PIC Microcontroller, the controller lights up LED strips to show digits on a scoreboard, It works with a companion application which can be found here (link soon...)


## What I Used:
* PIC18F4455
* PickIT3 Programmer
* MPLab X
* HC-06 Bluetooth Controller
...and oscilloscopes and stuff

## Stats
* I/O 44 Wires
+ 42 Output to LEDs
+1 Tx Pin
+ 1 Rx Pin
