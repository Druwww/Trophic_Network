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

    void write(std::ostream& os) const{
        os << m_quantity << " ";
        os << m_birthRate;
    }

    void read(std::istream& is){
        std::string word;
        is >> word;
        m_quantity = std::stof(word);
        is >> word;
        m_birthRate = std::stof(word);
    }
};

#endif
