/*
 * dynamixel.h
 *
 *  Created on: Jan 18, 2017
 *      Author: gregorio626
 */

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

#include <vector>

class Packet {
private:
	std::vector<unsigned char> m_packet;

	/*! \brief creates the packet header
	 * 			Responsible for setting the header, the motor id value, and reserving for the length value
	 * @param iMotorId The id of the motor that the packet is being generated for
	 */
	void beginPacket(int iMotorId);

	/*! \brief Creates the packet footer.
	 * 			Responsible for setting the length of the packet, as well as the checksum
	 */
	void endPacket();

	/*! \brief Get the low byte from a number greater than 255
	 * @param iWord The value being split into 2 bytes
	 */
	unsigned char lowByte(int iWord);

	/*! \brief Get the high byte from a number greater than 255
	 * @param iWord The value being split into 2 bytes
	 */
	unsigned char highByte(int iWord);

	/*! \brief Calculate the checksum for the packet being generated
	 * @param buffer A pinter to the current packet as an array
	 */
	unsigned char getChecksum(const unsigned char * buffer);

public:

	/*! \brief Generates a PING instruction packet
	 * @param iMotorId The id of the motor that the packet is being generated for
	 */
	const std::vector<unsigned char>& makePing(int iMotorId);

	/*! \brief Generates a READ instruction packet for reading 1 byte
	 * @param iMotorId The id of the motor that the packet is being generated for
	 * @param iRegister The register being read
	 */
	const std::vector<unsigned char>& makeReadByte(int iMotorId, int iRegister);

	/*! \brief Generates a READ instruction packet for reading 2 bytes
	 * @param iMotorId The id of the motor that the packet is being generated for
	 * @param iStartRegister The L register being read
	 */
	const std::vector<unsigned char>& makeReadWord(int iMotorId, int iStartRegister);


	/*! \brief Generates a WRITE instruction packet for writing 1 byte
	 * @param iMotorId The id of the motor that the packet is being generated for
	 * @param iRegister The register being written to
	 * @param iValue The value being written to the register
	 */
	const std::vector<unsigned char>& makeWriteByte(int iMotorId, int iRegister, int iValue);

	/*! \brief Generates a WRITE instruction packet for writing 2 bytes
	 * @param iMotorId The id of the motor that the packet is being generated for
	 * @param iStartRegister The L register being written to
	 * @param iValue The value being written to the registers
	 */
	const std::vector<unsigned char>& makeWriteWord(int iMotorId, int iStartRegister, int iValue);
};



#endif /* DYNAMIXEL_H_ */
