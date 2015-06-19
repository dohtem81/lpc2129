/*****************************************************************************
 *   target.c:  Target C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.13  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include "lpc21xx.h"
#include "type.h"
#include "target.h"

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a necessary 
**						place, change it as needed
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetInit(void)
{
    /* Add your codes here */
    return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
// void GPIOResetInit( void ) - mthomas, add static, avoid missing proto warning
static void GPIOResetInit( void )
{
	/* Reset all GPIO pins to default: primary function */
    /*PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    PINSEL3 = 0x00000000;
    PINSEL4 = 0x00000000;
    PINSEL5 = 0x00000000;
    PINSEL6 = 0x00000000;
    PINSEL7 = 0x00000000;
    PINSEL8 = 0x00000000;
    PINSEL9 = 0x00000000;
    PINSEL10 = 0x00000000;
    
    IODIR0 = 0x00000000;
    IODIR1 = 0x00000000;
	IOSET0 = 0x00000000;
    IOSET1 = 0x00000000;
    
    FIO0DIR = 0x00000000;
    FIO1DIR = 0x00000000;
    FIO2DIR = 0x00000000;
    FIO3DIR = 0x00000000;
    FIO4DIR = 0x00000000;
    
    FIO0SET = 0x00000000;
    FIO1SET = 0x00000000;
    FIO2SET = 0x00000000;
    FIO3SET = 0x00000000;
    FIO4SET = 0x00000000;
    return;*/
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL ( void )
{

    PLLCON = 0;				/* Disable PLL, disconnected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    PLLCFG = 0x3 + (0x3 << 5);
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    PLLCON = 1;				/* Enable PLL, disconnected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    PLLCON = 3;				/* enable and connect */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

	return;
}

/******************************************************************************
** Function name:		TargetResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**						function; User may change it as needed, but may not 
**						deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetResetInit(void)
{
	MEMMAP	=	0x1;

	ConfigurePLL();

    return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
