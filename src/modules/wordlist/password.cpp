#include "../../../include/password.h"

Password::Password(int _length) : length(_length) {
    characters = new vector<vector<char>*>;
    for(unsigned int i = 0; i<_length; i++){
        vector<char>* temp = new vector<char>;
        vector<char>& ref = *(temp);
        for(unsigned int i = 33; i<127; i++)
            ref.push_back(i);
        characters->push_back(temp);
    }
}

int Password::size() const{
    return length;
}

vector<vector<char>*>* Password::getCharacters() const{
    return characters;
}