/*
 * ENC28J60.h
 *
 *  Created on: Feb 12, 2011
 *      Author: strus
 */

#ifndef ENC28J60_H_
#define ENC28J60_H_

//bank selection, bits 1:0
//used by ECON1
#define	CR_BANK0		0x00
#define	CR_BANK1		0x01
#define	CR_BANK2		0x10
#define	CR_BANK3		0x11
#define	ECON1_TXRTS		0x80
#define	ECON1_RXEN		0x04

//OPCODEs - operation codes
#define OPCODE_RCR		0x00
#define OPCODE_RBR		0x01
#define OPCODE_WCR		0x02
#define	OPCODE_WBM		0x7A
#define OPCODE_BFS		0x04
#define OPCODE_BFC		0x05
#define	OPCODE_SRC		0x07
#define	OPCODE_RST		0xff

#define ARG_RBM			0x1a
#define ARG_WBM			0x1a
#define	ARG_SRC			0x1f

#define LEN_RCR			0x08
#define LEN_RBM			0x08
#define LEN_SRC			0x08

//control registers
// BANK 0
#define	ERDPTL		0x00
#define	ERDPTH		0x01
#define	EWRPTL		0x02
#define	EWRPTH		0x03
#define	ETXSTL		0x04
#define	ETXSTH		0x05
#define	ETXNDL		0x06
#define	ETXNDH		0x07
#define	ERXSTL		0x08
#define	ERXSTH		0x09
#define	ERXNDL		0x0a
#define	ERXNDH		0x0b
#define	ERXRDPTL	0x0c
#define	ERXRDPTH	0x0d
#define	ERXWRPTL	0x0e
#define	ERXWRPTH	0x0f
#define	EDMASTL		0x10
#define	EDMASTH		0x11
#define	EDMANDL		0x12
#define	EDMANDH		0x13
#define	EDMADSTL	0x14
#define	EDMADSTH	0x15
#define	EDMACSL		0x16
#define	EDMACSH		0x17
//		RESERVED
#define	EIE			0x1b
#define	EIR			0x1c
#define	ESTAT		0x1d
#define	ECON2		0x1e
#define	ECON1		0x1f

// BANK 1
#define	EHT0		0x00
#define	EHT1		0x01
#define	EHT2		0x02
#define	EHT3  		0x03
#define	EHT4  		0x04
#define	EHT5  		0x05
#define	EHT6  		0x06
#define	EHT7  		0x07
#define	EPMM0 		0x08
#define	EPMM1 		0x09
#define	EPMM2 		0x0a
#define	EPMM3 		0x0b
#define	EPMM4   	0x0c
#define	EPMM5   	0x0d
#define	EPMM6   	0x0e
#define	EPMM7   	0x0f
#define	EPMCSL 		0x10
#define	EPMCSH 		0x11
//	RESERVED
#define	EPMOL   	0x14
#define	EPMOH   	0x15
//	RESERVED
#define	ERXFCON		0x18
#define	EPKTCNT		0x19
//		RESERVED
#define	EIE 		0x1b
#define	EIR  		0x1c
#define	ESTAT		0x1d
#define	ECON2		0x1e
#define	ECON1		0x1f

// BANK 2
#define	MACON1 		0x00
//	RESERVED
#define	MACON3		0x02
#define	MACON4		0x03
#define	MABBIPG		0x04
//	RESERVED
#define	MAIPGL		0x06
#define	MAIPGH		0x07
#define	MACLCON1	0x08
#define	MACLCON2	0x09
#define	MAMXFLL		0x0a
#define	MAMXFLH		0x0b
//	reserved
#define	MICMD  		0x12
//	RESERVED
#define	MIREGADR	0x14
//	RESERVED
#define	MIWRL  		0x16
#define	MIWRH  		0x17
#define	MIRDL  		0x18
#define	MIRDH  		0x19
//		RESERVED
#define	EIE 		0x1b
#define	EIR  		0x1c
#define	ESTAT		0x1d
#define	ECON2		0x1e
#define	ECON1		0x1f


