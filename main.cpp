#include "header.hpp"
#include "Family.hpp"
#include "Individual.hpp"

int main()
{
    int quantityOfGenerations{0};
    bool isDominant;
    cout << "Insira a quantidade de gerações\n>>> ";
    cin >> quantityOfGenerations;
    cout << "Agora, insira se a característica é ou não dominante (Digite 1 para sim, 0 para não)\n>>> ";
    cin >> isDominant;
    
    Family newFamily(isDominant,quantityOfGenerations);
    return 0;
}