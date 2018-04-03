#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"
#include "../../headers/header.h"

//Declaration classe sommet pour la compilation
class Sommet;

class Arete{

    private :
        int m_id;

        bool m_active;

        bool m_marque;

        Sommet* m_sommetD;
        Sommet* m_sommetA;

        int m_valeurImpacte;



    public :
        //Default constructor
        Arete();

        //Default destructor
        virtual ~Arete();

        ///Getter/Setter
        int getId() const {return m_id;}
        void setId(int val){m_id = val;}

        bool getActive() const {return m_active;}
        void setActive(bool val){m_active = val;}

        bool getMarque() const {return m_marque;}
        void setMarque(bool val){m_marque = val;}

        Sommet* getSommetD() const {return m_sommetD;}
        void setSommetD(Sommet* val){m_sommetD = val;}

        Sommet* getSommetA() const {return m_sommetA;}
        void setSommetA(Sommet* val){m_sommetA = val;}

        int getValeurImpacte() const {return m_valeurImpacte;}
        void setValeurImpacte(int val){m_valeurImpacte = val;}



        ///Methode lecture flux
        //GOGO Omar

};

#endif // ARETE_H_INCLUDED
