#pragma once
#include <vector>
#include "Singleton.h"

constexpr bool DoCPULogging = true;
class Debugger : public Singleton {
public:
	void LogCPU();
	void Log();
private:
	static std::string LogPath;
};
