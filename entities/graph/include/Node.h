/**
 * \file Node.h
 * \brief Header Node
 * \author Omar.A / Quentin.M
 * \version 1
 * \date 08/04/2018
 *
 * La classe Node est la classe qui va contenir tout la data d un sommet
 *
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "../../../utils/include/utils.h"
#include <string>
#include <iostream>

/*! \class Node
   * \brief La class node permet de stocker toute la data d un sommet
   *
   */
class Node{
    private:
        std::string m_uid; /*!< Unique Identification : sa référence unique si vous preferez*/
        bool m_processed; /*!< Marquage ou non du commet*/
        int m_group; /*!< Numero de groupe de forte connexite*/
        void* m_data; /*!< pointeur vers la data du sommet*/

    public:
        /*!
        *  \brief Constructeur
        *
        *   Constructeur de la classe Node par defaut
        */
        Node();

        /*!
        *  \brief Constructeur par copie
        *
        *   Constructeur de la classe Node par copie
        */
        Node(const std::string& uid);

        /*!
        *  \brief Constructeur par copie avec data node
        *
        *   Constructeur de la classe Node par defaut
        */
        Node(const Node& node, void (*copyNodeDataListener)(void*, void**));

        /*!
     *  \brief Getter UID
     *
     *  Retourne l uid du sommet
     *
     *  \return l uid du sommet
     */
        std::string getUid() const;

        /*!
     *  \brief Getter processed
     *
     *  Retourne si le sommet est marque
     *
     *  \return true si il est marque,
     * false sinon
     */
        bool isProcessed() const;

        /*!
     *  \brief Getter Group
     *
     *  Retourne l uid du sommet0
     *
     *  \return l uid du sommet
     */
        int getGroup() const;

        /*!
     *  \brief Getter Data
     *
     *  Retourne la data du sommet
     *
     *  \return la data du sommet
     */
        void* getData() const;


        /*!
     *  \brief Setter processed
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setProcessed(const bool& processed);

        /*!
     *  \brief Setter Group
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setGroup(const int& group);

        /*!
     *  \brief Setter Data
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setData(void* data);


        /*!
     *  \brief << Node
     *
     *  Methode qui permet d ecrire le contenu du node dans un flux sortant en paramettre
     *
     *  \param le flux ou il faut ecrire
     */
        void write(std::ostream& os) const;

        /*!
     *  \brief >> Node
     *
     *  Methode qui permet de lire puis enregistrer le contenu du node depuis un flux entrant en paramettre
     *
     *  \param le flux ou il faut lire
     */
        void read(std::istream& is);
};

#endif
