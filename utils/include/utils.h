#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <string>

void initRand();
int genNumber(int min, int max);
std::string genUid(int length=15);

#endif
