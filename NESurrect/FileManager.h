#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <cstddef>
#include <map>

class FileManager {
	static std::string gameName;
	static std::ofstream *debug;

public:
	static void init();
	static void close();

	static std::string romPath;
	static int upscaleAmount;

	static void loadDebugMap();
	static void debugLog(std::string const& string);
	static std::map<std::string, std::string> debugMap;
};