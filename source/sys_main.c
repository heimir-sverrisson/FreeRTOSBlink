/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
/* Include FreeRTOS scheduler files */
#include "FreeRTOS.h"
#include "os_task.h"

/* Include HET header file - types, definitions and function declarations for system driver */
#include "het.h"
#include "gio.h"

/* Define Task Handles */
xTaskHandle xTask1Handle;

#define PIN_RED 0
#define PIN_YELLOW 1
#define PIN_GREEN 2

void set_value(int pin, int value){
	if(value == 0){
		hetREG1->DOUT &= ~(1 << pin);
	} else {
		hetREG1->DOUT |= (1 << pin);
	}
}

int toggle(int value){
	return (value == 1) ? 0 : 1;
}

void redTask(void *pvParameters)
{
	int red = 1;

    for(;;){
    	set_value(PIN_RED, red);
    	red = toggle(red);
    	vTaskDelay(1000);
    }
}

void yellowTask(void *pvParameters)
{
	int yellow = 1;

    for(;;){
    	set_value(PIN_YELLOW, yellow);
    	yellow = toggle(yellow);
    	vTaskDelay(600);
    }
}

void greenTask(void *pvParameters)
{
	int green = 1;

    for(;;){
    	set_value(PIN_GREEN, green);
    	green = toggle(green);
    	vTaskDelay(200);
    }
}

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
	// All three pins are output
	hetREG1->DIR |= (1 << PIN_RED);
	hetREG1->DIR |= (1 << PIN_YELLOW);
	hetREG1->DIR |= (1 << PIN_GREEN);

	// Turn all LED's off
	set_value(PIN_RED, 1);
	set_value(PIN_YELLOW, 1);
	set_value(PIN_GREEN, 1);

    if (xTaskCreate(redTask,"RedTask", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle) != pdTRUE){
        while(1); // Error
    }
    if (xTaskCreate(yellowTask,"YellowTask", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle) != pdTRUE){
        while(1); // Error
    }
    if (xTaskCreate(greenTask,"GreenTask", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle) != pdTRUE){
        while(1); // Error
    }

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Run forever */
    while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
