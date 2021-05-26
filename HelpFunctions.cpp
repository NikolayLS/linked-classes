#include "HelpFunctions.h"
unsigned int stringToNumber(std::string str)
{
	try
	{
		if (str.at(0) == '0') throw std::invalid_argument("can not convert this string to number");
	}
	catch (...)
	{
		throw std::invalid_argument("can not convert this string to number");
	}

	unsigned int forReturn = str[0] - '0';
	for (size_t i = 1;i < str.size();i++)
	{
		if (str[i] < '0' || str[i]>'9') throw std::invalid_argument("can not convert this string to number");
		forReturn *= 10;
		forReturn += str[i] - '0';
	}
	return forReturn;
}
