#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <iostream>
#include <map>

#include "utilities.hpp"
void DealWithDataOne();
void BuildTheBasicGuideBook(std::vector<std::vector<std::string>> string);
std::string Result(std::string target);
bool SpecialCase(std::string a);
std::vector<std::string> CopWithTarget(std::string a);
int CWithTarget(std::string a, std::string target, int count);
std::string FinalOperate(std::string abc, int x);
bool FindHelper(std::map<int, std::string>, int x);
#endif