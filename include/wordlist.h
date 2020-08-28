#ifndef WORDLIST_HEADER
#define WORDLIST_HEADER

#include "includes.h"
#include "module.h"
#include "password.h"

#include "stringutils.h"
#include "consoleutils.h"
#include "termcolor.h"

class Wordlist : public Module {

public:
    Wordlist(string name, bool enabled, string description);
    void run() const;
};

#endif // !WORDLIST_HEADER