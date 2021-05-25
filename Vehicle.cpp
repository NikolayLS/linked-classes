#include "Vehicle.h"

std::vector<Registration> Vehicle::used;

bool Vehicle::isRegUsed(const Registration& reg)
{
	for (size_t i = 0;i < used.size();i++)
	{
		if (used[i] == reg) return true;
	}
	return false;
}

Vehicle::Vehicle(const char* registration, const char* description) :registration(registration), description(description),owner(nullptr)
{
	if (isRegUsed(this->registration)) throw std::logic_error("Registration already in use");
	else
	{
		used.push_back(this->registration);
	}
}

Vehicle::~Vehicle()
{
	changeOwner(nullptr);
	for (size_t i = 0;i < used.size();i++)
	{
		if (used[i] == this->registration)
		{
			std::swap(used[i], used[used.size() - 1]);
			used.pop_back();
		}
	}
}

bool Vehicle::changeOwner(Person* owner)
{
	if (isOwner(owner)) return false;

	if (this->owner == nullptr)
	{
		this->owner = owner;
		if(owner != nullptr) owner->addCar(this);
		return true;
	}
	else
	{
		this->owner->removeCar(this);
		this->owner = owner;
		if (owner != nullptr) owner->addCar(this);
		return true;
	}
}

bool Vehicle::isOwner(const Person* othOwner)const
{
	return this->owner == othOwner;
}

Registration Vehicle::getRegistration()const
{
	return this->registration;
}

unsigned int Vehicle::ownerID()const
{
	if (this->owner == nullptr) throw std::logic_error("this vehicle does not have owner");
	return this->owner->getID();
}

void Vehicle::showOwner()const
{
	if (this->owner == nullptr)
	{
		std::cout << this->registration << " does not have owner";
		return;
	}
	std::cout << this->registration << " is owned by: " << *owner;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
	return os << '(' << v.registration << ',' << v.description<<")";
}


