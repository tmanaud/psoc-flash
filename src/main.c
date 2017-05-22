/******************************************************************************
*******************************************************************************
*  Project Name: A_Hssp_Programmer
*  Project Revision: 1.00
*  Software Version: PSoC Creator 3.2
*  Device Tested: CY8C5868AXI-LP035
*  Compilers Tested: ARM GCC 4.8.4
*  Related Hardware: CY8CKIT-050
******************************************************************************/

/******************************************************************************
* Project Description:
*
* main.c checks the result of ProgramDevice() function and if it returns
* SUCCESS, "HSSP Success" is displayed on the character LCD mounted on the
* PSoC 5LP kit. If ProgramDevice() returns failure, Step of failure, Reason
* of failure is displayed on the LCD. If the error is because of SROM, It
* displays the SROM error code.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* This file has the top level HSSP routines that should be called from main
   application code */
#include "ProgrammingSteps.h"

// GPIO library to access SDW input output pin
#include "gpio_lib.h"
#include "SWD_PhysicalLayer.h"

// Function which sequentially calls all the programming steps
unsigned char ProgramDevice(void);

/* Global variable which stores the current programming step under execution */
unsigned char currentStep;

int main(int argc, char * argv[])
{
	// Variable to store the result of HSSP operation
	unsigned char programResult;
	// Variable to store the HSSP Error status in case of failure
	unsigned char errorStatus;
	// Variable to store the SROM Error status if errorStatus contains SROM_TIMEOUT_ERROR
	unsigned char sromErrorStatus;
	if (sunxi_gpio_init()) {
		printf("sunxi_gpio_init ERROR\n");
		exit(-1);
	}


	printf("Programming PSoC4\n");
	// Start the HSSP Programming and store the status
	programResult = ProgramDevice();
	if (programResult == SUCCESS)	{	// HSSP completed successfully
		printf("HSSP Success\n");
	}
	else { // HSSP Failure
		printf("HSSP Fail Step %d\n", currentStep);
		/* Get the HSSP error status and display on THE LCD */
		errorStatus = ReadHsspErrorStatus();
		printf("ReadHsspErrorStatus Err %d \n", errorStatus);
		/* If the errorStatus contains THE SROM_TIMEOUT_ERROR error condition,
		   read the Status Code returned by CPUSS_SYSARG register and display
		   on THE LCD */
		if (errorStatus & SROM_TIMEOUT_ERROR) {
			sromErrorStatus = ReadSromStatus();
			printf(" SROM%d  ", sromErrorStatus);
		}
	}
	return sromErrorStatus;
}

/******************************************************************************
* Function Name: unsigned char ProgramDevice(void)
*******************************************************************************
* Summary:
*  This function sequentially calls all the functions required to program a
*  PSoC 4. These functions are defined in ProgrammingSteps.h.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - All the programming steps executed successfully
*  FAILURE - HSSP programming fails in any one of the programming step
*
******************************************************************************/
unsigned char ProgramDevice()
{
	currentStep = 0;

	currentStep++;
	printf("ProgramDevice : DeviceAcquire \n");
	if (DeviceAcquire() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : VerifySiliconId \n");
	if (VerifySiliconId() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : EraseAllFlash \n");
	if (EraseAllFlash() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : ChecksumPrivileged \n");
	if (ChecksumPrivileged() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : ProgramFlash \n");
	if (ProgramFlash() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : VerifyFlash \n");
	if (VerifyFlash() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : ProgramProtectionSettings \n");
	if (ProgramProtectionSettings() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : VerifyProtectionSettings \n");
	if (VerifyProtectionSettings() == FAILURE)
		return (FAILURE);

	currentStep++;
	printf("ProgramDevice : VerifyChecksum \n");
	if (VerifyChecksum() == FAILURE)
		return (FAILURE);

	printf("ProgramDevice : ExitProgrammingMode \n");
	ExitProgrammingMode();

	/* All the steps were completed successfully */
	return (SUCCESS);
}

/* End Of File [] */
