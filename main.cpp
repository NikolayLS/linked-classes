// files-task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vehicle.h"
#include "Person.h"
#include "CarRegisterSystem.h"

int main()
{
	try
	{
		CarRegisterSystem sys;
		while (true)
		{
			bool flag = false;
			std::string s;
			std::getline(std::cin, s);
			if (s == "EXIT")break;
			flag=sys.comand(s);
			if (!flag)std::cout << "something went wrong\n";
		}
	}

	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}