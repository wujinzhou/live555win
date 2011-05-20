#pragma once
#include <string>

class SysData
{
public:
	static std::string GetMac();
	static std::string GetOperaSystem();
	static std::string GetDirectXVersion();
	static std::string GetScreen();
	static std::string GetCpu();
	static std::string GetMem();
	static std::string GetLan();
};
