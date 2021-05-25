#include "Registration.h"

Registration::Registration(const char* str)
{
	if (str == nullptr) throw std::invalid_argument("Registration can not be empty");

	short strSize = 0;
	while (str[strSize] != '\0')
	{
		if (strSize > 7) throw std::invalid_argument("Too long registration");
		this->registration[strSize] = str[strSize];
		strSize++;
	}

	if (strSize == 7)
	{
		registration[7] = '\0';
		if (registration[0] < 'A' || registration[0] > 'Z') throw std::invalid_argument("This registration does not match the rules");
		if (registration[1] < '1' || registration[1] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[2] < '1' || registration[2] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[3] < '1' || registration[3] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[4] < '1' || registration[4] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[5] < 'A' || registration[5] > 'Z') throw std::invalid_argument("This registration does not match the rules");
		if (registration[6] < 'A' || registration[6] > 'Z') throw std::invalid_argument("This registration does not match the rules");
	}
	if (strSize == 8)
	{
		registration[8] = '\0';
		if (registration[0] < 'A' || registration[0] > 'Z') throw std::invalid_argument("This registration does not match the rules");
		if (registration[1] < 'A' || registration[1] > 'Z') throw std::invalid_argument("This registration does not match the rules");
		if (registration[2] < '1' || registration[2] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[3] < '1' || registration[3] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[4] < '1' || registration[4] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[5] < '1' || registration[5] > '9') throw std::invalid_argument("This registration does not match the rules");
		if (registration[6] < 'A' || registration[6] > 'Z') throw std::invalid_argument("This registration does not match the rules");
		if (registration[7] < 'A' || registration[7] > 'Z') throw std::invalid_argument("This registration does not match the rules");
	}
	if(strSize < 7)
	{
		throw std::invalid_argument("Too short registration");
	}
}

Registration::Registration(const Registration& other)
{
	for (short i = 0; i < 8;i++)
	{
		this->registration[i] = other.registration[i];
	}
}


Registration& Registration::operator=(const Registration& other)
{
	if (this != &other)
	{
		for (short i = 0; i < 8;i++)
		{
			this->registration[i] = other.registration[i];
		}
	}
	return *this;
}
Registration::~Registration(){}


bool Registration::operator==(const Registration& other)
{
	for (short i = 0;i < 8;i++)
	{
		if (this->registration[i] != other.registration[i])
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Registration& reg)
{

	return os << reg.registration;
}
