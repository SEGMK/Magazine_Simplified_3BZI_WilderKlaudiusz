#pragma once
#include <string>

class Helper
{
public:
	static bool TryParseInt(const std::string str, int& value);
	static bool TryParseDouble(const std::string str, double& value);
};