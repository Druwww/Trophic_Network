#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include "../../graph/include/Node.h"

struct Animal {
    int m_quantity;
    float m_birthRate;

    Animal(){
        m_quantity = 100;
        m_birthRate = 0;
    }
};

#endif
