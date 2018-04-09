/**
 * \file Graph.h
 * \brief Header Graph
 * \author Omar.A / Quentin.M
 * \version 1
 * \date 08/04/2018
 *
 * La classe Graph est la classe qui va contenir tout la data du graph
 *
 */


#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Node.h"
#include "Edge.h"
#include "../../data/include/DataInterface.h"

/**
 * \enum IO
 * \brief typedef Input Output
 *
 * IO est une pair de vecteur de pointeur d arête, le premier sont les Input (ceux qui arrive a notre sommet)
 * le deuxieme est les output (qui parte de notre sommet)
 */
typedef std::pair<std::vector<Edge*>, std::vector<Edge*> > IO;

/**
 * \enum data
 * \brief typedef data
 *
 * data est une pair comprenant un pointeur de noeud et sont IO d arrete
 */
typedef std::pair<Node*, IO> data;

/*! \class Graph
   * \brief La classe graph comprend tout la data du graph
   *
   */
class Graph{
    private:
        std::vector<data> m_data; /*!< Vecteur de data*/
        DataInterface m_nodeItf;  /*!< Inertaface de Node pour par partie graphique*/
        DataInterface m_edgeItf; /*!< Inertaface de Edge pour par partie graphique*/

         /*!
         *  \brief Subtract
         *
         *  Permet le substract d un vecteur sur l autre
         *
         *  \param v1 selon qu on va subtract a v2
         *  \return Voide
         */
         void subtract(std::vector<Edge*>& v1, const std::vector<Edge*>& v2);

    public:
        /*!
        *  \brief Constructeur
        *
        *   Constructeur de la classe Graph par defaut
        */
        Graph();

        /*!
     *  \brief Constructeur par cpy
     *
     *  Constructeur par copie de Graph
     *
     *  \param graph : reference du graph a copier
     */
        Graph(const Graph& graph);

        /*!
        *  \brief Destructeur
        *
        *  Destructeur de la classe Graph
        */
        ~Graph();

            /*!
         *  \brief Size()
         *
         *  Retourne le nombre de sommet dans le graphe
         *
         *  \return int : le nombre de sommet dans le graph
         */
        int size() const;

        /*!
     *  \brief get
     *
     *  Methode qui permet de retourner la data d un sommet dont son index est passe en paramettre
     *
     *  \param i : index qu on veut récuperer
     *  \return data : la data
     */
        data get(int i) const;

        /*!
     *  \brief getOrder
     *
     *  Meme methode que Size qui aurait du etre enleve
     *
     */
        int getOrder() const;

        /*!
     *  \brief hasNode
     *
     *  Methode qui permet d'ajouter un morceau a liste de
     *  lecturee dire si un noeud est present dans la data
     *
     *  \param strSong : le pointeur du noeud a tester
     *  \return true si le noeud est deja present dans la data,
     *  false sinon
     */
        bool hasNode(Node* node) const;

        /*!
     *  \brief areConnected
     *
     *  Methode qui permet de dire si deux noeud sont relier par une arrete
     *
     *  \param  Les pointeurs des deux noeud a tester
     *  \return true si il y a une arrete entre les deux sommet,
     *  false sinon
     */
        bool areConnected(Node* node1, Node* node2) const;

        /*!
     *  \brief getIndexByUid
     *
     *  Methode qui permet de donner l index dans la data du sommet dont on a passer l UID
     *
     *  \param l'UID du sommet dont on veut recuperer l index
     *  \return int: l index du sommet
     */
        int getIndexByUid(const std::string& uid) const;

        /*!
     *  \brief getNodeByUid
     *
     *  Methode qui permet d'obtenir le pointeur du sommet dont on passe l uid
     *
     *  \param uid du sommet a recuperer
     *  \return le pointeur du sommet qu on souhaite recuperer
     */
        Node* getNodeByUid(const std::string& uid) const;

        /*!
     *  \brief getConnections(UID)
     *
     *  Methode qui permet de retourner le IO d un sommet dont son UID est passe en paramettre
     *
     *  \param uid ud sommet qu on souhaite recuperer
     *  \return le IO du sommet passe
     */
        IO getConnections(const std::string& uid) const;

        /*!
     *  \brief getConnections(Node*)
     *
     *  Methode qui permet de retourner le IO d un sommet dont son pointeur est passe en paramettre
     *
     *  \param pointeur du sommet a recuperer
     *  \return  le IO du sommet passe
     */
        IO getConnections(Node* node) const;

        /*!
     *  \brief getNodeInterface
     *
     *  Methode qui permet de retourner l interface des sommet du graphe
     *
     *  \return  l interface
     */
        DataInterface* getNodeInterface();

        /*!
     *  \brief getEdgeInterface
     *
     *  Methode qui permet de retourner l interface des arretes du graphe
     *
     *  \return  l interface
     */
        DataInterface* getEdgeInterface();


        /*!
        *  \brief connect(UID)
        *
        *  Permet de creer une arrete entre deux sommet dont leur UID est passe en paramettre, avec possiblement avec la data de la laision
        *
        *  \param uid des sommet a lier, pointeur de la data a remplir : par defaut rien
        */
        void connect(const std::string& uid1, const std::string& uid2, void* data=nullptr);

        /*!
        *  \brief connect(Node*)
        *
        *  Permet de creer une arrete entre deux sommet dont leur pointeurs est passe en paramettre, avec possiblement avec la data de la laision
        *
        *  \param pointeurs des sommet a lier, pointeur de la data a remplir : par defaut rien
        */
        void connect(Node* node1, Node* node2, void* data=nullptr);

        /*!
     *  \brief addNode
     *
     *  Methode qui permet d ajouter un sommet au graphe dont on passe le pointeur du sommet creer
     *
     *  \param pointeur du sommet a ajouter
     *
     *  \return  le numero de l index du sommet juste avant lui
     */
        int addNode(Node* node);

        /*!
     *  \brief removeNode(Node*)
     *
     *  Methode qui permet de retirer un sommet de la data grace a son pointeur
     *
     *  \param le pointeur du sommet a supprimer
     *
     * \return  true : si il y a bien une suppression,
     * false sinon si le sommet n existe pas
     */
        bool removeNode(Node* node);

        /*!
     *  \brief removeNode(UID)
     *
     *  Methode qui permet de retirer un sommet de la data grace a son uid
     *
     *  \param l'uid du sommet a supprimer
     *
     * \return  true : si il y a bien une suppression,
     * false sinon si le sommet n existe pas
     */
        bool removeNode(const std::string& uid);

        /*!
     *  \brief removeEdge(Edge*)
     *
     *  Methode qui permet de retirer une arrete de la data grace a son pointeur
     *
     *  \param le pointeur de l arrete a supprimer
     *
     * \return  true : si il y a bien une suppression,
     * false sinon si le sommet n existe pas
     */
        bool removeEdge(Edge* edge);


        /*!
        *  \brief print
        *
        *  Methode qui permet d afficher dans la console tout le contenu du graphe
        */
        void print() const;

        /*!
     *  \brief << Graph
     *
     *  Methode qui permet d ecrire le contenu du graphe dans un flux sortant en paramettre
     *
     *  \param le flux ou il faut ecrire
     */
        void write(std::ostream& os) const;
        /*!
     *  \brief >> Graph
     *
     *  Methode qui permet de lire puis enregistrer le contenu du graphe depuis un flux entrant en paramettre
     *
     *  \param le flux ou il faut lire
     */
        void read(std::istream& is);
};


#endif
