#include <napi.h>
#include <string>
#include "Model.h"
Model n = Model();
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