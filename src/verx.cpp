#include "../include/includes.h"

#include "../include/module.h"
#include "../include/wordlist.h"
#include "../include/consoleutils.h"
#include "../include/termcolor.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

void load_modules(vector<Module*>* modules){
    modules->push_back(new Wordlist("Wordlist", true, "Generate custom wordlist"));
}

int main(){
    #if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(65001);
    #endif

    vector<Module*> modules;
    load_modules(&modules);
    vector<Module*> enabled_module = Module::getEnabledModules(modules);

    console_clear();

    cout << R"(  
            
 /\   /\ ___  _ __ __  __       
 \ \ / // _ \| '__|\ \/ /       | Vekoze
  \ V /|  __/| |    >  <        | v1.1-ALPHA
   \_/  \___||_|   /_/\_\       | gang gang gang
                         
    )" << endl;

    for(unsigned int i = 0; i<enabled_module.size(); i++){
        cout << i+1 << ": " << modules[i]->getName() << termcolor::yellow << " (" << modules[i]->getDescription() << ")" << termcolor::white << endl;
    }
    cout << endl;

    int mod;
    do {
        cout << termcolor::cyan << "$> " << termcolor::white;
        cin >> mod;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(mod<1 || mod>enabled_module.size());

    console_clear();
    modules[mod-1]->run();
    return 0;
} 