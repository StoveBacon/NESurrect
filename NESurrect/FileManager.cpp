#include "FileManager.h"

std::string FileManager::romPath = "";
int FileManager::upscaleAmount = 1;
std::string FileManager::gameName = "";
std::ofstream *FileManager::debug = nullptr;
std::map<std::string, std::string> FileManager::debugMap;

void FileManager::init() {
	std::ifstream file;
	file.open("config.txt");

	if (file.is_open()) {
		file >> romPath;
		file >> upscaleAmount;
		file.close();
	}

	// Extract game name from filepath
	gameName = romPath;
	// Erase the .nes
	gameName.erase(gameName.end() - 4, gameName.end());
	// Erase the folders leading up to the game name
	gameName.erase(gameName.begin(), gameName.begin() + static_cast<int>(gameName.find_last_of("/")) + 1);

	loadDebugMap();
}

void FileManager::debugLog(std::string const& string) {
	if (debug == nullptr) {
		debug = new std::ofstream;
		std::stringstream debugPath;
		time_t currentTime = time(0);
		tm ltm; 
		localtime_s(&ltm, &currentTime);

		debugPath << "./DebugLogs/" << gameName << std::setfill('0') << std::setw(2) << ltm.tm_mon + 1 << std::setw(2) << ltm.tm_mday << ltm.tm_year + 1900 
			<< "_" << std::setw(2) << ltm.tm_sec << std::setw(2) << ltm.tm_min << std::setw(2) << ltm.tm_hour << ".txt";
		//debug->open(debugPath.str());
		debug->open("./DebugLogs/lognes.txt");

		loadDebugMap();
	}

	if (debug->is_open())
	{
		*debug << string;
		debug->flush();
	}
}

// Opens the debug definitions file and puts it all in a map for use by the debugger for more verbose debugging
void FileManager::loadDebugMap() {
	if (!debugMap.empty()) {
		return;
	}

	std::ifstream file;
	file.open("./DebugDefinitions.txt");

	if (!file.is_open()) {
		debugLog("Unable to open debug definitions");
		return;
	}

	std::string index;
	std::string arg1, arg2;
	std::stringstream hexArg;
	file >> arg1;

	while (!file.eof()) {
		hexArg << std::setfill('0') << std::setw(2) << arg1;
		index = hexArg.str();
		file >> arg2;
		debugMap[index] = arg2;

		file >> arg1;
		if (arg1 == "=") {
			debugMap[index].append(" = ");
			file >> arg1;
		}
		hexArg.str(std::string());
	}

	file.close();
}

void FileManager::close() {
	delete debug;
}