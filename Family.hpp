#pragma once
#include "header.hpp"
#include "Individual.hpp" 
typedef map<int,std::shared_ptr<Individual>> mp;

int randChildNumber();
class Family
{
  public:
  Family(bool, int);
  
  private:
  bool isDominant;
  int totalGenerations;
  map<int,mp> allIndividuals;
  
  void createAllGenerations();
  void addIndividual(bool,bool,bool, int);
  int getLastIDInGeneration(map<int,mp>&, int);
  void generateQuestion(std::shared_ptr<Individual>,std::shared_ptr<Individual>);
  int returnPunnettSquareChance(int,int,int,int);

};

Family::Family(bool isDominant_, int totalGenerations_)
: isDominant(isDominant_), totalGenerations(totalGenerations_)
{
    newSeed;
    bool randGender = randBool;
    newSeed;
    bool randA1 = randBool;
    newSeed;
    bool randA2 = randBool;

    addIndividual(randGender,randA1,randA2, 1);
    createAllGenerations();
  }
  
  void Family::addIndividual(bool gender, bool a1, bool a2, int generationNumber)
  {
    int individualID = getLastIDInGeneration(allIndividuals,generationNumber);
    ++individualID;
    bool canMarry = 1;
    allIndividuals[generationNumber][individualID] = std::make_shared<Individual>(isDominant, gender, a1, a2, generationNumber, canMarry, individualID);
}

int Family::getLastIDInGeneration(map<int,mp>& allIndividuals, int generationNumber)
{
    auto ite = allIndividuals.find(generationNumber);
    if(ite == allIndividuals.end()) return -1;
    const auto& idMap = ite->second;
    if(idMap.empty()) return -1;
    return idMap.rbegin()->first;
}

void Family::createAllGenerations()
{
    int currentGeneration = 1; 
    //TODO: Colocar algo aqui para os individuos de cada geracao fiquem mais separadas
    std::shared_ptr<Individual> personForQuestion{nullptr};
    std::shared_ptr<Individual> wifeForQuestion{nullptr};
    while (currentGeneration <= totalGenerations)
    {
      cout << bold << greenBold << '\n' << currentGeneration << "º ============================================\n" << bold;

        vector<std::shared_ptr<Individual>> currentIndividuals;
        
        for (const auto& [id, person] : allIndividuals[currentGeneration])
        {
            if (person) currentIndividuals.push_back(person);
        }

        for (auto& person : currentIndividuals)
        {
          static bool questionGenerated{0};
          int newID = getLastIDInGeneration(allIndividuals, currentGeneration + 1) + 1;
          person->marry();
          auto wife = person->getPartnerPointer();
          if (wife)
          {
            allIndividuals[currentGeneration][newID] = wife;
          }
          newSeed;
          int sonQuantity = randChildNumber();
          for (int i = 0; i < sonQuantity; i++)
          {
            auto son = person->generateRandomSon(newID);
            if (son)
            {
              allIndividuals[currentGeneration + 1][newID + i] = son;
            }
          }

          cout << ' ';
          person->printIndividual();
          cout << " --- ";
          wife->printIndividual();
          cout << "  -> " << noBold << "Filhos: " << sonQuantity << ' ' << bold;
          cout << "\n  ";
          person->printGenotypes();
          cout << "     ";
          wife->printGenotypes();
          cout << "\n\n";
          personForQuestion = person;
          wifeForQuestion = wife;
        }

        currentGeneration++; 
    }
    cout << '\n';
    generateQuestion(personForQuestion,wifeForQuestion);
}
void Family::generateQuestion(std::shared_ptr<Individual> person,std::shared_ptr<Individual> wife)
{
  cout << "Qual a chance do filho do casal:\n";

  if(person)person->printIndividual();
  cout << " --- ";
  if(wife)wife->printIndividual();
  cout << '\n';
  if(person)person->printGenotypes();
  cout << "     ";
  if(wife)wife->printGenotypes();

  cout << "\nTer a característica " << (isDominant == 1 ? "dominante" : "recessiva") << "?\n";
  cout << "Pressione \"ENTER\" para ver a resposta: ";
  {
    std::string temp;
    getline(cin,temp);
    cin.ignore(10000,'\n');
  }
  cout << "\nRESPOSTA: " << returnPunnettSquareChance(person->getA1(),person->getA2(),wife->getA1(),wife->getA2()) << "%\n";
} 
int Family::returnPunnettSquareChance(int personA1,int personA2,int wifeA1,int wifeA2)
{
  int dominantCases{0},recessiveCases{0};
  (!personA1 && !wifeA1 ? ++recessiveCases : ++dominantCases);
  (!personA1 && !wifeA2 ? ++recessiveCases : ++dominantCases);
  (!personA2 && !wifeA1 ? ++recessiveCases : ++dominantCases);
  (!personA2 && !wifeA2 ? ++recessiveCases : ++dominantCases);

  if(isDominant) return (25 * dominantCases);
  return (25 * recessiveCases);
}

int randChildNumber()
{
  newSeed;
  int tempChance = (rand() % 10) + 1;
  if(tempChance < 4) return 1;
  if(tempChance < 8) return 2;
  return 3;
}