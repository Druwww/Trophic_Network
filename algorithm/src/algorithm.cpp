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

void unprossedAllNodeLinkToTheNode(data& d){
    //parcour toutes les liasions
    for(auto& l : d.second){
        //si le sommet d arriver de liaison est notre sommet d etude
        if(l->getEndNode() == d.first){
            //on le demarque pour une maj a refaire du a une de ses liaison qui est morte
            l->getStartNode()->setProcessed(false);
        }
    }
}

void updateNodeByVertex(data& d){
    int nb_liaisonVital_on = 0;
    int nb_liaisonVital_off = 0;

    for(auto & l : d.second){



        NaturalLaw* nl = (NaturalLaw*) l->getData();
        //si la liaison est vital
        if(nl->m_importance >= 1){
            //si le sommet de depart de la liasion est notre sommet d etude
            if(l->getStartNode() == d.first){
                Animal* aEtude = (Animal*) l->getEndNode()->getData();
                //si le sommet d arriver n a plus de population ou liaison inactive
                if (aEtude->m_quantity <= 0 || !l->isProcessed()){
                    //remet la liaison et sommet comme inactive
                    l->setProcessed(false);
                    //augmente le nombre de liaison inactive
                    nb_liaisonVital_off++;
                }
                else{
                    //sinon liaison toujours active
                    nb_liaisonVital_on++;
                }
            }
        }
        else{
            Animal* aEtude = (Animal*) l->getEndNode()->getData();
            //si le sommet d arriver n a plus de population (on met a jours meme les liaison non vital)
            if (aEtude->m_quantity <= 0){
                //met la liaison comme inactive
                l->setProcessed(false);
            }
        }
    }



    //si plus de liaison vital morte que de vivante
    if(nb_liaisonVital_off > nb_liaisonVital_on + 1){

        //on met sa population a 0 car on sait qu elle va mourir
        Animal* aEtudeSousProgramme = (Animal*) d.first->getData();
        aEtudeSousProgramme->m_quantity = 0;
        //et tout les sommet qui vont vers ce sommet vont etre demarque pour une nouvelle etude
        unprossedAllNodeLinkToTheNode(d);
    }
    //sinon ce sommet est encore vivant
    else{
        d.first->setProcessed(true);
    }
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
