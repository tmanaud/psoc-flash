/******************************************************************************
* File Name: SWD_PhysicalLayer.c
* Version 1.0
*
* Description:
*  This file provides the source code for the physical layer functions of the
*  SWD protocol. These function definitions are the same as the corresponding
*  macro definitions in SWD_PhysicalLayer.h
*
* Owner:
*   Tushar Rastogi, Application Engineer (tusr@cypress.com)
*
* Related Document:
*   AN84858 - PSoC 4 Programming using an External Microcontroller (HSSP)
*
* Hardware Dependency:
*   PSoC 5LP Development Kit - CY8CKIT-050
*
* Code Tested With:
*   PSoC Creator 3.2
*   ARM GCC 4.8.4
*   CY8CKIT-050
*
* Note:
*  The functions defined here are specific to PSoC 5LP Host Programmer.
*  Modify the definitions as applicable for your Host Programmer.
*
*******************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation.
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

/******************************************************************************
*   Header file Inclusion
******************************************************************************/

#include "gpio_lib.h"
#include "SWD_PhysicalLayer.h"

#define XRES_GPIO 9
#define XRES_PORT SUNXI_GPG

#define SWDC_GPIO 8
#define SWDC_PORT SUNXI_GPG

#define SWDD_GPIO 6
#define SWDD_PORT SUNXI_GPA




/******************************************************************************
*   Function Definitions
******************************************************************************/

/***************************** USER ATTENTION REQUIRED ************************
***************************** HOST PROCESSOR SPECIFIC *************************
******************* SWD Protocol Physical Layer functions *********************
*
* All of the function definitions below are for a PSoC 5LP host programmer.
* Modify the definitions as applicable for the specific host programmer.
******************************************************************************/

