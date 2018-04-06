#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/data/include/NodeAttr.h"
#include "../../entities/data/include/EdgeAttr.h"


class Simulation {
private:

    Graph* m_graph;

    int m_turn;

    std::vector<int> m_vecIndexOrdre;

public:
    Simulation ();
    Simulation(Graph* graph);

    virtual ~Simulation ();

    ///getter setter init
    Graph* getGraph() const {return m_graph;}
    void setGraph(Graph* val){m_graph = val;}

    int getTurn() const {return m_turn;}
    void setTurn(int val){m_turn = val;}

    // Preparation function
    int numberDegreEatNode(Node* node);

    template <typename T>
    void clearVecteur(std::vector<T>& vec);

    void generateVecIndexOrdre();

    void nextYearNode(Node* nodeUpdate);

    void nextYearNodes();



};


#endif
