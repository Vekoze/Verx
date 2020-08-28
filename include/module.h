#ifndef MODULE_HEADER
#define MODULE_HEADER

#include "includes.h"

class Module {

public:

    Module(string name, bool enabled, string description);
    virtual void run() const = 0;
    
    /* Getter */
    string getName() const;
    bool isEnabled() const;
    string getDescription() const;

    /* Utils function */
    static vector<Module*> getEnabledModules(vector<Module*> modules);


private:
    string name;
    bool enabled;
    string description;
};

#endif // !MODULE_HEADER
