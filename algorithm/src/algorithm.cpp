#include "../include/algorithm.h"

void clearAllMarck(Graph& graph){

    for(int i = 0; i < graph.size(); i++){
        data d = graph.get(i);
        d.first->setProcessed(false);
        for(auto & v : d.second.first){
            v->setProcessed(false);
        }
        for(auto & v : d.second.second){
            v->setProcessed(false);
        }
    }

    std::cout<< "\n\nDone\n\n";
}

bool checkAllNodeMarck(Graph& graph){
    for(int i = 0; i < graph.size(); i++){
        data d = graph.get(i);
        if(!d.first->isProcessed()){
            return false;
        }
    }

    return true;
}

void processedThreeRecursive(Graph& graph, data d, bool down){

    //marque le sommet
    d.first->setProcessed(true);

    //si on descend
    if(down){
        //on prend le vecteur des arete sortant
        for(auto & l : d.second.second){
            //Si l arete n est pas marque
            if(!l->isProcessed()){
                //on marque l arete
                l->setProcessed(true);
                //si le sommmet d arriver n est pas marque
                if(!l->getEndNode()->isProcessed()){
                    processedThreeRecursive(graph, graph.get(graph.getIndexByUid(l->getEndNode()->getUid())), true);
                }
            }
        }
    }
    else{
        //on prend le vecteur des arete entrant
        for(auto & l : d.second.first){
            //Si l arete n est pas marque
            if(!l->isProcessed()){
                //on marque l arete
                l->setProcessed(true);
                //si le sommmet d arriver n est pas marque
                if(!l->getStartNode()->isProcessed()){
                    processedThreeRecursive(graph, graph.get(graph.getIndexByUid(l->getStartNode()->getUid())), false);
                }
            }
        }
    }
}

void processedThreeOfNodeByNode(Graph& graph, Node* nodeWork){

    clearAllMarck(graph);

    nodeWork->setProcessed(true);

    data d =graph.get(graph.getIndexByUid(nodeWork->getUid()));

    //pour toutes les aretes qui descende
    for(auto & l : d.second.second){
        l->setProcessed(true);
        processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getEndNode()->getUid())), true);
    }
    for(auto & l : d.second.first){
        l->setProcessed(true);
        processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getStartNode()->getUid())), false);
    }

    //Affichage du resultat
    displayNodeProssed(graph);

    clearAllMarck(graph);
}

void displayNodeProssed(Graph& graph){

    std::cout << "Les marquee : \n";

    for(int i = 0; i < graph.size(); i++){
        data d = graph.get(i);
        if(d.first->isProcessed()){
            std::cout << "\t" << d.first->getUid() << "\n";
        }
    }

    std::cout << "\n\n";

}
