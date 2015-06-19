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

#ifndef SPI_H_
#define SPI_H_

#define SETUP_SPI0				0
#define SETUP_SPI1				1 //to be implemented

#define PINSEL_SPI0_SCK			0x01 << 8
#define PINSEL_SPI0_MISO		0x01 << 10
#define	PINSEL_SPI0_MOSI		0x01 << 12
#define PINSEL_SPI0_SSEL0		0x01 << 14
#define PCONP_SPI0				0x1 << 8


// function declarations
void spi_initialize (int);
void spi_write (int, unsigned char *, unsigned short);
void spi_read  (int, unsigned short *, unsigned short);

#endif /* SPI_H_ */
