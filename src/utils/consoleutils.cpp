#include "../../include/consoleutils.h"

void console_clear(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__unix__) || defined(__unix)
        system("clear");
    #endif
}

void console_progressbar(unsigned int val, unsigned int max, string info){
    cout << "\r" << termcolor::yellow << "[";
    int percent = (int)(val*100/max);
    int formatted_percent = percent*20/100;
    for(unsigned int i = 0; i<formatted_percent; i++){
        cout << termcolor::cyan << "■" << termcolor::white;
    }
    for(unsigned int i = formatted_percent; i<20; i++){
        cout << ' ';
    }
    cout << termcolor::yellow << "] " << termcolor::white << percent << "%";
    if(info.empty()) cout << flush;
    else cout << " (" << info << "s)" << flush;
    if(val==max) cout << endl;
}