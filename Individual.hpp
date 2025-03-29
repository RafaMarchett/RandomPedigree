#pragma once
#include "header.hpp"

class Individual : public std::enable_shared_from_this<Individual> // Para retornar o ponteiro
{
public:
	Individual(bool,bool,bool,bool, int, bool, int);

	void printIndividual();

	bool getA1() const;
	bool getA2() const;
	std::shared_ptr<Individual> getPointer();
	std::shared_ptr<Individual> getPartnerPointer();
	int getIndividualID() const;
	int getGenerationsNumber() const;
	std::shared_ptr<Individual> generateRandomSon(int);
	void marry();
    void printGenotypes();
    
    private:
	bool individualStatus[3] {0,0,0};
	bool canMarry;
	bool isDominant;
	vector<std::shared_ptr<Individual>> son_ptr;
    
	u_int8_t genderPosition{0}, a1Position{1}, a2Position{2};
	int generationsNumber, individualID;
	std::shared_ptr<Individual> partnerPointer = nullptr;
    
	void generateRandomIndividualToMarry();
	bool getIndividualStatus(int);
	bool getIsDominant();
    
};
Individual::Individual(bool isDominant, bool gender, bool a1, bool a2, int generationsNumber, bool canMarry, int individualID)
{
    this->isDominant = isDominant;
	this->generationsNumber = generationsNumber;
	this->canMarry = canMarry;
	individualStatus[genderPosition] = gender;
	individualStatus[a1Position] = a1;
	individualStatus[a2Position] = a2;
	this->individualID = individualID;
}

void Individual::printIndividual()
{
    if(getIsDominant() && (getIndividualStatus(a1Position) || getIndividualStatus(a2Position)))
	{
        getIndividualStatus(genderPosition) == true ?  cout << womanYes : cout << manYes;
	}
	else if (!isDominant && !individualStatus[a1Position] && !individualStatus[a2Position])
	{
        individualStatus[genderPosition] == true ?  cout << womanYes : cout << manYes;
	}
	else
	{
        individualStatus[genderPosition] == true ?  cout << womanNo : cout << manNo;
	}
    
}

void Individual::marry()
{
    if(canMarry && !partnerPointer)
    {
        generateRandomIndividualToMarry();
    }
}

void Individual::generateRandomIndividualToMarry()
{
    bool cantMarry = 0;
	newSeed;
	bool newGender = !individualStatus[genderPosition];
	newSeed;
	bool newA1 = randBool;
	newSeed;
	bool newA2 = randBool;
    
	partnerPointer = std::make_shared<Individual>(isDominant,newGender,newA1,newA2,(getGenerationsNumber()),cantMarry, (getIndividualID()+1));
}

std::shared_ptr<Individual> Individual::generateRandomSon(int newID)
{
    if(partnerPointer)
	{
        bool newA1,newA2, canMarry={true};
		newSeed;
		bool newGender = randBool;
		newSeed;
		if(randBool) newA1 = partnerPointer->getA1();
		else newA1 = partnerPointer->getA2();
        
		newSeed;
		if(randBool) newA2 =  getA1();
		else newA2 = getA2();
        std::shared_ptr<Individual> newSon = std::make_shared<Individual>(isDominant,newGender,newA1, newA2, generationsNumber+1,canMarry,newID);
		son_ptr.push_back(newSon);
		return newSon;
	}
	return nullptr;
}

bool Individual::getIndividualStatus(int position)
{
    return individualStatus[position];
}

std::shared_ptr<Individual> Individual::getPointer()
{
    return shared_from_this();
}
std::shared_ptr<Individual> Individual::getPartnerPointer()
{
    return partnerPointer;
}

void Individual::printGenotypes()
{
    cout << (getA1() == 0 ? 'a' : 'A') << ',' << (getA2() == 0 ? 'a' : 'A');
}

bool Individual::getA1() const
{
    return individualStatus[a1Position];
}

bool Individual::getA2() const
{
    return individualStatus[a2Position];
}

bool Individual::getIsDominant()
{
    return isDominant;
}

int Individual::getGenerationsNumber() const
{
    return generationsNumber;
}

int Individual::getIndividualID() const
{
    return individualID;
}