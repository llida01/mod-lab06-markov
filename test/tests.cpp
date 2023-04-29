// Copyright 2021 GHA Test Team
#include "gtest/gtest.h"
#include "textgen.h"

TEST(test1, CountPrefix) {
    std::vector <std::string> text = ReadFile("text2.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    EXPECT_EQ(prefixTable[0].size(), 2);
}

TEST(test2, PrefixSuffix) {
	std::vector <std::string> text = ReadFile("text.txt");
	std::deque <prefix> prefixTable = CreatePrefixTable(text);
	std::map<prefix, std::vector<std::string>> statetab = CreatePrefixSuffixTable(prefixTable, text);
	prefix pref1 = { "Заметался", "пожар" };
	std::vector <std::string> expSuffix1 = { "голубой," };
	prefix pref2 = { "первый", "раз" };
	std::vector <std::string> expSuffix2 = { "я", "отрекаюсь", "я", "отрекаюсь" };
	std::vector <std::string> suffix1 = statetab.find(pref1)->second;
	std::vector <std::string> suffix2 = statetab.find(pref2)->second;
	EXPECT_EQ(expSuffix1, suffix1);
	EXPECT_EQ(expSuffix2, suffix2);
}

TEST(test3, SuffixFromOne) {
    std::vector <std::string> text = ReadFile("text1.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    std::map<prefix, std::vector<std::string>> statetab = CreatePrefixSuffixTable(prefixTable, text);
    prefix pref = { "В", "белом" };
    std::string expSuffix = "плаще";
    std::map<prefix, std::vector<std::string>>::iterator it = statetab.find(pref);
    std::vector <std::string> suffix = it->second;
    int index = ChooseSuffix(suffix);
    EXPECT_EQ(expSuffix, suffix[index]);
}

TEST(test4, SuffixFromMuch) {
    std::vector <std::string> text = ReadFile("text2.txt");
    std::deque <prefix> prefixTable = CreatePrefixTable(text);
    std::map<prefix, std::vector<std::string>> statetab = CreatePrefixSuffixTable(prefixTable, text);
    prefix pref = { "Имя", "твое-" };
    std::vector <std::string> expSuffix = {"птица", "льдинка", "пять", "ах,", "поцелуй", "поцелуй" };
    std::map<prefix, std::vector<std::string>>::iterator it = statetab.find(pref);
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