/*
 * packet.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: gregorio626
 */

#include "dynamixel.h"

#define PKT_LENGTH		(3)
#define INST_PING 		(0x01)
#define INST_READ		(0x02)
#define INST_WRITE		(0x03)

unsigned char Packet::lowByte(int iWord) {
	unsigned short tmp;
	tmp = iWord & 0xff;

	return (unsigned char)tmp;//Why are we converting back to an int? can we just return the unsigned char?
}

unsigned char Packet::highByte(int iWord) {
	unsigned short tmp;
	tmp = iWord & 0xff00;
	tmp = tmp >> 8; //bit shift

	return (unsigned char)tmp; //Why are we converting back to an int? can we just return the unsigned char?
}

unsigned char Packet::getChecksum(const unsigned char * buffer) {
	unsigned char checksum = 0;
	int i;
	for (i = 2; i < (3 + buffer[PKT_LENGTH]); i++)
		checksum += buffer[i];
	return ~(checksum & 0xFF);
}

void Packet::beginPacket(int iMotorId) {
	m_packet.clear(); //Make sure the vector is empty
	m_packet.push_back(0xff); //header 0
	m_packet.push_back(0xff); //header 1
	m_packet.push_back((unsigned char) iMotorId); //the ID of Dynamixel which will receive Instruction Packet.
	m_packet.push_back(0x00);
}

void Packet::endPacket() {
	m_packet[PKT_LENGTH] = m_packet.size() - 3; //Set the length value
	m_packet.push_back(getChecksum(m_packet.data()));
}

const std::vector<unsigned char>& Packet::makePing(int iMotorId) {
	beginPacket(iMotorId); //Header, id, length
	m_packet.push_back(INST_PING); //Instruction
	endPacket();

	return m_packet;
}

const std::vector<unsigned char>& Packet::makeReadByte(int iMotorId, int iRegister) {
	beginPacket(iMotorId); //Header, id, length
	m_packet.push_back(INST_READ); //Instruction
	m_packet.push_back((unsigned char)iRegister); //Parameter 0
	m_packet.push_back(0x01); //Parameter 1(number of bytes to read)
	endPacket();//footer(checksum)

	return m_packet;
}

const std::vector<unsigned char>& Packet::makeReadWord(int iMotorId, int iStartRegister) {
	beginPacket(iMotorId); //Header, id, length
	m_packet.push_back(INST_READ); //Instruction
	m_packet.push_back(iStartRegister); //Parameter 0
	m_packet.push_back(0x02); //Parameter 1(number of bytes to read)
	endPacket();//footer(checksum)

	return m_packet;
}

const std::vector<unsigned char>& Packet::makeWriteByte(int iMotorId, int iRegister, int iValue) {
	beginPacket(iMotorId);//header, id, length
	m_packet.push_back(INST_WRITE);//instruction
	m_packet.push_back((unsigned char)iRegister);//register
	m_packet.push_back((unsigned char)iValue);//value
	endPacket();//footer(checksum)

	return m_packet;
}

const std::vector<unsigned char>& Packet::makeWriteWord(int iMotorId, int iStartRegister, int iValue) {
	beginPacket(iMotorId);//header, id, length
	m_packet.push_back(INST_WRITE);//instruction
	m_packet.push_back((unsigned char)iStartRegister);//register
	m_packet.push_back(lowByte(iValue));//value(Low byte)
	m_packet.push_back(highByte(iValue));//value(High byte)
	endPacket();//checksum

	return m_packet;
}



