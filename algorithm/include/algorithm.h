#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/animal/include/Animal.h"
#include "../../entities/animal/include/NaturalLaw.h"


struct Algorithm{

    private:
        Graph* m_graph;


    public:
        Algorithm();
        Algorithm(Graph* graph);
        virtual ~Algorithm();

        //getter setter
        Graph* getGraph() const {return m_graph;}
        void setGraph(Graph* val){m_graph = val;}


        ///Algorithm fonctions
        void clearAllMarck();

        bool checkAllNodeMarck();

        void processedThreeOfNodeByNode(Node* nodeWork);

        void processedThreeRecursive(data d, bool down);

        bool testStrongConnexeGraph();

        void processedGraphRecursive(data d);

        ///Fonction temporaire
        void displayNodeProssed();

};











#endif
