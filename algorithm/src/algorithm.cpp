#include "../include/algorithm.h"

Algorithm::Algorithm(){
    m_graph = nullptr;
}

Algorithm::~Algorithm(){
    //dtor
}

Algorithm::Algorithm(Graph* graph): m_graph(graph){
    //ctor
}

void Algorithm::clearAllMarck(){

    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);
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

bool Algorithm::checkAllNodeMarck(){
    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);
        if(!d.first->isProcessed()){
            return false;
        }
    }

    return true;
}

void Algorithm::processedThreeRecursive(data d, bool down){

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
                    processedThreeRecursive(m_graph->get(m_graph->getIndexByUid(l->getEndNode()->getUid())), true);
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
                    processedThreeRecursive(m_graph->get(m_graph->getIndexByUid(l->getStartNode()->getUid())), false);
                }
            }
        }
    }
}

void Algorithm::processedThreeOfNodeByNode(Node* nodeWork){

    clearAllMarck();

    nodeWork->setProcessed(true);

    data d =m_graph->get(m_graph->getIndexByUid(nodeWork->getUid()));

    //pour toutes les aretes qui descende
    for(auto & l : d.second.second){
        l->setProcessed(true);
        processedThreeRecursive(m_graph->get(m_graph->getIndexByUid(l->getEndNode()->getUid())), true);
    }
    for(auto & l : d.second.first){
        l->setProcessed(true);
        processedThreeRecursive(m_graph->get(m_graph->getIndexByUid(l->getStartNode()->getUid())), false);
    }

    //Affichage du resultat
    displayNodeProssed();

    clearAllMarck();
}

void Algorithm::displayNodeProssed(){

    std::cout << "Les marquee : \n";

    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);
        if(d.first->isProcessed()){
            std::cout << "\t" << d.first->getUid() << "\n";
        }
    }

    std::cout << "\n\n";

}


bool Algorithm::testStrongConnexeGraph(){

    clearAllMarck();

    //demare au premier sommmet
    processedGraphRecursive(m_graph->get(0));

    bool anwser =  checkAllNodeMarck();

    clearAllMarck();

    return anwser;

}

void Algorithm::processedGraphRecursive(data d){

    d.first->setProcessed(true);

    //pour toute les aretes sortante
    for(auto & l : d.second.second){
        //si arete active et que le sommet d arrivee n est pas marquee
        if(l->isActive() && !l->getEndNode()->isProcessed()){
            processedGraphRecursive(m_graph->get(m_graph->getIndexByUid(l->getEndNode()->getUid())));
        }
    }
    for(auto & l : d.second.first){
        //si arete active et que le sommet d arrivee n est pas marquee
        if(l->isActive() && !l->getStartNode()->isProcessed()){
            processedGraphRecursive(m_graph->get(m_graph->getIndexByUid(l->getStartNode()->getUid())));
        }
    }
}