// BANK 3
#define	MAADR5		0x00
#define	MAADR6		0x01
#define	MAADR3		0x02
#define	MAADR4		0x03
#define	MAADR1		0x04
#define	MAADR2		0x05
#define	EBSTSD		0x06
#define	EBSTCON		0x07
#define	EBSTCSL		0x08
#define	EBSTCSH		0x09
#define	MISTAT		0x0a
//	RESERVED
#define	EREVID 		0x12
//	RESERVED
#define	ECOCON  	0x15
//	RESERVED
#define	EFLOCON		0x17
#define	EPAUSL 		0x18
#define	EPAUSH 		0x19
//		RESERVED
#define	EIE 		0x1b
#define	EIR  		0x1c
#define	ESTAT		0x1d
#define	ECON2		0x1e
#define	ECON1		0x1f


// initialisation data
//----------------------
// RX buffer
#define TXSTART		0x0000
#define RXSTART		0x1a19
#define RXEND		0x1ff0

//values for ERXFCON (filter)
//=============================
#define	ERXFCON_BCEN	(0x1)
/* When ANDOR = 1:
1 = Packets must have a destination address of FF-FF-FF-FF-FF-FF or they will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Packets which have a destination address of FF-FF-FF-FF-FF-FF will be accepted
0 = Filter disabled */
#define	ERXFCON_MCEN	(0x1<<1)
/* When ANDOR = 1:
1 = Packets must have the Least Significant bit set in the destination address or they will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Packets which have the Least Significant bit set in the destination address will be accepted
0 = Filter disabled */
#define	ERXFCON_HTEN	(0x1<<2)
/* When ANDOR = 1:
1 = Packets must meet the Hash Table criteria or they will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Packets which meet the Hash Table criteria will be accepted
0 = Filter disabled */
#define	ERXFCON_MTEN	(0x1<<3)
/* When ANDOR = 1:
1 = Packets must be Magic Packets for the local MAC address or they will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Magic Packets for the local MAC address will be accepted
0 = Filter disabled */
#define	ERXFCON_PMEN	(0x1<<4)
/* When ANDOR = 1:
1 = Packets must meet the Pattern Match criteria or they will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Packets which m */
#define	ERXFCON_CRCEN	(0x1<<5)
/* 1 = All packets with an invalid CRC will be discarded
0 = The CRC validity will be ignored */
#define	ERXFCON_ANDOR	(0x1<<6)
/* 1 = AND: Packets will be rejected unless all enabled filters accept the packet
0 = OR: Packets will be accepted unless all enabled filters reject the packet */
#define	ERXFCON_UCEN	(0x1<<7)
/* When ANDOR = 1:
1 = Packets not having a destination address matching the local MAC address will be discarded
0 = Filter disabled
When ANDOR = 0:
1 = Packets with a destination address matching the local MAC address will be accepted
0 = Filter disabled */


//values for MACON1
//=============================
#define MACON1_MAXREN		0x1		//1 = Enable packets to be received by the MAC
#define MACON1_PASSALL		0x2		//1 = Control frames received by the MAC will be
									//written into the receive buffer if not filtered out
#define MACON1_RXPAUS		0x4		//1 = Inhibit transmissions when pause control frames
									//are received (normal operation)
#define MACON1_TXPAUS		0x8		//1 = Allow the MAC to transmit pause control frames
									//(needed for flow control in full duplex)

//values for MACON3
//=============================
#define MACON3_FULDPX		0x01	//1 = MAC will operate in Full-Duplex mode.
									//PDPXMD bit must also be set.
#define MACON3_FRMLEN		0x02	//1 = The type/length field of transmitted and
									//received frames will be checked. If it represents
									//a length, the frame size will be compared and mismatches
									//will be reported in the transmit/receive status vector.
#define MACON3_HFRMEN		0x04	//1 = Frames of any size will be allowed to be transmitted
									//and received
#define MACON3_PHDREN		0x08	//1 = Frames presented to the MAC contain a 4-byte proprietary
//header which will not be used when calculating the CRC
#define MACON3_TXCRCEN		0x01	//1 = MAC will append a valid CRC to all frames transmitted
									//regardless of PADCFG bits. TXCRCEN must be set if the PADCFG
									//bits specify that a valid CRC will be appended.


