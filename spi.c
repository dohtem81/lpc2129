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

#include "spi.h"
#include "lpc21xx.h"

//**************************************************************************/
//
//	initializes selected SPI
//	currently only SPI0 implemented
//	PARAMETERS:
//		int port	-	which SPI to be initialized
//
//**************************************************************************/
void spi_initialize (int port){
	if (port == SETUP_SPI0) {
		PINSEL0 	|= 	PINSEL_SPI0_SCK +
						PINSEL_SPI0_MISO +
						PINSEL_SPI0_MOSI +
						PINSEL_SPI0_SSEL0 ;
		PCONP 		|=	PCONP_SPI0 ;

		SPI_SPCR	=	0x1 << 5 ;	//in master mode
		/* in master mode this value min 8;
		 * rate = PCLK / SPCCR, where PCLK = CCLK / APBDIV
		 * as default APBDIV = 4 (register = 0)
		 * PCLK = ~60MHz / 4 = 15MHz
		 * rate = 15MHz / 8 = 1.875 MHz
		 */
		SPI_SPCCR	=	0x20;
	}

}


//**************************************************************************/
//
//	writes data (future: into selected SPI)
//	currently only SPI0 implemented
//	PARAMETERS:
//		int port	-	which SPI to be initialized
//		short *data	-	pointer to data to be written to SPI
//		short length-	length of the message (bytes)
//
//**************************************************************************/
void spi_write (int port, unsigned char *data, unsigned short length){
	unsigned short idx; //index pointer

	for (idx = 0; idx < length; idx++){
		SPI_SPDR = *data++;
		while (!(SPI_SPSR));
	}
}

//**************************************************************************/
//
//	reads data (future: into selected SPI)
//	currently only SPI0 implemented
//	PARAMETERS:
//		int port	-	which SPI to be initialized
//		short *data	-	pointer for data to be read from SPI
//
//**************************************************************************/
void spi_read (int port, unsigned short *data, unsigned short length){
	unsigned short idx, status;

	status = SPI_SPSR;

	for (idx = 0; idx < length; idx++){
		while(!(SPI_SPSR));
		*data++		=	SPI_SPDR ;
	}
}
