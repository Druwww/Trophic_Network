#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/data/include/NodeAttr.h"
#include "../../entities/data/include/EdgeAttr.h"
#include <math.h>

void onDeleteNode(void* data);
void onDeleteEdge(void* data);
void onSerializeNode(std::ostream& os, void* data);
void onSerializeEdge(std::ostream& os, void* data);
void onDeserializeNode(std::istream& is, void** data);
void onDeserializeEdge(std::istream& is, void** data);



struct Algorithm{

    private:

        //Pointeur of the graph's data
        Graph* m_graph;

        //Vector who will have the index of our solution for kmin
        std::vector<int> m_vecIndexCombinaison;

        //Vector who will have all Edge's pointeur of our graph
        std::vector<Edge*> m_vecLiaisonGraph;

        //Vecteur who will have the edge's pointeurs of our solution for kEdgeMin
        std::vector<Edge*> m_vecKEdgeMin;

    public:
        //Defauklt ctor
        Algorithm();
        //Ctor with the graph's pointeurs
        Algorithm(Graph* graph);
        //default dtor
        virtual ~Algorithm();

        //getter setter init
        Graph* getGraph() const {return m_graph;}
        void setGraph(Graph* val){m_graph = val;}

        /***
        Methodes use in all algorithm
        ***/

        //Clean all prossed for all nodes and edges
        void clearAllMarck();
        void clearAllMarck(Graph& graph);

        //Return true if all nodes are prossed
        bool checkAllNodeMarck();

        //Methode to clear a vecteur of type T
        template <typename T>
        void clearVecteur(std::vector<T>& vec);

        //Marquage composante connexe
        void processedThreeOfNodeByNode(Node* nodeWork);

        //Function of recurisive in BFS for see the strong connexity of two nodes
        //d : data for the node in strudding
        //down : true if we want to go down in the graph
        void processedThreeRecursive(data d, bool down);

        //Return true if all the graph is strong connexe
        bool testStrongConnexeGraph();

        //BFS to prossed the nodes and edges with strong connexe
        void processedGraphRecursive(data d);

        /***
        Methode to find kmin : number of nodes to "kill" to not have a strong graph
        ***/

        //Methode who will active/desactivate all edge in function of the sommet kill or not
        int updateEdgesActive(Graph& graph);

        //Methode who will activate/desactive the edge passe in parameter
        bool updateEdgeActive(Edge* l);

        //We pass a index of nodes to "kill", and it kill them
        void killNodeAttrsByIndex(std::vector<int> vecIndex);

        //We pass a index of nodes to "revive", and it revive them
        void ReviveNodeAttrsByIndex(std::vector<int> vecIndex);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill create all combinaison possible of k number take in vecIndex and after test them (call function)
        //return true if the combination works and need to stop all recursive
        bool goKmin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill check if the combination success to disconnect our graph
        //return true if he success
        bool testCombinaisonKmin(std::vector<int> vectest);

        //Function who whill find the kmin : number and which nodes need to be kill to disconect our graph
        //display them in the consol and poressed them
        void findKmin();

        //whill prossed all nodes with the indes in the vector of kmin nodes
        void processedKmin();

        /***
        Methode to find kEdgemin : number of edge to desactivate to not have a strong graph
        ***/

        //will put all graph edges' pointeur in the vector to analyse them one by one after
        void makeVecEdgeGraph();

        //return true if the pointer pass in parameter is not in the vector
        bool testUnicEdgeInVec(Edge* edgeTest);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill create all combinaison possible of k number take in vecIndex and after test them (call function)
        //return true if the combination works and need to stop all recursive
        bool goKEdgeMin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill check if the combination success to disconnect our graph
        //return true if he success
        bool testCombinaisonKedgeMin(std::vector<int> vectest);

        //We give him the index of edge to put their pointer in the vec of our kEdge min solution
        void saveEdgeByIndex(std::vector<int>& vecIndex);

        //will desactivate all edges give in the vector of index
        void killEdgeByIndex(std::vector<int> vecIndex);

        //will activate all edges give in the vector of index
        void reviveEdgeByIndex(std::vector<int> vecIndex);

        //Function who whill find the kmin : number and which edges need to be desactivate to disconect our graph
        //display them in the consol and poressed them
        void findKEdgeMin();

        //whill prossed all edges with the indes in the vector of kmin nodes
        void processedEdgeByPointeur(const std::vector<Edge*>& vecEdge, const std::vector<int>& vecIndex);

        ///Functopn not permanente for display resulte in consol
        void displayNodeProssed();


        /*
        Algo strong connexity ... ty to anwser quicly in the forum
        */
        //do the BFS recursive for make strong connexe
        void BFSConnexity(data d, Graph& graphProssed, bool normal);

        //put the group number to node who are in the new group
        void emptyConnexity(int numero, Graph& graph1, Graph& graph2, Graph& graphData);

        int testStillConnexe0(Graph& graph);

        //algo who put the number of strong connexity in all nodes
        void algoForteConnexity(Graph& graphData);

        /*
        Algo find the real kmin for edge .... en gros il va dire combien d arrete qu il faut enlever pour briser n'importe quelle composante fortement connexe
        */
        //true if 2 graph have all nodes with same connexity group
        bool testIdenticForteConnexity(Graph& graph1, Graph& graph2);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill create all combinaison possible of k number take in vecIndex and after test them (call function)
        //return true if the combination works and need to stop all recursive
        bool goKminConnexity(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill check if the combination success to disconnect our graph
        //return true if he success
        bool testCombinaisonKminConnexity(std::vector<int> vectest);

        //function who will prossed all node to kill to break a strong connexity
        void findKminConnexity();

        /*
        Algo find the real kmin for node .... en gros il va dire combien de sommets qu il faut enlever pour briser n'importe quelle composante fortement connexe
        */
        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill create all combinaison possible of k number take in vecIndex and after test them (call function)
        //return true if the combination works and need to stop all recursive
        bool goKEdgeminConnexity(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination);

        ///Algo/code retake from : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
        //whill check if the combination success to disconnect our graph
        //return true if he success
        bool testCombinaisonKEdgeminConnexity(std::vector<int> vectest);

        //function who will prossed all edge to kill to break a strong connexity
        void findKEdgeminConnexity();
};

#endif
