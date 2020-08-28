#include "../../include/stringutils.h"

vector<string> split(string str, string delim){
    vector<string> out;
    int startIndex = 0;
    int endIndex = 0;
    while( (endIndex=str.find(delim, startIndex)) < str.size() ){
        string s =  str.substr(startIndex, endIndex - startIndex);
        out.push_back(s);
        startIndex = endIndex + delim.size();
    }
    if(startIndex < str.size()){
        string s = str.substr(startIndex);
        out.push_back(s);
    }
    return out;
}