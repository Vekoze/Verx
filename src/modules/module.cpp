#include "../../include/module.h"

Module::Module(string _name, bool _enabled, string _description) : name(_name), enabled(_enabled), description(_description) {}

vector<Module*> Module::getEnabledModules(vector<Module*> modules) {
    vector<Module*> enabled_modules;
    for(unsigned int i = 0; i<modules.size(); i++){
        if(modules[i]->isEnabled()) 
            enabled_modules.push_back(modules[i]);
    }
    return enabled_modules;
}

string Module::getName() const {
    return name;
}

bool Module::isEnabled() const {
    return enabled;
}

string Module::getDescription() const {
    return description;
}