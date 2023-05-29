/*
 *   This file is part of lpc2129.
 *
 *   lpc2129 is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   lpc2129 is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with lpc2129.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   For any comment or suggestion please contact the author of that software
 *   at pedziwiatr.piotr@gmail.com
 */

/* *********************************************************
               Function declarations
  ********************************************************* */

void Initialize(void);
void feed(void);

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

/**********************************************************
                  Header files
 **********************************************************/
#include "lpc21xx.h"
#include "spi.h"
#include "ENC28J60.h"

#define   ST_LED_OFF     IO1CLR |= 0x02000000
#define   ST_LED_ON    IO1SET |= 0x02000000



unsigned char frame[42];
unsigned short *ptr; //42 bytes is ARP frame


/**********************************************************
                       MAIN
**********************************************************/

int	main (void) {

	long		j;			// loop counter (stack variable)
	PINSEL0 =	0x0; //done in init
	PINSEL1 =	0x0; //done in init
	IO0DIR	=	0x00000102 ;//0x1 << 1;
	IO0CLR	=	0x1 << 1;


	IO0SET	=	0x1 << 1;
	for (j = 0; j < 50000; j++ );		// wait 500 msec
	IO0CLR	=	0x1 << 1;
	for (j = 0; j < 50000; j++ );

	// Initialize the system
	Initialize();

	// initialize SPI0 interface
	spi_initialize(SETUP_SPI0);
	enc_initialize();

	// endless loop to toggle the RED LED
	while (1)
	{
		IO0SET	=	0x1 << 1;
		for (j = 0; j < 150000; j++ );		// wait 500 msec
		IO0CLR	=	0x1 << 1;
		for (j = 0; j < 150000; j++ );
		enc_postData(frame, 42);
	}
}



/**********************************************************
                      Initialize
**********************************************************/

#define PLOCK 0x400

void Initialize(void)
{
	//M=3(4?),P=1(2?) PLLfreq = 58.9824 Mhz, CCLK = 14,7456 Mhz
	PLLCFG = 0x00000023;
	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	// Enable the PLL
	PLLCON |= 0x01;
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	//while(!(PLLSTAT & PLOCK));  // Wait for PLL to lock

	//Init MAM & Flash memory fetch
	MAMCR = 0x02;
	MAMTIM = 0x04;

	// configure peripherals speed
	//VPBDIV = 0x01; //pclk = cclk

	//GPIO init
	//ST_LED_OFF;

	//PINSEL0 = 0; //P0 lower 16 bits all GPIO
	//PINSEL1 = 0; //P0 upper 16 bits all GPIO

	//IODIR in binary 0000 0010 0000 0000 0000 0000 0000 0000     ...P1.25 is the LED
	//IO1DIR = 0x02000000;

	//init ARP packet

	//sets pointer at begining fo the frame
	ptr 		=	(unsigned short *)frame;
	//first 3 words is destination MAC - broadcast	[0-2]
	*(ptr++)		=	0xffff;
	*(ptr++)		=	0xffff;
	*(ptr++)		=	0xffff;

	//3 wrods source MAC (this station)	[3-5]
	*(ptr++)		=	ETH_MAC1;
	*(ptr++)		=	ETH_MAC2;
	*(ptr++)		=	ETH_MAC3;

	//sets type as ARP	[6]
	*(ptr++)		=	TYPE_ARP;

	//hardware type - ethernet	[7]
	*(ptr++)		=	ARP_ETH;

	//protocol type IP	[8]
	*(ptr++)		=	TYPE_IP;

	//hardware size and protocol size (contant)		[9]
	*(ptr++)		=	ARP_HDPS;

	//opcode (is gratuitous)	[10]
	*(ptr++)		=	0x0001;

	//sorce MAC again...	[11-13]
	*(ptr++)		=	ETH_MAC1;
	*(ptr++)		=	ETH_MAC2;
	*(ptr++)		=	ETH_MAC3;

	//source IP address		[14-15]
	*(ptr++)		=	(IP1 << 8) | IP2;
	*(ptr++)		=	(IP3 << 8) | IP4;

	//destination MAC - this time 0s	[16-18]
	*(ptr++)		=	0x0000;
	*(ptr++)		=	0x0000;
	*(ptr++)		=	0x0000;

	//destination IP
	*(ptr++)		=	(192 << 8) + 168;
	*ptr			=	(2 << 8) + 5;
}


/*  Stubs for various interrupts (may be replaced later)  */
/*  ----------------------------------------------------  */

void IRQ_Routine (void) {
	//while (1) ;
}

void FIQ_Routine (void)  {
	//while (1) ;
}


void SWI_Routine (void)  {
	//while (1) ;
}


void UNDEF_Routine (void) {
	//while (1) ;
}
