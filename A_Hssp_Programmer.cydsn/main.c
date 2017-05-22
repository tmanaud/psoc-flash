/******************************************************************************
*  Project Name: A_Hssp_Programmer
*  Project Revision: 1.00
*  Software Version: PSoC Creator 4.0
*  Device Tested: CY8C5868AXI-LP035
*  Compilers Tested: ARM GCC 4.9-2015-q1-update
*  Related Hardware: CY8CKIT-050
******************************************************************************/

/******************************************************************************
* Project Description:
* This is a sample HSSP implmentation demonstrating a PSoC 5LP programming
* PSoC 4/PSoC Analog Coprocessor. The project is tested using CY8CKIT-050 
* with PSoC 5LP chip and CY8CKIT-001 with PSoC 4 processor module.
*
* Connections Required
* CY8CKIT-050 (PSoC 5LP DVK) :
*  Pin_SWDIO (P0[0])- This pin is connected to SWDIO (Debug pin) of PSoC 4 kit.
*  Pin_SWDCK (P0[1])- This pin is connected to SWDCK (Debug pin) of PSoC 4 kit.
*  Pin_XRES  (P0[2])- This pin is connected to XRES input of PSoC kit.
*  Pin_Start (P6[1])- This pin is internally connected to switch SW2.
*
* Note that the GNDs of both DVKs should be connected together and Power should
* be supplied from a single source.
*
* The hex file included in this project toggles pin P1[6] of PSoC 4 at 1Hz
* frequency and displays “PSoC Programmed” on the character LCD mounted on
* CY8CKIT-001 DVK.
* 
* Connections required on the CY8CKIT-001 with PSoC 4 Processor Module :
* 	1. Connect P1[6] to LED1
*	2. Mount character LCD on the kit
*
* Press SW2 on the PSoC 5LP DVK to start the programming operation.
* ProgramDevice() function in main.c calls all the programming steps
* sequentially to program PSoC 4.
*
* main.c checks the result of ProgramDevice() function and if it returns 
* SUCCESS, "HSSP Success" is displayed on the character LCD mounted on the
* PSoC 5LP kit. If ProgramDevice() returns failure, Step of failure, Reason
* of failure is displayed on the LCD. If the error is because of SROM, It
* displays the SROM error code.
*
* On the PSoC 4 Side, LED connected to P1[6] starts to toggle at 1 Hz
* frequency and character LCD displays the message after successful 
* programming.
*
* Note:
*  The Character LCD functions and the Pin_Start APIs in the main() function
*  are for PSoC 5LP host programmer. If you are using any other microcontroller,
*  replace the functions with the APIs supported by the host or change the macro
*  USE_LCD and USE_START_PIN to 0 to remove all LCD and Pin_Start functions.
******************************************************************************/

/* Copyright (c) 2013-2016, Cypress Semiconductor Corporation
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

*******************************************************************************/


/* This file is included for calling Character LCD and Pin_Start APIs in
   PSoC 5LP. Remove this header file while porting to non PSoC 5LP host
   programmer */
#include <device.h> 

/* These macros are used to remove all LCD and Pin_Start functions while
   porting this code to non PSoC 5LP host programmer */
#define USE_LCD 		(1u)
#define USE_START_PIN 	(1u)

/* This file has the top level HSSP routines that should be called from main
   application code */
#include "ProgrammingSteps.h"

/* Function which sequentially calls all the programming steps */
static unsigned char ProgramDevice(void);

/* Global variable which stores the current programming step under execution */
static unsigned char currentStep = 0u;

