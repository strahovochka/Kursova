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
    static regex suffixes [3]; 
    int getSize(string word);
    bool wordIsIn(string word);
    bool isOk(string word);
public:
    vector<string> parse(string file);
    vector<string> tokenize(string text);
    string stem(string word);
    string lemmatize(string word);
    Model();
    ~Model();
};