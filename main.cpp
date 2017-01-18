/*
 * main.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: gregorio626
 */

#include "dynamixel.h"

#include <iostream>
#include <vector>

int main(int argc, char * argv[]) {
	std::vector<unsigned char> pkt;
	////WELCOME & PORT INTIALIZATION////
	std::cerr << "//////////////////////////////" << std::endl;
	std::cerr << "//----------Hexapod---------//" << std::endl;
	std::cerr << "//////////////////////////////" << std::endl << std::endl;
	Packet p;
	pkt = p.makeWriteByte(1, 3, 0);

	for(unsigned int ii = 0; ii < pkt.size(); ii++) {
		std::cerr << " " << (int)pkt.at(ii);
	}
	std::cerr << std::endl;

	return 0;
}


