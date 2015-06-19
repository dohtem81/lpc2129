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

#include "lpc21xx.h"
#include "ENC28J60.h"
#include "spi.h"
#include "type.h"


//**************************************************************************/
//
//	(inline) for communication
//	PARAMETERS:
//		char	flag		; TRUE/FALSE if pin should be 0 or 1 (CS)
//
//**************************************************************************/
inline void enc_selMac(unsigned char flag){
	(flag == TRUE) ? (IO0CLR = 0x00000100) : (IO0SET = 0x00000100) ;
}


//**************************************************************************/
//
//	writes control register
//	PARAMETERS:
//		short	address	; addr to register to be written
//		short	data		; data to be written into register
//
//**************************************************************************/
void enc_writeCtrlReg(unsigned char address, unsigned char data){
	unsigned char ch_data[2];

	ch_data[0] = ((OPCODE_WCR << 5) | address);
	ch_data[1] = data;

	enc_selMac(TRUE);
	spi_write(0, ch_data, 2);
	enc_selMac(FALSE);
}


//**************************************************************************/
//
//	writes PHY register
//	PARAMETERS:
//		short	address		; PHY addr to register to be written
//		int		data		; data to be written into register H&L register
//
//**************************************************************************/
void enc_writePHYReg(unsigned char address, unsigned short data){
	enc_writeCtrlReg(MIREGADR, address);
	enc_writeCtrlReg(MIWRL, (unsigned char)(data & 0xff));
	enc_writeCtrlReg(MIWRH, (unsigned char)(data >> 8));
}


//**************************************************************************/
//
//	selectd bank for cntrol register
//	PARAMETERS:
//		short	bankNumber
//
//**************************************************************************/
void enc_bankSelect(unsigned char bankNumber){
	unsigned char ch_data[2];

	ch_data[0] = (unsigned char)((OPCODE_WCR << 5) | ECON1);
	ch_data[1] = bankNumber;

	enc_selMac(TRUE);
	spi_write(0, ch_data, 2);
	enc_selMac(FALSE);
}


//**************************************************************************/
//
//	write MAC register
//	PARAMETERS:
//		short*	data		; pointer to data
//		short	length		; length of data (in bytes)
//
//**************************************************************************/
void enc_writeMACReg(unsigned char *data, unsigned short length){
	unsigned char jobCode = OPCODE_WBM;
	unsigned short idx;

	enc_selMac(TRUE);
	spi_write(0, &jobCode, 1);
	spi_write(0, data, length);
	enc_selMac(FALSE);
}



//**************************************************************************/
//
//	initializes ENC interface
//	PARAMETERS:
//		void
//
//**************************************************************************/
void enc_initialize(void){
	short data;
	unsigned char bOp = OPCODE_RST;

	//reset MAC
	enc_selMac(TRUE);
	spi_write(0, &bOp, 1);
	enc_selMac(FALSE);

	//select bank 0
	enc_bankSelect(CR_BANK0);
	// setting buffers
	enc_writeCtrlReg(ERXSTL, (unsigned char)(RXSTART & 0xff));
	enc_writeCtrlReg(ERXSTH, (unsigned char)(RXSTART >> 8));

	enc_writeCtrlReg(ERXNDL, (unsigned char)(RXEND & 0xff));
	enc_writeCtrlReg(ERXNDH, (unsigned char)(RXEND >> 8));

	enc_writeCtrlReg(ERXRDPTL, (unsigned char)(RXSTART & 0xff));
	enc_writeCtrlReg(ERXRDPTH, (unsigned char)(RXSTART >> 8));

	//setting up recieve filters
	// no filter to be set at this time
	//no point in using bank 1
	//enc_bankSelect(CR_BANK1);

	//select bank 2 for MAC initialization
	enc_bankSelect(CR_BANK2);

	//MACON1 - enable recieve, all not filtered into buffer
	enc_writeCtrlReg(MACON1, (unsigned char)(MACON1_MAXREN));// + MACON1_PASSALL + MACON1_RXPAUS + MACON1_TXPAUS));

	//MACON3 -
	enc_writeCtrlReg(MACON3, (unsigned char)(MACON3_FULDPX + MACON3_TXCRCEN + (0x1<<5)));

	//MAMXFL
	enc_writeCtrlReg(MAMXFLL, (unsigned char)(MAXFRAMELENGTH & 0xff));
	enc_writeCtrlReg(MAMXFLL, (unsigned char)(MAXFRAMELENGTH >> 8));

	//MABPIG - MAC back-to-back interpacked gap regiser
	//0x12 when full duplex off, 0x15 when full duplex on
	enc_writeCtrlReg(MABBIPG, (unsigned char)0x12);
	enc_writeCtrlReg(MAIPGL , (unsigned char)0x12);
	enc_writeCtrlReg(MAIPGH , (unsigned char)0x0c);

	//set PHCON register
	//setup MAC address
	enc_bankSelect(CR_BANK3);
	enc_writeCtrlReg(MAADR1, (unsigned char)(ETH_MAC1 & 0xff));
	enc_writeCtrlReg(MAADR2, (unsigned char)(ETH_MAC1 >> 8));
	enc_writeCtrlReg(MAADR3, (unsigned char)(ETH_MAC2 & 0xff));
	enc_writeCtrlReg(MAADR4, (unsigned char)(ETH_MAC2 >> 8));
	enc_writeCtrlReg(MAADR5, (unsigned char)(ETH_MAC3 & 0xff));
	enc_writeCtrlReg(MAADR6, (unsigned char)(ETH_MAC3 >> 8));

	enc_writePHYReg(PHCON1, (unsigned char)0x0);
	enc_writePHYReg(PHCON2, (unsigned char)PHCON2_HDLDIS);
	enc_writeCtrlReg(ECON1, (unsigned char)ECON1_RXEN);

}

//**************************************************************************/
//
//	post data on ethernet
//	PARAMETERS:
//		short*	data		; pointer to data
//		short	length		; length of data
//
//**************************************************************************/
void enc_postData(unsigned char *data, unsigned short length){
	unsigned char *pointerAddress;

	enc_bankSelect(CR_BANK0);
	//sets up write buffer
	enc_writeCtrlReg(ETXSTL, (unsigned char)(TXSTART & 0xff));
	enc_writeCtrlReg(ETXSTH, (unsigned char)(TXSTART >> 8));

	enc_writeCtrlReg(EWRPTL, (unsigned char)(TXSTART & 0xff));
	enc_writeCtrlReg(EWRPTH, (unsigned char)(TXSTART >> 8));

	//write control byte
	unsigned char byte;

	enc_selMac(TRUE);
	byte = OPCODE_WBM;
	spi_write(0, &byte, 1);
	spi_write(0, data, length);
	enc_selMac(FALSE);

	//sets up end of packet pointer to length + 1 with respect to TXSTART
	pointerAddress = TXSTART;
	pointerAddress = &pointerAddress[length+1];
	enc_writeCtrlReg(ETXNDL, (unsigned char)(*pointerAddress & 0xff));
	enc_writeCtrlReg(ETXNDH, (unsigned char)(*pointerAddress >> 8));

	//start transmission by setting ECON1.TXRTS
	enc_writeCtrlReg(ECON1, ECON1_TXRTS);

}


