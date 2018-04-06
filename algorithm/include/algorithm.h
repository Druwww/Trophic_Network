#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/data/include/NodeAttr.h"
#include "../../entities/data/include/NodeAttr.h"
#include <math.h>


struct Algorithm{

    private:
        Graph* m_graph;

        std::vector<int> m_vecIndexCombinaison;

        std::vector<Edge*> m_vecLiaisonGraph;

    public:
        Algorithm();
        Algorithm(Graph* graph);
        virtual ~Algorithm();

        //getter setter init
        Graph* getGraph() const {return m_graph;}
        void setGraph(Graph* val){m_graph = val;}

        ///Algorithm fonctions
        void clearAllMarck();

        bool checkAllNodeMarck();

        template <typename T>
        void clearVecteur(std::vector<T>& vec);

        //Marquage composante fortement connexe
        void processedThreeOfNodeByNode(Node* nodeWork);

        void processedThreeRecursive(data d, bool down);

        bool testStrongConnexeGraph();

        void processedGraphRecursive(data d);

        //Trouver kmin
        int updateEdgesActive();

        bool updateEdgeActive(Edge* l);

        void killNodeAttrsByIndex(std::vector<int> vecIndex);

        void ReviveNodeAttrsByIndex(std::vector<int> vecIndex);

        bool go(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        bool testCombinaison(std::vector<int> vectest);

        void findKmin();

        //trouver k connexe min
        void makeVecEdgeGraph();

        bool testUnicEdgeInVec(Edge* edgeTest);

        ///Fonction temporaire
        void displayNodeProssed();

};











#endif
