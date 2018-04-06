#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/data/include/NodeAttr.h"
#include "../../entities/data/include/EdgeAttr.h"


class Simulation {
private:

    Graph* m_graph;

    int m_turn;

public:
    Simulation ();
    Simulation(Graph* graph);

    virtual ~Simulation ();

    ///getter setter init
    Graph* getGraph() const {return m_graph;}
    vois setGraph(Graph* val){m_graph = val;}

    int getTurn() const {return m_turn;}
    void setTurn(int val){m_turn = val;}


};


#endif