int main()
{
    /* Variable to store the result of HSSP operation */
    unsigned char programResult = 0u;   
	
	/* Variable to store the HSSP Error status in case of failure */
    unsigned char errorStatus = 0u; 
	
	/* Variable to store the SROM Error status if errorStatus contains
	   SROM_TIMEOUT_ERROR error */
    unsigned char sromErrorStatus = 0u;
	
	/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
	if(USE_LCD == 1)
	{
		/* Initialize Character LCD  */
	    LCD_Char_Start();
		
		/* Display the message */
		LCD_Char_Position(0,0);
		LCD_Char_PrintString("Press SWITCH SW2");
	}
    
	/* Set USE_START_PIN macro to 0 if PSoC 5LP is not used as host
	   microcontroller */
	if(USE_START_PIN == 1)
	{
		while (Pin_Start_Read() == 1);
	}
	
	/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
	if(USE_LCD == 1)
	{
		/* Clear Character LCD  */
		LCD_Char_ClearDisplay();
		
		/* Display the message */
	    LCD_Char_Position(0,0);
	    LCD_Char_PrintString("Programming PSoC4");
	}
    /* Start the HSSP Programming and store the status */
    programResult = ProgramDevice();
    
	/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
	if(USE_LCD)
	{
	    /* Character LCD will display the status of HSSP Programming  */
	    LCD_Char_ClearDisplay();
	}
    
	/* HSSP completed successfully */
    if(programResult == SUCCESS) 
    {
		/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
        if(USE_LCD)
		{
			LCD_Char_Position(0,0);
        	LCD_Char_PrintString("HSSP Success");
    	}
	}
	
	/* HSSP Failure */
    else
    {
		/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
        if(USE_LCD == 1)
		{
			/* Display the step number where the HSSP failed */
	        LCD_Char_Position(0,0);
	        LCD_Char_PrintString("HSSP Fail Step");
	        LCD_Char_PrintInt8(currentStep);
		}
        		
        /* Get the HSSP error status and display on THE LCD */
        errorStatus = ReadHsspErrorStatus();
        
		/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
		if(USE_LCD == 1)
		{
	        LCD_Char_Position(1,0);
	        LCD_Char_PrintString("Err ");
	        LCD_Char_PrintInt8(errorStatus);
		}
        
        /* If the errorStatus contains THE SROM_TIMEOUT_ERROR error condition,
           read the Status Code returned by CPUSS_SYSARG register and display
		   on THE LCD */
        if(errorStatus & SROM_TIMEOUT_ERROR)
        {
            sromErrorStatus = ReadSromStatus();
            
			/* Set USE_LCD macro to 0 if PSoC 5LP is not used as host microcontroller */
			if(USE_LCD)
			{
				LCD_Char_PrintString(" SROM ");
				LCD_Char_PrintInt8(sromErrorStatus);
			}
        }
    }

    for( ; ; )
    {
        /* Do Nothing */
    }
}

/******************************************************************************
* Function Name:ProgramDevice
*******************************************************************************
* Summary:
*  This function sequentially calls all the functions required to program a
*  PSoC 4/PSoC Analog Coprocessor. These functions are defined in ProgrammingSteps.h.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - All the programming steps executed successfully
*  FAILURE - HSSP programming fails in any one of the programming step
*
******************************************************************************/
unsigned char ProgramDevice(void)
{
    currentStep = 1;
       
    if(DeviceAcquire() == FAILURE)     
        return(FAILURE);
    
    currentStep++;
    if(VerifySiliconId() == FAILURE)    
        return(FAILURE);
    
    currentStep++;
    if(EraseAllFlash() == FAILURE)             
        return(FAILURE);
 
    currentStep++;
    if(ChecksumPrivileged() == FAILURE)                    
        return(FAILURE);
 
    currentStep++;
    if(ProgramFlash() == FAILURE)          
        return(FAILURE);
   
    currentStep++;
    if(VerifyFlash() == FAILURE)       
        return(FAILURE);
   
    currentStep++;
    if(ProgramProtectionSettings() == FAILURE) 
        return(FAILURE);
 
    currentStep++;
    if(VerifyProtectionSettings() == FAILURE)
        return(FAILURE);
   
    currentStep++;
    if(VerifyChecksum() == FAILURE) 
        return(FAILURE);
        
    ExitProgrammingMode();
        
	/* All the steps were completed successfully */
    return(SUCCESS);
}

/* End Of File [] */
