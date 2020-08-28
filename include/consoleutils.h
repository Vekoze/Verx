#ifndef CONSOLE_UTILS_HEADER
#define CONSOLE_UTILS_HEADER

#include "includes.h"
#include "termcolor.h"

void console_clear();
void console_progressbar(unsigned int val, unsigned int max, string info = "");

#endif // !CONSOLE_UTILS_HEADER