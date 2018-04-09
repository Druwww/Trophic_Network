/**
 * \file Edge.h
 * \brief Header Edge
 * \author Omar.A / Quentin.M
 * \version 1
 * \date 08/04/2018
 *
 * La classe Edge est la classe qui va contenir tout la data d une liaison
 *
 */

#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include "Node.h"
#include "../../../utils/include/utils.h"

class Edge{
    private:
        std::string m_uid; /*!< Unique Identification : sa référence unique si vous preferez*/
        float m_weight;  /*!< Poids de la liaison*/
        bool m_active;  /*!< Si la liaison est active (existe mais ne peut pas se proceder)*/
        bool m_processed; /*!< Marquage ou non de la liaison*/

        Node* m_startNode; /*!< Pointeur du noeud de depart de la liaison*/
        Node* m_endNode; /*!< Pointeur du sommet d arrivee*/

        void* m_data;  /*!< Pointeur de la data de la liaison*/

    public:
        /*!
        *  \brief Constructeur
        *
        *   Constructeur de la classe Edge par defaut
        */
        Edge();

        /*!
        *  \brief Constructeur par copie
        *
        *   Constructeur de la classe Edge par copie
        */
        Edge(const Edge& edge, void (*copyEdgeData)(void*, void**));

        /*!
     *  \brief Getter UID
     *
     *  Retourne l uid de la liasion
     *
     *  \return l uid de la liasion
     */
        std::string getUid() const;

        /*!
     *  \brief Getter Weight
     *
     *  Retourne le poids de la liasion
     *
     *  \return le poids de la liasion
     */
        float getWeight() const;

        /*!
     *  \brief Getter Active
     *
     *  Retourne si la liasion est active ou non
     *
     *  \return true si elle est active
     */
        bool isActive() const;

        /*!
     *  \brief Getter processed
     *
     *  Retourne si la liasion est marque
     *
     *  \return true si elle est marque
     */
        bool isProcessed() const;

        /*!
     *  \brief Getter Start Node
     *
     *  Retourne le pointeur du sommet de depart de la liasion
     *
     *  \return le pointeur du sommet
     */
        Node* getStartNode() const;

        /*!
     *  \brief Getter End Node
     *
     *  Retourne le pointeur du sommet d arrivee de la liasion
     *
     *  \return le pointeur du sommet
     */
        Node* getEndNode() const;

        /*!
     *  \brief Getter data edge
     *
     *  Retourne la data de la liasion
     *
     *  \return la data
     */
        void* getData() const;


        /*!
        *  \brief Setter uid
        *
        *  Remplce la valeur stocker par celle en pramattre
        *
        *  \param la valeur a poser
        */
        void setUid(const std::string& uid);

        /*!
     *  \brief Setter Weight
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setWeight(const float& weight);

        /*!
     *  \brief Setter active
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setActive(const bool& active);

        /*!
        *  \brief Setter processed
        *
        *  Remplce la valeur stocker par celle en pramattre
        *
        *  \param la valeur a poser
        */
        void setProcessed(const bool& processed);

        /*!
     *  \brief Setter Start Node
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setStartNode(Node* node);

        /*!
     *  \brief Setter End Node
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setEndNode(Node* node);

        /*!
     *  \brief Setter Data
     *
     *  Remplce la valeur stocker par celle en pramattre
     *
     *  \param la valeur a poser
     */
        void setData(void* data);


        /*!
     *  \brief << Edge
     *
     *  Methode qui permet d ecrire le contenu de la liaison dans un flux sortant en paramettre
     *
     *  \param le flux ou il faut ecrire
     */
        void write(std::ostream& os) const;

        /*!
     *  \brief >> Edge
     *
     *  Methode qui permet de lire puis enregistrer le contenu de la liaison depuis un flux entrant en paramettre
     *
     *  \param le flux ou il faut lire
     */
        void read(std::istream& is);
};

#endif
