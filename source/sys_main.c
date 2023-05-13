/** @file sys_main.c 
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
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
#include "bl_run_target.h"
#include "bl_watchdog.h"

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
	int delay = 1000;
	int target_counter = 10;

    for(;;){
    	set_value(PIN_RED, red);
    	red = toggle(red);
    	vTaskDelay(delay);
//    	if(--target_counter < 0){
//   		softReset();
//    	}
    }
}

void yellowTask(void *pvParameters)
{
	int yellow = 1;
	int delay = 600;

    for(;;){
    	set_value(PIN_YELLOW, yellow);
    	yellow = toggle(yellow);
    	vTaskDelay(delay);
    }
}

void greenTask(void *pvParameters)
{
	int green = 1;
	int delay = 200;

    for(;;){
    	kickWatchdog();
    	set_value(PIN_GREEN, green);
    	green = toggle(green);
    	vTaskDelay(delay);
    }
}

/* USER CODE END */

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

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