//values for MACON4
//=============================
#define MACON4_NOBKOFF		0x01	//1 = After any collision, the MAC will immediately
									//begin retransmitting
#define MACON4_BPEN			0x02	//1 = After incidentally causing a collision during
									//backpressure, the MAC will immediately begin retransmitting
#define MACON4_DEFER		0x04	//1 = When the medium is occupied, the MAC will wait
									//indefinitely for it to become free when attempting
									//to transmit (use this setting for IEEE 802.3TM compliance)


//PHY addresses
//=============================
#define	PHCON1				0x00
#define PHSTAT1				0x01
#define PHID1				0x02
#define PHID2				0x03
#define PHCON2				0x10
#define PHSTAT2				0x11
#define PHIE				0x12
#define PHIR				0x13
#define PHLCON				0x14

//PHYSTAT registers
//=============================
#define	PHSTAT1_JBSTAT		0x0002	//1 = PHY has detected a transmission meeting the jabber
									//criteria since PHSTAT1 was last read
#define	PHSTAT1_LLSTAT		0x0004	//1 = Link is up and has been up continously since
									//PHSTAT1 was last read
#define	PHSTAT1_PHDPX		0x0800	//1 = PHY is capable of operating at 10 Mbps in Half-Duplex
									//mode (this bit is always set)
#define	PHSTAT1_PFDPX		0x1000	//1 = PHY is capable of operating at 10 Mbps in Full-Duplex
									//mode (this bit is always set)

#define	PHSTAT2_PLRITY		0x0020	//1 = The polarity of the signal on TPIN+/TPIN- is reversed
#define	PHSTAT2_DPXSTAT		0x0200	//1 = PHY is configured for full-duplex operation
									//(PHCON1<8> is set)
#define	PHSTAT2_LSTAT		0x0400	//1 = Link is up
#define	PHSTAT2_COLSTAT		0x0800	//1 = A collision is occuring
#define	PHSTAT2_RXSTAT		0x1000	//1 = PHY is receiving data
#define	PHSTAT2_TXSTAT		0x2000	//1 = PHY is transmitting data


//PHYCON registers
//=============================
#define	PHCON1_PDPXMD		0x0100
#define	PHCON1_PPWRSV		0x0800
#define	PHCON1_PLOOPBK		0x4000
#define	PHCON1_PRST			0x8000

#define	PHCON2_HDLDIS		0x0100
#define	PHCON2_JABBER		0x0400
#define	PHCON2_TXDIS		0x2000
#define	PHCON2_FRCLINK		0x4000

//TX Control Byte (per packet)
//=============================
#define TXCTRL_POVERRIDE	0x0001	//	1 = The values of PCRCEN, PPADEN and PHUGEEN will
									//	override the configuration defined by MACON3
#define TXCTRL_PCRCEN		0x0002	//	1 = A valid CRC will be calculated and attached to the frame
#define TXCTRL_PPADEN		0x0004	//	1 = The packet will be zero padded to 60 bytes if
									//	it is less than 60 bytes
#define TXCTRL_PHUGEEN		0x0008	//	1 = The packet will be transmitted in whole


//addresses
#define	MAXFRAMELENGTH		1518
#define ETH_MAC1	0x0011
#define ETH_MAC2	0x4353
#define ETH_MAC3	0xe48d

#define IP1			192
#define IP2			168
#define	IP3			2
#define	IP4			201

#define			TYPE_IP		0x0800
#define			TYPE_ARP	0x0806
#define			ARP_ETH		0x0001
#define			ARP_HDPS	0x0604

//functions
void enc_initialize(void);
void enc_bankSelect(unsigned char);
void enc_writeCtrlReg(unsigned char, unsigned char);
void enc_writePHYReg(unsigned char, unsigned short);
void enc_writeMACReg(unsigned char *, unsigned short);
inline void enc_selMac(unsigned char);
void enc_postData(unsigned char*, unsigned short);


#endif /* ENC28J60_H_ */
