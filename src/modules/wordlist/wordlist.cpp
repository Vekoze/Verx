#include "../../../include/wordlist.h"

unsigned long long wordlist_possibilities(Password* password){
    unsigned long long total = 0;
    int length = password->size();
    vector<vector<char>*>& ref = *(password->getCharacters());
    for(unsigned int i = 0; i<ref.size(); i++){
        vector<char>& refVec2 = *(ref[i]);
        if(total==0) total++;
        total *= refVec2.size();
    }
    return total;
}

void wordlist_write_combinaison(vector<vector<char>*>& arr, ofstream& file, unsigned long long possibilities) {
    int n = arr.size(); 
    unsigned long long current = 0;
    int* indices = new int[n]; 
  
    for (unsigned int i = 0; i < n; i++) 
        indices[i] = 0; 
  
    while (1) { 

        for (unsigned int i = 0; i < n; i++){
            vector<char>& ref = *(arr[i]);
            file << ref[indices[i]]; 
        }
        file << '\n';
        current++;

        console_progressbar(current, possibilities);
    
        int next = n - 1;
        vector<char>& ref = *(arr[next]);
        while (next >= 0 &&  
              (indices[next] + 1 >= ref.size())) 
            next--; 
  
        if (next < 0) 
            return; 

        indices[next]++; 
  
        for (int i = next + 1; i < n; i++) 
            indices[i] = 0; 
    } 
}

void wordlist_generate_file(Password* password, string path){
    string file_path;
    vector<vector<char>*>& ref = *(password->getCharacters());
    ofstream file;
    file.open(path);
    wordlist_write_combinaison(ref, *(&file), wordlist_possibilities(password));
    file.close();
}

void wordlist_add_char(Password *password, unsigned int index, char c){
    vector<vector<char>*>& refVec = *(password->getCharacters());
    vector<char>& refVec2 = *(refVec[index]);
    auto it = find(refVec2.begin(), refVec2.end(), c);
    if(it==refVec2.end())
        refVec2.push_back(c);
}

void wordlist_remove_char(Password *password, unsigned int index, char c){
    vector<vector<char>*>& refVec = *(password->getCharacters());
    vector<char>& refVec2 = *(refVec[index]);
    auto it = find(refVec2.begin(), refVec2.end(), c);
    if(it!=refVec2.end()){
        unsigned int pos = distance(refVec2.begin(), it);
        refVec2.erase(refVec2.begin() + pos);
    }
}

void wordlist_refine(Password* password, unsigned int index, string pattern, int option){
    vector<char> characters(pattern.begin(), pattern.end());
    ifstream file("keyword.txt");
    string line;
    if(file.is_open()){
        cout << "file open" << endl;
        while(getline(file, line)){
            vector<string> splitted = split(line, "::");
            if(pattern.compare(splitted[0]) == 0){
                for(unsigned int i = 0; i<splitted[1].size(); i++){
                    if(option==1) wordlist_add_char(password, index, splitted[1][i]);
                    else wordlist_remove_char(password, index, splitted[1][i]);
                }
                return;
            }
        }
        file.close();
    }

    for(unsigned int i = 0; i<characters.size(); i++){
        if(option==1) wordlist_add_char(password, index, characters[i]);
        else wordlist_remove_char(password, index, characters[i]);
    }
}

Wordlist::Wordlist(string name, bool enabled, string description) : Module(name, enabled, description) {}

void Wordlist::run() const {
        cout << R"(  
            
 /\   /\ ___  _ __ __  __       
 \ \ / // _ \| '__|\ \/ /
  \ V /|  __/| |    >  < 
   \_/  \___||_|   /_/\_\)" << termcolor::green << " - Wordlist" << termcolor::reset << R"(
       
    )" << endl;

    cout << "* Generated words size *" << endl;
    int size;
    do {
        cout << termcolor::cyan << "$> " << termcolor::white;
        cin >> size;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(size<1);
    cout << endl;

    Password password(size);

    cout << "* Refine password ? (Y/N) *" << endl;
    char refine_choose;
    do {
        cout << termcolor::cyan << "$> " << termcolor::white;
        cin >> refine_choose;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(refine_choose!='Y' && refine_choose!='N');
    cout << endl;

    if(refine_choose=='Y') {

        bool finish = false;
        do {
            cout << "* Password character index *" << endl;
            int password_index;
            do {
                cout << termcolor::cyan << "$> " << termcolor::white;
                cin >> password_index;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while(password_index<0 && password_index>=size);
            cout << endl;

            cout << "* Add(1) or Remove(2) character(s)/pattern(s) *" << endl;
            int refine_option;
            do {
                cout << termcolor::cyan << "$> " << termcolor::white;
                cin >> refine_option;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while(refine_option!=1 && refine_option!=2);
            cout << endl;

            cout << "* Character(s)/Keyword *" << endl;
            cout << "(Tips: enter 'a&5' if you wanna add/remove 'a' - '&' and '5' and use keyword if you wanna add/remove entire pattern)" << endl;
            cout << termcolor::cyan << "$> " << termcolor::white;
            string characters;
            getline(cin, characters);
            cout << endl;

            wordlist_refine(&password, password_index, characters, refine_option);

            cout << "* Continue ? (Y/N) *" << endl;
            char retry;
            do {
                cout << termcolor::cyan << "$> " << termcolor::white;
                cin >> retry;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while(retry!='Y' && retry!='N');
            cout << endl;

            if(retry=='N') finish=true;

        } while(!finish);
        
    }
    wordlist_generate_file(&password, "custom_wordlist.txt");
}
