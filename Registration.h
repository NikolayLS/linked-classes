#pragma once
#include<iostream>

class Registration
{
	char registration[9];

public:
	Registration(const char* str);
	Registration(const Registration& other);
	Registration& operator=(const Registration& other);
	~Registration();
	bool operator==(const Registration& other);
	friend std::ostream& operator<<(std::ostream& os, const Registration& reg);
};
