// Copyright 2022 UNN-IASR
#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <random>
#include "textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string>> statetab;

std::vector <std::string> ReadFile(std::string name) {
    std::vector <std::string> text;
    std::ifstream file(name);
    if (file.is_open()) {
        std::string line;
        while (!file.eof()) {
            getline(file, line);
            int startIndex = 0, endIndex = 0;
            for (int i = 0; i <= line.size(); i++) {
                if (line[i] == ' ' || i == line.size()) {
                    endIndex = i;
                    std::string word;
                    word.append(line, startIndex, endIndex - startIndex);
                    text.push_back(word);
                    startIndex = endIndex + 1;
                }
            }
        }
    }
    file.close();
    return text;
}

bool find(std::deque <prefix> prefixTable, prefix curr) {
    std::deque<prefix>::iterator itr;
    itr = std::find(prefixTable.begin(), prefixTable.end(), curr);
    if (itr != prefixTable.end()) {
        return true;
    } else {
        return false;
    }
}

std::vector <std::string> CreateSuffixTable(prefix Prefix,
  std::vector <std::string> text) {
    std::vector <std::string> suffix;
    for (int i = 0; i < text.size() - NPREF; i++) {
        for (int j = 0; j < NPREF; j++) {
            if (text[i + j] != Prefix[j]) {
                break;
            }
            if (j == NPREF - 1) {
                suffix.push_back(text[i + NPREF]);
            }
        }
    }
    return suffix;
}

std::deque <prefix> CreatePrefixTable(std::vector <std::string> text) {
    std::deque <prefix> prefixTable;
    for (int i = 0; i < text.size() - NPREF; i++) {
        prefix curr;
        for (int j = 0; j < NPREF; j++) {
            curr.push_back(text[i + j]);
        }
        if (!find(prefixTable, curr)) {
            prefixTable.push_back(curr);
        }
    }
    return prefixTable;
}

std::map<prefix, std::vector<std::string>> CreatePrefixSuffixTable(
  std::deque <prefix> prefixTable, std::vector <std::string> text) {
    for (int i = 0; i < prefixTable.size(); i++) {
        std::vector <std::string> suffix =
            CreateSuffixTable(prefixTable[i], text);
        statetab.insert(make_pair(prefixTable[i], suffix));
    }
    return statetab;
}

int ChooseSuffix(std::vector<std::string> suffix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (suffix.size() - 1));
    int index = dist(gen);
    return index;
}

std::string Generation(std::deque <prefix> prefixTable, int length) {
    if (length == 0) {
        length = MAXGEN;
    }
    std::string genText = "";
    srand(time(NULL));
    prefix nextPrefix = prefixTable[0];
    for (int i = 0; i < nextPrefix.size(); i++) {
        genText = genText + nextPrefix[i] + " ";
    }
    std::map<prefix, std::vector<std::string>>::iterator it =
        statetab.find(nextPrefix);
    for (int i = 0; i < length - NPREF; i++) {
        if (it != statetab.end()) {
            std::vector <std::string> suffix = it->second;
            if (!suffix.empty()) {
                auto iter = it->second.cbegin();
                int index = ChooseSuffix(suffix);
                genText = genText + suffix[index] + " ";
                nextPrefix.pop_front();
                nextPrefix.push_back(suffix[index]);
                it->second.erase(iter + index);
                it = statetab.find(nextPrefix);
            }
        } else {
            break;
        }
    }
    return genText;
}

int CountWords(std::string text) {
    int count = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            count += 1;
        }
    }
    return count;
}
