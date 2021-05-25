#pragma once
#include <iostream>
#include "Registration.h"
#include "vector"
#include "string"
#include "Person.h"

class Person;

class Vehicle
{
	static std::vector<Registration> used;
	static bool isRegUsed(const Registration& reg);

	Registration registration;
	std::string description;
	Person* owner;

public:
	Vehicle(const char* registration, const char* description);
	Vehicle(const Vehicle& other) = delete;
	Vehicle& operator=(const Vehicle& other) = delete;
	~Vehicle();

	bool changeOwner(Person* owner);
	bool isOwner(const Person* othOwner)const;
	Registration getRegistration()const;
	unsigned int ownerID()const;
	void showOwner()const;
	friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};

