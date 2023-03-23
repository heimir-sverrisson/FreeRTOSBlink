/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
/*
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    KERNEL (RX)  : origin=0x00000020 length=0x00008000
    FLASH0  (RX) : origin=0x00008020 length=0x000FFFE0 - 0x8000
    STACKS  (RW) : origin=0x08000000 length=0x00001500
    KRAM    (RW) : origin=0x08001500 length=0x00000800
    RAM     (RW) : origin=0x08001500 + 0x800 length=0x0001EB00 - 0x800
*/

	VECTORS	(X)		: origin=0x00010100 length=0x00000040
	KERNEL	(RX)	: origin=0x00010140 length=0x00008000
	FLASH0	(RX)	: origin=0x00018140 length=0x000E7EC0

	RUNTARGET (RW)  : origin=0x08000000 length=0x00000010
    STACKS  (RW)    : origin=0x08000010 length=0x000014F0
    KRAM	(RW)	: origin=0x08001500 length=0x00000800
	RAM	(RW)		: origin=0x08001D00 length=0x0001E2E0
	RAMVECTORS(RWX) : origin=0x0801FFE0 length=0x00000020


/* USER CODE BEGIN (2) */
/* USER CODE END */
}

/* USER CODE BEGIN (3) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
    // FreeRTOS kernel in protected flash
    .kernelTEXT : {} > KERNEL
    .cinit      : {} > KERNEL
    .pinit      : {} > KERNEL
    // Rest of code to user mode flash region
    .text       : {} > FLASH0
    .const      : {} > FLASH0
    .ovly		: {} > FLASH0
    .runTarget   : {} > RUNTARGET, type = NOINIT
	// FreeRTOS kernel data in protected RAM
	.kernelBSS  : {} > KRAM
	.kernelHEAP : {} > RAM
    .bss        : {} > RAM
    .data       : {} > RAM
    .ramIntvecs  : {} load=FLASH0, run=RAMVECTORS, palign=8, table(ram_undef)

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (6) */
/* USER CODE END */
/*----------------------------------------------------------------------------*/
