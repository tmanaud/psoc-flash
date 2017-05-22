/******************************************************************************
* File Name: RegisterDefines.h
* Version 1.0
*
* Description:
*  This header file contains the definitions for the programming pins on the
*  host side - SWDIO, SWDCK, XRES. The definitions include:
*
*  1.) Port number, Pin number of the programming pins 
*  2.) Registers for writing to the pins, reading from the pins, 
*      configuring the pin drive modes
*  3.) Mask values for writing to, reading from an individual pin
*  4.) Mask values for configuring the different pin drive modes
*
* Note:
*  The definitions provided here are for a PSoC 5LP host programmer.
*  Modify them as applicable for your specific host programmer.
*  These definitions are used in the file SWD_PhysicalLayer.h.
*
*******************************************************************************
* Copyright (c) 2013-2016, Cypress Semiconductor Corporation”
*******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
******************************************************************************/
#ifndef __REGISTERDEFINES_H
#define __REGISTERDEFINES_H

/***************************** USER ATTENTION REQUIRED ************************
***************************** HOST PROCESSOR SPECIFIC *************************
********************  PORT NUMBER, PIN NUMBER ASSIGNMENTS *********************
*
* Modify these port, pin assignment definitions based on host programmer
* pin selection
******************************************************************************/

#define SWDIO_PRT_NUM   0
#define SWDIO_PIN_NUM   0

#define SWDCK_PRT_NUM   0
#define SWDCK_PIN_NUM   1

#define XRES_PRT_NUM    0
#define XRES_PIN_NUM    2

/***************************** USER ATTENTION REQUIRED ************************
***************************** HOST PROCESSOR SPECIFIC *************************
************************  INPUT, OUTPUT, DRIVE MODE REGISTERS ***************
*
* PSoC 5LP host programmer I/O registers are 8-bits wide. The addresses of the
* PSoC 5LP I/O registers defined below are from the PSoC 5LP Technical Reference 
* Manual. The defines below are "Value at the 8-bit register address".
* The defines are used to change the pin output(OUT_REG), read the
* pin input (IN_REG), and also to change the pin drive mode(DM_REG).
* 
* Modify these definitions as applicable for your Host programmer.
******************************************************************************/

#define SWDIO_PRT_OUT_REG     (*((volatile unsigned char *)(0x40005100 + (SWDIO_PRT_NUM * 0x10)))) 
#define SWDIO_PRT_IN_REG      (*((volatile unsigned char *)(0x40005101 + (SWDIO_PRT_NUM * 0x10))))
#define SWDIO_PIN_DM_REG      (*((volatile unsigned char *)(0x40005000 + (SWDIO_PRT_NUM * 8) + SWDIO_PIN_NUM)))

#define SWDCK_PRT_OUT_REG     (*((volatile unsigned char *)(0x40005100 + (SWDCK_PRT_NUM * 0x10))))
#define SWDCK_PIN_DM_REG      (*((volatile unsigned char *)(0x40005000 + (SWDCK_PRT_NUM * 8) + SWDCK_PIN_NUM)))

#define XRES_PRT_OUT_REG      (*((volatile unsigned char *)(0x40005100 + (XRES_PRT_NUM * 0x10))))
#define XRES_PIN_DM_REG       (*((volatile unsigned char *)(0x40005000 + (XRES_PRT_NUM * 8) + XRES_PIN_NUM)))

/***************************** USER ATTENTION REQUIRED ************************
***************************** HOST PROCESSOR SPECIFIC *************************
************** Mask values for manipulating Port pins *************************
*
* These mask values will be used to modify the specific bits of a
* Port register (8-bits wide) like Port input/output registers. These will be
* used to set a output pin as high or low, or return the logic state (high or low)
* of an input pin.
* 
* Modify these as applicable for Host programmer.
******************************************************************************/
#define XRES_PIN_MASK   (0x01 << XRES_PIN_NUM)
#define SWDCK_PIN_MASK  (0x01 << SWDCK_PIN_NUM)
#define SWDIO_PIN_MASK  (0x01 << SWDIO_PIN_NUM)

/***************************** USER ATTENTION REQUIRED ************************
***************************** HOST PROCESSOR SPECIFIC *************************
********** Mask values for Pin Drive mode configuration ***********************
*
* Mask definitions below are for configuring the pin drive modes of Host PSoC 5LP.
*
* Output pins should be in Strong drive (CMOS Drive) mode and input pins should
* be in High impedance digital (High-Z) drive mode.
*
* Modify these mask values as applicable for Host programmer.
******************************************************************************/
#define HIGHZIN_DM_ANDMASK  0xF1
#define HIGHZIN_DM_ORMASK   0x02
#define CMOSOUT_DM_ANDMASK  0xF1
#define CMOSOUT_DM_ORMASK   0x0C

#endif /* __REGISTERDEFINES_H */


/* [] END OF FILE */
