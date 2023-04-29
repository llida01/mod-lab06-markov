// Copyright 2022 UNN-IASR
#pragma once
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <fstream>

typedef std::deque<std::string> prefix;

std::vector <std::string> ReadFile(std::string name);
bool find(std::deque <prefix> prefixTable, prefix curr);
std::vector <std::string> CreateSuffixTable(prefix Prefix,
  std::vector <std::string> text);
std::deque <prefix> CreatePrefixTable(std::vector <std::string> text);
std::map<prefix, std::vector<std::string>> CreatePrefixSuffixTable(
  std::deque <prefix> prefixTable, std::vector <std::string> text);
int ChooseSuffix(std::vector<std::string> suffix);
std::string Generation(std::deque <prefix> prefixTable, int length);
int CountWords(std::string text);
