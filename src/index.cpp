#include <napi.h>
#include <string>
#include <fstrem>
#include <stdio.h>
#include <vector>
#include "Model.h"
using namespace std;
Model n = Model();
Napi::Array processFile(const Napi::CallbackInfo& data){
    Napi::Env env = data.Env();
    FILE * file;
    file = fopen(data[0], "r");
    vector<vector<string>> processedWords;
    if (!file) processedWords[0].push_back("Failed to read file");
    else {
        char sentence [300];
        vector <string> words_set;
        fgets(sentence, 300, file);
        unsigned long length = sentence.length();
        char *pt = strtok(sentence, " -.,;:'_?!()");
        while (pt!=NULL) {
            words_set.push_back(pt);
            pt = strtok(NULL, " -.,;:'_?!()");
        }
        vector<string>::iterator it = words_set.begin();
        for (it; it!= words_set.end(); ++it){
            processedWords[0].push_back(n.stem(*it));
            processedWords[1].push_back(n.lemmatize(*it));
        }
    }
    return Napi::Array::New(env, processedWords);
}
Napi::String stemmer(const Napi::CallbackInfo &data){
    Napi::Env env = data.Env();
    std::string word = (std::string) data[0].ToString();
    std::string result = n.stem(word);
    return Napi::String::New(env, result);
}
Napi::String lemmatizer (const Napi::CallbackInfo &data){
   Napi::Env env = data.Env();
    std::string word = (std::string) data[0].ToString();
    std::string result = n.lemmatize(word);
    return Napi::String::New(env, result); 
}
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "stemmer"),
        Napi::Function::New(env, stemmer)
    );
    exports.Set(
        Napi::String::New(env, "lemmatizer"),
        Napi::Function::New(env, lemmatizer)
    );
    return exports;
}
NODE_API_MODULE(Model, Init)