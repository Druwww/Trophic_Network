#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include "../../graph/include/Node.h"
#include "../../../gui/App/nodeguiattr.h"

struct Animal {
    NodeGuiAttr* m_gui;
    int m_quantity;
    float m_birthRate;

    Animal(int quantity=100, float birthRate=0){
        m_quantity = quantity;
        m_birthRate = birthRate;
        m_gui = nullptr;
    }

    Animal(int quantity, float birthRate){
        m_quantity = quantity;
        m_birthRate = birthRate;
    }

    void write(std::ostream& os) const{
        os << m_quantity << " ";
        os << m_birthRate << " ";
        os << (m_gui!=nullptr);
        if(m_gui!=nullptr){
            os << " ";
            m_gui->write(os);
        }
    }

    void read(std::istream& is){
        std::string word;
        bool hasGui;

        is >> word;
        m_quantity = string_to_float(word);
        is >> word;
        m_birthRate = string_to_float(word);
        is >> hasGui;
        if(hasGui){
            m_gui = new NodeGuiAttr();
            m_gui->read(is);
        }
    }
};

#endif
