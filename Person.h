#pragma once
#include<iostream>
#include "string"
#include "vector"
#include "Vehicle.h"

class Vehicle;

class Person
{
	static std::vector<unsigned int> used;
	static bool isUsed(unsigned int id);

	unsigned int ID;
	std::string name;
	std::vector<Vehicle*> cars;

public:
	Person(const char* name,unsigned int ID);
	Person(const Person&) = delete;
	Person& operator=(const Person&) = delete;
	~Person();

	bool addCar(Vehicle* car);
	bool removeCar(Vehicle* car);
	unsigned int getID()const;
	bool isOwner(const char* reg)const;
	bool isOwner(const Vehicle* v)const;
	void showCars()const;
	friend std::ostream& operator<<(std::ostream& os, const Person& p);

};