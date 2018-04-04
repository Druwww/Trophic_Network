#include "../include/utils.h"

void initRand(){
    srand(time(0));
}

int genNumber(int min, int max){
    return min + rand()%(max - min + 1);
}

std::string genUid(int length){
    std::string str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string uid = "";
    for(unsigned int i=0 ; i<length ; i++){
        int index = genNumber(0, str.size()-1);
        uid += str[index];
    }
    return uid;
}

int string_to_int(const std::string& str){
    std::stringstream ss(str);
    int n;
    ss >> n;
    return n;
}

float string_to_float(const std::string& str){
    std::stringstream ss(str);
    float n;
    ss >> n;
    return n;
}
