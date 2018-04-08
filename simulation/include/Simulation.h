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
        Simulation();
        Simulation(Graph* graph);

        void nextTurn();
        void updateDataNode(data& d) const;

        Graph* getGraph() const;
        int getTurn() const;

        void setGraph(Graph* graph);
        void setTurn(int turn);
};

#endif
