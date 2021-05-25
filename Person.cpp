#include "Person.h"

std::vector<unsigned int> Person::used;

bool Person::isUsed(unsigned int id)
{
	for (size_t i = 0;i < used.size();i++)
	{
		if (used[i] == id)
			return true;
	}
	return false;
}

Person::Person(const char* name, unsigned int ID) :name(name), ID(ID), cars()
{
	if (Person::isUsed(ID)) throw std::logic_error("ID is already in use");
	else Person::used.push_back(ID);
}

Person::~Person()
{
	for (size_t i = 0;i < this->cars.size();i++)
		removeCar(this->cars[i]);

	for (size_t i = 0;i < Person::used.size();i++)
		if (Person::used[i] == this->ID)
		{
			std::swap(Person::used[i], Person::used[Person::used.size() - 1]);
			Person::used.pop_back();
		}
}

bool Person::addCar(Vehicle* car)
{
	if (this->isOwner(car) || car == nullptr) return false;

	this->cars.push_back(car);
	car->changeOwner(this);
	return true;
}

bool Person::removeCar(Vehicle* car)
{
	if (car == nullptr || !isOwner(car)) return false;

	for (size_t i = 0; i < this->cars.size();i++)
		if (this->cars[i] == car)
		{
			std::swap(this->cars[i], this->cars[this->cars.size() - 1]);
			this->cars.pop_back();
			car->changeOwner(nullptr);
			return true;
		}
	return false;
}

unsigned int Person::getID()const
{
	return this->ID;
}

bool Person::isOwner(const Vehicle* v)const
{
	if (v == nullptr) return false;

	for (size_t i = 0;i < this->cars.size();i++)
		if (v == this->cars[i]) return true;
	return false;
}

bool Person::isOwner(const char* reg)const
{
	Registration temp(reg);
	for (size_t i = 0;i < this->cars.size();i++)
		if (this->cars[i]->getRegistration() == temp)
			return true;

	return false;
}

void Person::showCars()const
{
	if (this->cars.size() == 0)
	{
		std::cout << this->ID << " owns 0 cars";
		return;
	}
	std::cout << this->ID << " owns: ";
	for (size_t i = 0; i < this->cars.size();i++)
		std::cout << *(this->cars[i]);
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << '(' << p.name << ',' << p.ID << ')';
}

