#pragma once
#include <iostream>
#include <vector>

using namespace std;

string delSpaces(string &str);

void csvPrint(std::vector< vector<string> >& data);

void csvRead(std::string& fileName, char delimeter, std::vector < std::vector<string> >& csv);

bool taskNameValid(string& s);

bool taskSlotValid(string& s);

bool ItemNameValid(string& s);

bool ItemSlotValid(string& s);

bool OrderNameValid(string& s);

bool OrderSlotValid(string& s);
