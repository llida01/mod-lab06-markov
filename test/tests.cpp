// Copyright 2021 GHA Test Team
#include "gtest/gtest.h"
#include "textgen.h"

TEST(test1, CountPrefix) {
    std::vector <std::string> text = ReadFile("text2.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    bool answer = true;
    for (int i = 0; i < prefixTable.size(); i++) {
        if (prefixTable[i].size() != 2) {
            answer = false;
            break;
        }
    }
    EXPECT_EQ(answer, true);
}

TEST(test2, PrefixSuffix) {
    std::vector <std::string> text = ReadFile("text.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    std::map<prefix, std::vector<std::string>> statetab =
        CreatePrefixSuffixTable(prefixTable, text);
    prefix pref1 = { "Tips", "of" };
    std::vector <std::string> expSuffix1 = { "blue" };
    prefix pref2 = { "first", "time" };
    std::vector <std::string> expSuffix2 = { "that", "refusing",
        "that", "refusing" };
    std::vector <std::string> suffix1 = statetab.find(pref1)->second;
    std::vector <std::string> suffix2 = statetab.find(pref2)->second;
    EXPECT_EQ(expSuffix1, suffix1);
    EXPECT_EQ(expSuffix2, suffix2);
}

TEST(test3, SuffixFromOne) {
    std::vector <std::string> text = ReadFile("text1.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    std::map<prefix, std::vector<std::string>> statetab =
        CreatePrefixSuffixTable(prefixTable, text);
    prefix pref = { "a", "white" };
    std::string expSuffix = "cloak";
    std::map<prefix, std::vector<std::string>>::iterator it =
        statetab.find(pref);
    std::vector <std::string> suffix = it->second;
    int index = ChooseSuffix(suffix);
    EXPECT_EQ(expSuffix, suffix[index]);
}

TEST(test4, SuffixFromMuch) {
    std::vector <std::string> text = ReadFile("text2.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    std::map<prefix, std::vector<std::string>> statetab =
        CreatePrefixSuffixTable(prefixTable, text);
    prefix pref = { "is", "a" };
    std::vector <std::string> expSuffix = {"bird", "stone", "bullet,",
        "light", "holy" };
    std::map<prefix, std::vector<std::string>>::iterator it =
        statetab.find(pref);
    std::vector <std::string> suffix = it->second;
    int index = ChooseSuffix(suffix);
    bool answer = false;
    for (int i = 0; i < expSuffix.size(); i++) {
        if (suffix[index] == expSuffix.at(i)) {
            answer = true;
            break;
        }
    }
    EXPECT_EQ(answer, true);
}

TEST(test5, TextLength) {
    std::vector <std::string> text = ReadFile("text3.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    CreatePrefixSuffixTable(prefixTable, text);
    std::string genText = Generation(prefixTable, 50);
    EXPECT_EQ(CountWords(genText), 50);
}