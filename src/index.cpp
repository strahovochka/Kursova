#include <napi.h>
#include <string>
#include "Model.cpp"

Model n = Model();

Napi::String stemmer(Napi::CallbackInfo &data){
    Napi::Env env = data.Env();
    std::string word = (std::string) data[0].ToString();
    std::string result = n.stem(word);
    return Napi::String::New(env, word);
}

Napi::String lemmatizator (Napi::CallbackInfo &data){
   Napi::Env env = data.Env();
    std::string word = (std::string) data[0].ToString();
    std::string result = n.lemmatize(word);
    return Napi::String::New(env, word); 
}

Napi::Object Init(Napi::Env env, Napi::Object export){
    export.Set(
        Napi::String::New(env, "stemmer"),
        Napi::Function::New(env, stemmer)
        Napi::String::New(env, "lemmatizator"),
        Napi::Function::New(end, lemmatizator)
    )
}

NODE_API_MODULE(Model, Init)
