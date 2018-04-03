#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arete.h"
#include "../../headers/header.h"

//declaration de la classe Arete pour la compilation
class Arete;

class Sommet{

    private :
        int m_id;

        bool m_marque;

        std::string m_nomFichierImage;

        int m_nombrePopulation;

        std::vector<Arete*> m_vecArete;

    public :
        //default constructor
        Sommet();
        //default destructor
        ~Sommet();

        ///Getter/Setter
        int getId() const {return m_id;}
        void setId(int val){m_id = val;}

        bool getMarque() const {return m_marque;}
        void setMarque(bool val){m_marque = val;}

        std::string getNomFichierImage() const {return m_nomFichierImage;}
        void setNomFichierImage(std::string val){m_nomFichierImage = val;}

        int getNombrePopulation() const {return m_nombrePopulation;}
        void setNombrePopulation(int val){m_nombrePopulation = val;}

        std::vector<Arete*>* getpVecArete() const {return &m_vecArete;}

};


#endif // SOMMET_H_INCLUDED
