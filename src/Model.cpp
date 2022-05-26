#include "Model.h"
using namespace std;

regex Model::end ("(я|а|и|і|у|ою|ею|о|е|ю)$");
regex Model::punctuation ("[^A-Яа-я]");
regex Model::suffixes[3] = {regex("(к|ц)$"), regex("(г|з)$"), regex("(х|с)$")};

Model::Model(){}

vector<string> Model::parse(string file){
    ifstream fin(file);
    if (!fin) throw "file";
    string word;
    vector<string> words_set;
    while (!fin.eof()) {
        fin>>word;
        if (isOk(word) && regex_match(word, regex("[^0-9]+")) && !wordIsIn(word)){
            words_set.push_back(regex_replace(word, punctuation, ""));
        }
    }
    return words_set;
}

vector<string> Model::tokenize(string text){
    vector<string> words_set;
    unsigned long length = text.length();
    char str[length+1];
    strcpy(str, text.c_str());
    char *pt = strtok(str, " -.,;:'_?!()");
    while (pt!=NULL) {
        words_set.push_back(pt);
        pt = strtok(NULL, " -.,;:'_?!()");
    }
    return words_set;
}
bool Model::isOk(string word){
    bool word_is_ok = false;
    string vowels = "(а|о|у|и|і|е|я|ї|ю|є)";
    if (getSize(word) > 2){
        if (regex_search(word, regex("^"+vowels))){
            if (!regex_match(word, regex(vowels+"{2,}"))) word_is_ok = true;
        }
        else if (regex_search(word, regex(vowels))) word_is_ok = true;
    }
    return word_is_ok;
}

int Model::getSize(string word){
    int lastIndex = 0;
    int iterator = 0;
    unsigned char byte;
    while (word[iterator]) {
        byte = word[iterator];
        if (byte<=0x7F) {
            iterator++;
        }
        else {
            for (int i = 0; byte & 0x80; i++) {
                byte <<=1;
                iterator++;
            }
        }
        lastIndex++;
    }
    return lastIndex;
}

bool Model::wordIsIn(string word){
    string check;
    ifstream fin("Resources/stopwords_list.txt");
    while (!fin.eof()) {
        fin>>check;
        if (!word.compare(check)) return 1;
    }
    return 0;
}

string Model::stem(string word){
    word = regex_replace (word, end, "");//add prefixes
    return word;
}

string Model::lemmatize(string word){
    word = regex_replace (word, end, "");
    string save = word;
    if (regex_search(word, regex(suffixes[0]))){
        word = regex_replace (word, regex(suffixes[0]), "");
        if (regex_search(word, regex("(ра|ни|ки|щи)$"))){
            word = save;
        }
    }
    else if (regex_search(word, regex(suffixes[2]))){
        word = regex_replace(word, regex(suffixes[2]), "");
        if (!regex_search(word, regex("(ва|да|ю|ура|ома|уба|ля|бло|пи|у|рі)$"))){
            word = save;
        }
    }
    return word;
}



Model::~Model()
{
}

