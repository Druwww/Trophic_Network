/**
 * \file Simulation.h
 * \brief Header Graph
 * \author Omar.A / Quentin.M
 * \version 1
 * \date 08/04/2018
 *
 * La classe Simulation va prendre le pointeur de notre graphe de donnée, puis va annalyser/modifier les données pour réaliser une simulatiion de l evolution des populations au cours du temps
 *
 */

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/data/include/NodeAttr.h"
#include "../../entities/data/include/EdgeAttr.h"

/*! \class Simulation
   * \brief La classe simulation va pouvoir faire l evolution des populations au cours du temps
   *
   */
class Simulation {
    private:
        Graph* m_graph; /*!< Pointeur du graphe avec tout la data*/
        int m_turn; /*!< Numero du tour de la simulation*/

    public:
        /*!
        *  \brief Constructeur
        *
        *   Constructeur de la classe Simulation par defaut
        */
        Simulation();

        /*!
        *  \brief Constructeur avec paramettre
        *
        *   Constructeur de la classe Simulation en lui passant le pointeur du graph data qu il va exploiter
        */
        Simulation(Graph* graph);


        /*!
        *  \brief nextTurn
        *
        *  Permet de mettre a jours les quantitées de population de tout les sommets en fonction des paramettres des sommets et liaisons
        */
        void nextTurn();

        /*!
        *  \brief updateDataNode
        *
        *   Permet de mettre a jour la quantitée de la population de la data passé en paramettre
        *
        * \param data : data de la population a mettre a jour
        */
        void updateDataNode(data& d) const;

        /*!
        *  \brief Getter Graph
        *
        *   \return retourne le pointeur du graph
        */
        Graph* getGraph() const;

        /*!
        *  \brief Getter Turn
        *
        *   Permet de mettre a jour la quantitée de la population de la data passé en paramettre
        */
        int getTurn() const;

        /*!
        * \brief Setter Graph
        *
        * \param le pointeur du graph a mettre
        */
        void setGraph(Graph* graph);

        /*!
        * \brief Setter Turn
        *
        * \param le numero du tour a mettre
        */
        void setTurn(int turn);
};

#endif
