#include "Helper.h"
#include <charconv>

//converts exception to bool
bool Helper::TryParseInt(const std::string str, int& value)
{
    //standard parser
    auto [ptr, ex] = std::from_chars(
        str.data(),
        str.data() + str.size(),
        value
    );

    return ex == std::errc{} && ptr == str.data() + str.size();
}

bool Helper::TryParseDouble(const std::string str, double& value)
{
	auto [ptr, ex] = std::from_chars(
		str.data(),
		str.data() + str.size(),
		value
	);
	return ex == std::errc{} && ptr == str.data() + str.size();
}