#include "../include/algorithm.h"

void clearAllMarck(Graph& graph){

    for(int i = 0; i < graph.size(); i++){
        data d = graph.get(i);
        d.first->setProcessed(false);
        for(auto & v : d.second){
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

void updateAllVertex(Graph& graph){

    while(!checkAllNodeMarck(graph)){

        for(int i = 0; i < graph.size(); i++){
            data d = graph.get(i);
            if(!d.first->isProcessed()){
                updateNodeByVertex(d);
            }
        }
    }

    clearAllMarck(graph);
}

void processedThreeRecursive(Graph& graph, data d, bool down){

    //marque le sommet
    d.first->setProcessed(true);

    //on parcoure toutes ses liaisions
    for(auto& l : d.second){
        //si la liaison est pas deja marque
        if(!l->isProcessed()){
            //si on souahite descendre et que le sommet de depart est le sommet en etude
            if(down && l->getStartNode() == d.first){
                //Marque la liasion et on lance la recursivité (algo de parcours en profondeur)
                l->setProcessed(true);
                processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getEndNode()->getUid())), true);
            }
            //si on monte et que le sommet d arriver est le sommet en etude
            else if(!down && l->getStartNode() != d.first){
                //Marque la liasion et on lance la recursivité (algo de parcours en profondeur)
                l->setProcessed(true);
                processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getStartNode()->getUid())), false);
            }
        }
    }
}

void processedThreeOfNodeByNode(Graph& graph, Node* nodeWork){

    clearAllMarck(graph);

    nodeWork->setProcessed(true);

    data d =graph.get(graph.getIndexByUid(nodeWork->getUid()));

    for(auto & l : d.second){
        l->setProcessed(true);

        std::cout << "Test : " << (l->getStartNode() == nodeWork) << " & " << (l->getStartNode() != nodeWork) << "\n";

        //si on descend
        if(l->getStartNode() == nodeWork){
            std::cout << "En bas\n";
            processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getEndNode()->getUid())), true);
        }
        //si on monte
        if(l->getStartNode() != nodeWork){
            std::cout << "En haut\n";
            processedThreeRecursive(graph ,graph.get(graph.getIndexByUid(l->getStartNode()->getUid())), false);
        }
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
