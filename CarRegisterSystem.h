#pragma once
#include <iostream>
#include "Person.h"
#include "Vehicle.h"
#include "HelpFunctions.h"
#include <fstream>

class CarRegisterSystem
{
private:
	std::vector<Person*> people;
	std::vector<Vehicle*> vehicles;
	std::vector<std::string> comands;

	Vehicle* findVehicle(const char* r)const;
	Person* findPerson(unsigned int id)const;
	void clear();

public:
	CarRegisterSystem();
	CarRegisterSystem(const CarRegisterSystem& other) = delete;
	CarRegisterSystem(CarRegisterSystem&& other) = delete;
	CarRegisterSystem& operator=(const CarRegisterSystem& other) = delete;
	CarRegisterSystem& operator=(CarRegisterSystem&& other) = delete;
	~CarRegisterSystem();

private:
	//comand help-functions
	bool process(const std::string& fst, const std::string& snd);
	bool process(const std::string& fst, const std::string& snd, const std::string& trd);

public:
	bool comand(const std::string& str);

private:
	bool addVehicle(const char* registration, const char* description);
	bool addPerson(const char* name, unsigned int ID);
	bool acquire(unsigned int ID, const char* registration);
	bool release(unsigned int ID, const char* registration);
	bool remove(unsigned int ID);
	bool remove(const char* registration);
	bool show(const char* str);
	bool show(unsigned int ID);
	bool serialize(const char* f);
	bool deserialize(const char* f);
};
