#include "CarRegisterSystem.h"

CarRegisterSystem::CarRegisterSystem() :vehicles(), people(), comands() {}

CarRegisterSystem::~CarRegisterSystem()
{
	for (size_t i = 0;i < vehicles.size();i++)
		delete vehicles[i];

	for (size_t i = 0;i < people.size();i++)
		delete people[i];
}

bool CarRegisterSystem::addVehicle(const char* registration, const char* description)
{
	try
	{
		this->vehicles.push_back(new Vehicle(registration, description));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool CarRegisterSystem::addPerson(const char* name, unsigned int ID)
{
	try
	{
		this->people.push_back(new Person(name, ID));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

Vehicle* CarRegisterSystem::findVehicle(const char* r)const
{
	try
	{
		Registration temp(r);
		for (size_t i = 0;i < vehicles.size();i++)
			if (vehicles[i]->getRegistration() == temp)
				return vehicles[i];
		return nullptr;
	}
	catch (...)
	{
		return nullptr;
	}

}
Person* CarRegisterSystem::findPerson(unsigned int id)const
{
	for (size_t i = 0;i < people.size();i++)
		if (people[i]->getID() == id)
			return people[i];
	return nullptr;
}

void CarRegisterSystem::clear()
{
	for (size_t i = 0;i < vehicles.size();i++)
	{
		delete vehicles[vehicles.size() - i - 1];
		vehicles.pop_back();
	}

	for (size_t i = 0;i < people.size();i++)
	{
		delete people[people.size() - i - 1];
		people.pop_back();
	}

	for (size_t i = 0;i < comands.size();i++)
		comands.pop_back();
}

bool CarRegisterSystem::acquire(unsigned int ID, const char* registration)
{
	Person* tempPerson = findPerson(ID);
	Vehicle* tempVehicle = findVehicle(registration);

	if (tempPerson == nullptr || tempVehicle == nullptr) return false;
	return tempVehicle->changeOwner(tempPerson);
}


bool CarRegisterSystem::release(unsigned int ID, const char* registration)
{
	Person* tempPerson = findPerson(ID);
	Vehicle* tempVehicle = findVehicle(registration);

	if (tempVehicle == nullptr || tempPerson == nullptr) return false;

	return tempVehicle->changeOwner(nullptr);
}

bool CarRegisterSystem::remove(unsigned int ID)
{
	bool isInSystem = false;
	size_t index = 0;
	for (size_t i = 0; i < people.size();i++)
		if (people[i]->getID() == ID)
		{
			index = i;
			isInSystem = true;
			break;
		}
	if (!isInSystem) return false;

	std::swap(people[index], people[people.size() - 1]);
	delete people[people.size() - 1];
	people.pop_back();
	return true;
}

bool CarRegisterSystem::remove(const char* registration)
{
	try
	{
		Registration temp(registration);
		bool isInSystem = false;
		size_t index = 0;
		for (size_t i = 0;i < vehicles.size();i++)
			if (vehicles[i]->getRegistration() == temp)
			{
				index = i;
				isInSystem = true;
			}
		if (!isInSystem) return false;

		std::swap(vehicles[index], vehicles[vehicles.size() - 1]);
		delete vehicles[vehicles.size() - 1];
		vehicles.pop_back();
		return true;
	}
	catch (...)
	{
		return false;
	}

}


bool CarRegisterSystem::show(const char* str)
{
	try
	{
		Registration temp(str);
		for (size_t i = 0; i < vehicles.size();i++)
			if (vehicles[i]->getRegistration() == temp)
			{
				vehicles[i]->showOwner();
				std::cout << std::endl;
				return true;
			}
		return false;
	}
	catch (...)
	{
		std::string temp(str);
		if (temp != "PEOPLE" && temp != "VEHICLES") throw std::invalid_argument("Only PEOPLE or VEHICLES");

		if (temp == "PEOPLE")
		{
			for (size_t i = 0; i < this->people.size();i++)
				std::cout << *(this->people[i]);
			std::cout << std::endl;
			return true;
		}

		if (temp == "VEHICLES")
		{
			for (size_t i = 0; i < this->vehicles.size();i++)
				std::cout << *(this->vehicles[i]);
			std::cout << std::endl;
			return true;
		}
		return false;
	}
}

bool CarRegisterSystem::show(unsigned int ID)
{
	for (size_t i = 0;i < this->people.size();i++)
	{
		if (this->people[i]->getID() == ID)
			this->people[i]->showCars();
		std::cout << std::endl;
		return true;
	}
	return false;
}

bool CarRegisterSystem::serialize(const char* f)
{
	std::ofstream file(f);
	if (!file) return false;

	for (size_t i = 0;i < comands.size();i++)
		file << comands[i] << '\n';

	file.close();
	return true;
}

bool CarRegisterSystem::deserialize(const char* f)
{
	std::ifstream file(f);
	if (!file) return false;

	this->clear();
	while (file)
	{
		std::string temp;
		std::getline(file, temp);
		this->comand(temp);
	}
	file.close();
	return true;
}

bool CarRegisterSystem::comand(const std::string& str)
{

	std::vector<size_t> spaceIndex;
	for (size_t i = 0;i < str.size();i++)
		if (str[i] == ' ')
			spaceIndex.push_back(i);

	if (spaceIndex.size() == 0)
	{
		if (str == "VEHICLES") { show("VEHICLES");return true; }
		if (str == "PEOPLE") { show("PEOPLE");return true; }
		return false;
	}

	if (spaceIndex.size() == 1)
	{
		if (str.size() <= spaceIndex[0] + 1) return 0;
		std::string fst(str.substr(0, spaceIndex[0]));
		std::string snd(str.substr(spaceIndex[0] + 1, str.size() - 1));
		return process(fst, snd);
	}
	if (spaceIndex.size() == 2)
	{
		if (str.size() <= spaceIndex[1] + 1) return 0;
		std::string fst(str.substr(0, spaceIndex[0]));
		std::string snd(str.substr(spaceIndex[0] + 1, spaceIndex[1] - spaceIndex[0] - 1));
		std::string trd(str.substr(spaceIndex[1] + 1, str.size() - 1));
		return process(fst, snd, trd);
	}
}

	bool CarRegisterSystem::process(const std::string & fst, const std::string & snd)
	{
		try
		{
			bool flag = false;
			if (fst == "SAVE")
			{
				char* temp = new char[snd.size() + 1];
				for (size_t i = 0;i < snd.size();i++)
					temp[i] = snd[i];
				temp[snd.size()] = '\0';

				flag = serialize(temp);
				delete[] temp;
				return flag;
			}
			if (fst == "OPEN")
			{
				char* temp = new char[snd.size() + 1];
				for (size_t i = 0;i < snd.size();i++)
					temp[i] = snd[i];
				temp[snd.size()] = '\0';

				flag = deserialize(temp);
				delete[]temp;
				return flag;
			}
			if (fst == "SHOW" && snd[0] > '0' && snd[0] <= '9')
			{
				flag = show(stringToNumber(snd));
				return flag;
			}
			if (fst == "SHOW" && snd[0] >= 'A' && snd[0] <= 'Z')
			{
				char* t = new char[snd.size() + 1];
				for (size_t i = 0; i < snd.size();i++)
					t[i] = snd[i];
				t[snd.size()] = '\0';
				flag = show(t);
				delete[] t;
				return flag;
			}
			if (fst == "REMOVE" && snd[0] > '0' && snd[0] <= '9')
			{
				flag = remove(stringToNumber(snd));
				if (flag)this->comands.push_back(fst + " " + snd);
				return flag;
			}
			if (fst == "REMOVE" && snd[0] >= 'A' && snd[0] <= 'Z')
			{
				char* t = new char[snd.size() + 1];
				for (size_t i = 0; i < snd.size();i++)
					t[i] = snd[i];
				t[snd.size()] = '\0';
				flag = remove(t);
				delete[] t;
				if (flag)this->comands.push_back(fst +" "+ snd);
				return flag;
			}
		}
		catch (...)
		{
			return false;
		}
	}
	bool CarRegisterSystem::process(const std::string & fst, const std::string & snd, const std::string & trd)
	{
		try
		{
			bool flag = false;;
			if (fst == "PERSON")
			{
				char* s = new char[snd.size() + 1];
				for (size_t i = 0;i < snd.size();i++)
					s[i] = snd[i];
				s[snd.size()] = '\0';
				unsigned int num = stringToNumber(trd);

				flag = addPerson(s, num);
				delete[] s;
				if (flag) comands.push_back(fst + " " + snd + " " + trd);
				return flag;
			}
			if (fst == "VEHICLE")
			{
				char* s = new char[snd.size() + 1];
				for (size_t i = 0;i < snd.size();i++)
					s[i] = snd[i];
				s[snd.size()] = '\0';

				char* e = new char[trd.size() + 1];
				for (size_t i = 0;i < trd.size();i++)
					e[i] = trd[i];
				e[trd.size()] = '\0';

				flag = addVehicle(s, e);
				delete[]s;
				delete[]e;
				if (flag) comands.push_back(fst + " " + snd + " " + trd);
				return flag;
			}
			if (fst == "ACQUIRE")
			{
				unsigned int num = stringToNumber(snd);

				char* e = new char[trd.size() + 1];
				for (size_t i = 0;i < trd.size();i++)
					e[i] = trd[i];
				e[trd.size()] = '\0';

				flag = acquire(num, e);
				delete[] e;
				if (flag) comands.push_back(fst + " " + snd + " " + trd);
				return flag;
			}
			if (fst == "RELEASE")
			{
				unsigned int num = stringToNumber(snd);

				char* e = new char[trd.size() + 1];
				for (size_t i = 0;i < trd.size();i++)
					e[i] = trd[i];
				e[trd.size()] = '\0';

				flag = release(num, e);
				delete[] e;
				if (flag) comands.push_back(fst + " " + snd + " " + trd);
				return flag;
			}
		}
		catch (...)
		{
			return false;
		}
	}



