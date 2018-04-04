#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

void initRand();
int genNumber(int min, int max);
std::string genUid(int length=15);
int string_to_int(const std::string& str);
float string_to_float(const std::string& str);


#endif
