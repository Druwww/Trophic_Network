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

        std::vector<Edge*> m_vecKEdgeMin;
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

        bool goKmin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        bool testCombinaisonKmin(std::vector<int> vectest);

        void findKmin();

        void processedKmin();

        //trouver k connexe min
        void makeVecEdgeGraph();

        bool testUnicEdgeInVec(Edge* edgeTest);

        bool goKEdgeMin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        bool testCombinaisonKedgeMin(std::vector<int> vectest);

        void saveEdgeByIndex(std::vector<int>& vecIndex);

        void killEdgeByIndex(std::vector<int> vecIndex);

        void reviveEdgeByIndex(std::vector<int> vecIndex);

        void findKEdgeMin();

        void processedKEdgemin();

        ///Fonction temporaire
        void displayNodeProssed();

};











#endif
