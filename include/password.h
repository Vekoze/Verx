#ifndef PASSWORD_HEADER
#define PASSWORD_HEADER

#include "includes.h"

class Password {

public:
    Password(int length);

    int size() const;
    vector<vector<char>*>* getCharacters() const;

private:
    int length;
    vector<vector<char>*>* characters;

};

#endif // !PASSWORD_HEADER
