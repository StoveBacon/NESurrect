#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include "FileManager.h"

#define LOG_FRAMERATE false
#define LOG_CPU false


class Debug {
public:
	static void LogCPUStatus(uint16_t CPUStatus[12]);
	static void PrintFPS(unsigned int *lastFrameTime, unsigned int *cycles);
};