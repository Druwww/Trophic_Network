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
    for(int i=0 ; i<length ; i++){
        int index = genNumber(0, str.size()-1);
        uid += str[index];
    }
    return uid;
}