/******************************************************************************
* Function Name: SetSwdckCmosOutput
*******************************************************************************
*
* Summary:
*  Sets the SWDCK pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDCK_DRIVEMODE_CMOSOUT in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdckCmosOutput()
{
    //SWDCK_PIN_DM_REG = (SWDCK_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK;
    // setGPIODirection(SWD_C_LINUX_GPIO, GPIO_OUT);
    sunxi_gpio_set_cfgpin(SWDC_PORT(SWDC_GPIO), SUNXI_GPIO_OUTPUT);

}


/******************************************************************************
* Function Name: SetSwdckHizInput
*******************************************************************************
*
* Summary:
*  Sets the SWDCK pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDCK_DRIVEMODE_HIGHZIN in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdckHizInput()
{
    //SWDCK_PIN_DM_REG = (SWDCK_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK;
    // setGPIODirection(SWD_C_LINUX_GPIO, GPIO_IN);
    sunxi_gpio_set_cfgpin(SWDC_PORT(SWDC_GPIO), SUNXI_GPIO_INPUT);
}

/******************************************************************************
* Function Name: SetSwdioCmosOutput
*******************************************************************************
*
* Summary:
*  Sets the SWDIO pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDIO_DRIVEMODE_CMOSOUT in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdioCmosOutput()
{
    //SWDIO_PIN_DM_REG = (SWDIO_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK;
    // setGPIODirection(SWD_D_LINUX_GPIO, GPIO_OUT);
    sunxi_gpio_set_cfgpin(SWDD_PORT(SWDD_GPIO), SUNXI_GPIO_OUTPUT);
}

/******************************************************************************
* Function Name: SetSwdioHizInput
*******************************************************************************
*
* Summary:
*  Sets the SWDIO pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDIO_DRIVEMODE_HIGHZIN in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdioHizInput()
{
    //SWDIO_PIN_DM_REG = (SWDIO_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK;
    // setGPIODirection(SWD_D_LINUX_GPIO, GPIO_IN);
    sunxi_gpio_set_cfgpin(SWDD_PORT(SWDD_GPIO), SUNXI_GPIO_INPUT);
}

/******************************************************************************
* Function Name: SetXresCmosOutput
*******************************************************************************
*
* Summary:
*  Sets the XRES pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  XRES_DRIVEMODE_CMOSOUT in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetXresCmosOutput()
{
    //XRES_PIN_DM_REG = (XRES_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK;
    // setGPIODirection(SWD_XRES_LINUX_GPIO, GPIO_OUT);
    sunxi_gpio_set_cfgpin(XRES_PORT(XRES_GPIO), SUNXI_GPIO_OUTPUT);
}

/******************************************************************************
* Function Name: SetXresHizInput
*******************************************************************************
*
* Summary:
*  Sets the XRES pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  XRES_DRIVEMODE_HIGHZIN in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetXresHizInput()
{
    //XRES_PIN_DM_REG = (XRES_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK;
    sunxi_gpio_set_cfgpin(XRES_PORT(XRES_GPIO), SUNXI_GPIO_INPUT);
}

/******************************************************************************
* Function Name: SetSwdckHigh
*******************************************************************************
*
* Summary:
*  Sets the SWDCK pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDCK_OUTPUT_HIGH in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdckHigh()
{
    // SWDCK_PRT_OUT_REG = SWDCK_PRT_OUT_REG | SWDCK_PIN_MASK;
    // setGPIOValue(SWD_C_LINUX_GPIO, GPIO_HIGH);
    sunxi_gpio_output(SWDC_PORT(SWDC_GPIO), 1);
}

/******************************************************************************
* Function Name: SetSwdckLow
*******************************************************************************
*
* Summary:
*  Sets the SWDCK pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDCK_OUTPUT_LOW in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdckLow()
{
    //SWDCK_PRT_OUT_REG = SWDCK_PRT_OUT_REG & (~SWDCK_PIN_MASK);
    // setGPIOValue(SWD_C_LINUX_GPIO, GPIO_LOW);
    sunxi_gpio_output(SWDC_PORT(SWDC_GPIO), 0);
}

/******************************************************************************
* Function Name: SetSwdioHigh
*******************************************************************************
*
* Summary:
*  Sets the SWDIO pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition
*  SWDIO_OUTPUT_HIGH in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdioHigh()
{
    // SWDIO_PRT_OUT_REG = SWDIO_PRT_OUT_REG | SWDIO_PIN_MASK;
    // setGPIOValue(SWD_D_LINUX_GPIO, GPIO_HIGH);
    sunxi_gpio_output(SWDD_PORT(SWDD_GPIO), 1);
}

/******************************************************************************
* Function Name: SetSwdioLow
*******************************************************************************
*
* Summary:
*  Sets the SWDIO pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDIO_OUTPUT_LOW
*  in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetSwdioLow()
{
    //SWDIO_PRT_OUT_REG = SWDIO_PRT_OUT_REG & (~SWDIO_PIN_MASK);
    // setGPIOValue(SWD_D_LINUX_GPIO, GPIO_LOW);
    sunxi_gpio_output(SWDD_PORT(SWDD_GPIO), 0);
}

/******************************************************************************
* Function Name: SetXresHigh
*******************************************************************************
*
* Summary:
*  Sets the XRES pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_OUTPUT_HIGH
*  in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetXresHigh()
{
    //XRES_PRT_OUT_REG = XRES_PRT_OUT_REG | XRES_PIN_MASK;
    // setGPIOValue(SWD_XRES_LINUX_GPIO, GPIO_HIGH);
    sunxi_gpio_output(XRES_PORT(XRES_GPIO), 1);
}

/******************************************************************************
* Function Name: SetXresLow
*******************************************************************************
*
* Summary:
*  Sets the XRES pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_OUTPUT_LOW
*  in SWD_PhysicalLayer.h.
*
******************************************************************************/
inline void SetXresLow()
{
    //XRES_PRT_OUT_REG = XRES_PRT_OUT_REG & (~XRES_PIN_MASK);
    sunxi_gpio_output(XRES_PORT(XRES_GPIO), 0);
}

/******************************************************************************
* Function Name: ReadSwdio
*******************************************************************************
*
* Summary:
*  Returns the state of the SWDIO input pin
*
* Parameters:
*  None.
*
* Return:
*  unsigned char (only one of the two values as given below)
*   0x00 - If the SWDIO pin state is low
*   0x01 - If the SWDIO pin state is high
*
* Note:
*  The function definition is the same as the macro definition SWDIO_INPUT_READ
*  in SWD_PhysicalLayer.h.
*
******************************************************************************/
unsigned char ReadSwdio()
{
    // return ((SWDIO_PRT_IN_REG >> SWDIO_PIN_NUM) & 0x01);
    // return getGPIOValue(SWD_D_LINUX_GPIO);
    if ( sunxi_gpio_input(SWDD_PORT(SWDD_GPIO)))
        return 0x01;
    else
        return 0x00;
}

/* [] END OF FILE */
