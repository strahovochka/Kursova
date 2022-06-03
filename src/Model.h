#pragma once
#include <vector>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

class Model
{
private: 
    static regex end;
    static regex punctuation;
    static regex prefixes;
    static regex suffixes [3]; 
    int getSize(string word);
    bool wordIsStopWord(string word);
    bool isOk(string word);
public:
    string dictionarySearch(string word);
    string stem(string word);
    string lemmatize(string word);
    Model();
    ~Model();
};