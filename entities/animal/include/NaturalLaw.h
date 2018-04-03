#ifndef NATURELAW_H_INCLUDED
#define NATURELAW_H_INCLUDED

#include "../../graph/include/Vertex.h"

struct NaturalLaw {
    float m_survivalRate;
    float m_importance;

    NaturalLaw(){
        m_survivalRate = 1;
        m_importance = 1;
    }

    NaturalLaw(float survivalRate, float importance){
        m_survivalRate = survivalRate;
        m_importance = importance;
    }
};

#endif
