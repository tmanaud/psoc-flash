# psoc-flash
Small utility to flash psoc4 and psoc5 from SBC (single board computer, like rpi) using SWD pins with the HSSP procotol from Cypress.

## Setup
Connect SWD-C, SWD-D and XRES pins to your SBC GPIO.
Change the SWD_PhysicalLayer call to hardware pins functions.
Convert your HEX file with the C# HexFile Parser (Windows software available in AN84858) and replace HexImage.c and HexImage.h in the project.
Compile the software and run it on the SBC linux.

## Technical requirement
- GPIO access with SUNXI GPIO_lib on H3 ARM CPU

## Todo
- add other GPIO access to other platform
- port the HEX file parser (currently C# HexFile Parser) to read the .hex file instead of the generated HexImage.c