#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
// #include <iomanip>
#include <chrono>
#include <map>
#include <memory>

#define newSeed srand(std::chrono::high_resolution_clock::now().time_since_epoch().count())
#define randBool (rand() % 2 == 0)

using std::cout; using std::vector; using std::srand; using std::cin; using std::map;

std::ostream& bold(std::ostream& manip) {return manip << "\033[37m\033[1m";}
std::ostream& greenBold(std::ostream& manip) {return manip << "\033[1m\033[33m";}
std::ostream& noBold(std::ostream& manip) {return manip << "\033[0m";}

std::string womanNo= "⚪";
std::string womanYes= "🔴";

std::string manNo= "⬜";
std::string manYes= "🟥";