#include "Debug.h"


//        0  1  2  3   4   5  6       7        8         9     10    11
// Order: A, X, Y, PC, SP, P, Opcode, Operand, Start PC, peek, word, addr
void Debug::LogCPUStatus(uint16_t CPUStatus[12]) {
	if (LOG_CPU) {
		std::map<std::string, std::string> debugMap = FileManager::debugMap;

		// Extract the operand from the debug map
		std::stringstream operand;
		std::stringstream opcodeIndex;
		std::string opcode;
		opcodeIndex << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (CPUStatus[6]);
		if (debugMap.find(opcodeIndex.str()) == debugMap.end()) {
			printf("Couldn't find string %s\n", opcodeIndex.str().c_str());
			return;
		}
		opcode = debugMap.at(opcodeIndex.str());

		// Check if we need to page memory
		if (opcode.find("=") != std::string::npos) {
			// Remove the equals
			opcode.erase(opcode.end() - 2, opcode.end());

			// Zero page read
			if (CPUStatus[11] <= 0xFF) {
				operand << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[11] << std::setfill(' ') << std::setw(10) << opcode << "#$" 
					<< std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[11] << " = " 
					<< std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[9];
			}
			// Absolute read
			else if(CPUStatus[11] != 0) {
				operand << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (CPUStatus[11] & 0xFF) << " "
					<< std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (CPUStatus[11] >> 8)
					<< std::setfill(' ') << std::setw(7) << opcode << "$" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << CPUStatus[11] << " = "
					<< std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[9];
			}
		}
		// Implicit
		else {
			uint16_t pcSteps = CPUStatus[8] - CPUStatus[3];

			if (pcSteps == 2) {
				operand << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[11] << std::setfill(' ') << std::setw(9) << opcode
					<< " #$" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << CPUStatus[7];
			}
			else if (pcSteps == 3) {
				operand << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (CPUStatus[11] & 0xFF) << " "
					<< std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (CPUStatus[11] >> 8)
					<< std::setfill(' ') << std::setw(6) << opcode
					<< " $" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << CPUStatus[7];
			}
			else {
				operand << std::setfill(' ') << std::setw(11) << opcode;
			}
		}

		std::stringstream output;
		output << std::uppercase << std::hex << CPUStatus[8] << "  ";
		output << opcodeIndex.str() << " ";
		output << std::setfill(' ') << std::left << std::setw(40) << operand.str();
		output << "A:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[0] << "  ";
		output << "X:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[1] << "  ";
		output << "Y:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[2] << "  ";
		output << "P:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[5] << "  ";
		output << "SP:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << CPUStatus[4] << std::endl;

		FileManager::debugLog(output.str());
	}
}

// Take the amount of time it took to render the last frame, and the number of cycles used
// to determine the framerate
void Debug::PrintFPS(unsigned int *lastFrameTime, unsigned int *cycles) {
	//if (LOG_FRAMERATE && SDL_GetTicks() > *lastFrameTime + 1000) {
	//	printf("FPS: %i\n", ((*cycles * 3) / 341) / 261);
	//	*lastFrameTime = SDL_GetTicks();
	//	*cycles = 0;
	//}
}