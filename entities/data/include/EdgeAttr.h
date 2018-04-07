#ifndef NATURELAW_H_INCLUDED
#define NATURELAW_H_INCLUDED

#include "../../graph/include/Edge.h"
#include <string>

struct EdgeAttr {
    float m_survivalRate;
    float m_importance;

    EdgeAttr(float survivalRate=1.0f, float importance=1.0f){
        m_survivalRate = survivalRate;
        m_importance = importance;
    }

    EdgeAttr(const EdgeAttr& attr){
        m_survivalRate = attr.m_survivalRate;
        m_importance = attr.m_importance;
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
