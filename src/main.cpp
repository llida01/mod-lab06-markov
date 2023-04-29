#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include "textgen.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    std::vector <std::string> text = ReadFile("text1.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    CreatePrefixSuffixTable(prefixTable, text);
    std::string genText = Generation(prefixTable, 0);
    std::cout << genText << std::endl;
}
