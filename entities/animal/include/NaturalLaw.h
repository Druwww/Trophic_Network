#ifndef NATURELAW_H_INCLUDED
#define NATURELAW_H_INCLUDED

#include "../../graph/include/Vertex.h"
#include <string>

struct NaturalLaw {
    float m_survivalRate;
    float m_importance;

    NaturalLaw(){
        m_survivalRate = 1.0f;
        m_importance = 1.0f;
    }

    NaturalLaw(float survivalRate, float importance){
        m_survivalRate = survivalRate;
        m_importance = importance;
    }

    void write(std::ostream& os) const{
        os << m_survivalRate << " ";
        os << m_importance;
    }

    void read(std::istream& is){
        std::string word;
        is >> word;
        m_survivalRate = string_to_float(word);
        is >> word;
        m_importance = string_to_float(word);
    }
};

#endif
