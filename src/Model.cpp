#include "Model.h"
using namespace std;

regex Model::end ("(я|а|и|і|у|ою|ею|о|е|ю)$");
regex Model::punctuation ("[^A-Яа-я]");
regex Model::prefixes ("^(без|роз|через|перед|понад|при|пре|прі|архі)");
regex Model::suffixes[3] = {regex("(к|ц)$"), regex("(г|з)$"), regex("(х|с)$")};

Model::Model(){}

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

bool Model::wordIsStopWord(string word){
    char check [256];
    ifstream fin("src/texts/stopwords_list.txt");
    while (!fin.eof()) {
        fin.getline(check, 255);
        if (!word.compare(string(check))) return 1;
    }
    return 0;
}

string Model::stem(string word){
    if (!wordIsStopWord(word) && regex_search(word, end)){
        word = regex_replace (word, end, "");//add prefixes
        word = regex_replace (word, prefixes, "");
    }else{
        word += " - invalid";
    }
    return word;
}

string Model::lemmatize(string word){
    if (!wordIsStopWord(word) && regex_search(word, end)){
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
            if (!regex_search(word, regex("(ва|да|ю|ура|ома|уба|ля|бло|пи|у|рі|^та)$"))){
                word = save;
            }
        }
        else if (regex_search(word, regex(suffixes[1]))){
            word = regex_replace(word, regex(suffixes[1]), "");
            if (!regex_search(word, regex("(^но|йо|юн|ту|ни|ля|дь|ле|ура|бра|пра|ова|два|бло|оло|^ва|рло|оро|ру|бо|на|ар|ря|ілу|слу|фу|омо|змо|емо|дмо|оль|ль|ари)$"))){
                word = save;
            }
        }
    }else {
        word += " - invalid";
    }
    return word;
}

string Model::dictionarySearch(string word){
    string check;
    string found;
    ifstream fin("src/texts/dict_corp_lt.txt");
    while (!fin.eof()) {
        fin>>check;
        fin>>found;
        if (!word.compare(check)) return found;
        fin.ignore(265, '\n');
    }
    return "not found";
}

Model::~Model()
{
}