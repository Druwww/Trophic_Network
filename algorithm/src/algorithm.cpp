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

template <typename T>
void Algorithm::clearVecteur(std::vector<T>& vec){
    while(!vec.empty()){
        vec.pop_back();
    }
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

bool Algorithm::updateEdgeActive(Edge* l){

    NodeAttr* animalD = (NodeAttr*) l->getStartNode()->getData();
    NodeAttr* animalA = (NodeAttr*) l->getEndNode()->getData();

    //si un des deux sommet n est pas mort
    if(animalD->m_quantity != 0 || animalA->m_quantity != 0){
        //on remet la liasion sur active
        l->setActive(true);
        //retourne pas de changement
        return false;
    }

    //sinon les deux sommet sont mort
    l->setActive(false);

    //si il est marque, c est que le changement a deja eu lieux
    if(l->isProcessed()){
        return false;
    }

    //sinon on le marque et on dit qu il y a eu un changement
    l->setProcessed(true);
    return true;
}

int Algorithm::updateEdgesActive(){

    int nb_changement = 0;

    clearAllMarck();

    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);

        for(auto & l : d.second.first){
            if(updateEdgeActive(l)){
                nb_changement++;
            }
        }
        for(auto & l : d.second.second){
            if(updateEdgeActive(l)){
                nb_changement++;
            }
        }

    }

    clearAllMarck();

    return nb_changement;
}

void Algorithm::killNodeAttrsByIndex(std::vector<int> vecIndex){

    for(auto index : vecIndex){
        NodeAttr* pNodeAttr = (NodeAttr*) m_graph->get(index).first->getData();
        pNodeAttr->m_quantity = 0;
    }
}

void Algorithm::ReviveNodeAttrsByIndex(std::vector<int> vecIndex){

    for(auto index : vecIndex){
        NodeAttr* pNodeAttr = (NodeAttr*) m_graph->get(index).first->getData();
        pNodeAttr->m_quantity = 100;
    }
}

//Code inspiré puis repris de : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
bool Algorithm::goKmin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination) {
  if (k == 0) {
    return testCombinaisonKmin(combination);
  }
  for (int i = offset; i <= vecIndex.size() - k; ++i) {
    combination.push_back(vecIndex[i]);

    if(goKmin(i+1, k-1, vecIndex, combination)){
        m_vecIndexCombinaison = combination;
        ReviveNodeAttrsByIndex(combination);
        return true;
    }
    combination.pop_back();
  }

  return false;
}

bool Algorithm::testCombinaisonKmin(std::vector<int> vectest){
    killNodeAttrsByIndex(vectest);
    updateEdgesActive();
    bool resul = !testStrongConnexeGraph();
    ReviveNodeAttrsByIndex(vectest);

    return resul;
}
/// Fin inspiration

void Algorithm::findKmin(){

    std::vector<int> vecIndex;
    std::vector<int> combination;

    clearVecteur<int>(m_vecIndexCombinaison);

    for(int i = 0; i < m_graph->size(); i++){
        vecIndex.push_back(i);
    }

    int kmin = 1;

    while(!goKmin(0,kmin, vecIndex, combination)){
        kmin++;
    }

    std::cout<< "Done : Kmin = " << kmin << "\n Combinaison : [ ";

    for(const auto l : m_vecIndexCombinaison){
        std::cout << l << " ,";
    }

    std::cout << "]\n\n";

    processedKmin();
}

void Algorithm::processedKmin(){
    if(!m_vecIndexCombinaison.empty()){
        for(auto l : m_vecIndexCombinaison){
            m_graph->get(l).first->setProcessed(true);
        }
    }
}

void Algorithm::makeVecEdgeGraph(){

    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);

        for(auto& l : d.second.first){
            if(testUnicEdgeInVec(l)){
                m_vecLiaisonGraph.push_back(l);
            }
        }
        for(auto& l : d.second.second){
            if(testUnicEdgeInVec(l)){
                m_vecLiaisonGraph.push_back(l);
            }
        }
    }
}

bool Algorithm::testUnicEdgeInVec(Edge* edgeTest){
    for(const auto & l : m_vecLiaisonGraph){
        if(edgeTest->getUid() == l->getUid()){
            return false;
        }
    }

    return true;
}

//Code inspiré puis repris de : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
bool Algorithm::goKEdgeMin(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination) {
  if (k == 0) {
    return testCombinaisonKedgeMin(combination);
  }
  for (int i = offset; i <= vecIndex.size() - k; ++i) {
    combination.push_back(vecIndex[i]);

    if(goKEdgeMin(i+1, k-1, vecIndex, combination)){
        saveEdgeByIndex(combination);
        reviveEdgeByIndex(combination);
        return true;
    }
    combination.pop_back();
  }

  return false;
}

bool Algorithm::testCombinaisonKedgeMin(std::vector<int> vectest){
    killEdgeByIndex(vectest);
    bool resul = !testStrongConnexeGraph();
    reviveEdgeByIndex(vectest);

    return resul;
}
/// Fin inspiration

void Algorithm::saveEdgeByIndex(std::vector<int>& vecIndex){
    for(const auto l : vecIndex){
        m_vecKEdgeMin.push_back(m_vecLiaisonGraph[l]);
    }
}

void Algorithm::killEdgeByIndex(std::vector<int> vecIndex){
    for(auto l : vecIndex){
        m_vecLiaisonGraph[l]->setActive(false);
    }
}

void Algorithm::reviveEdgeByIndex(std::vector<int> vecIndex){
    for(auto l : vecIndex){
        m_vecLiaisonGraph[l]->setActive(true);
    }
}

void Algorithm::findKEdgeMin(){

    std::vector<int> vecIndex;
    std::vector<int> combination;

    clearVecteur<Edge*>(m_vecLiaisonGraph);
    clearVecteur<Edge*>(m_vecKEdgeMin);

    makeVecEdgeGraph();


    for(int i = 0; i < m_vecLiaisonGraph.size(); i++){
        vecIndex.push_back(i);
    }

    int kEdgemin = 1;

    while(!goKEdgeMin(0,kEdgemin, vecIndex, combination)){
        kEdgemin++;
    }

    std::cout<< "Done : KEdgemin = " << kEdgemin << "\n Combinaison :";

    for(const auto l : m_vecKEdgeMin){
        std::cout << "\n\t[ " << l->getStartNode()->getUid() << " , " << l->getEndNode()->getUid() << " ]";
    }

    std::cout << "\n\n";

    processedKEdgemin();
}

void Algorithm::processedKEdgemin(){
    if(!m_vecKEdgeMin.empty()){
        for(auto l : m_vecKEdgeMin){
            l->setProcessed(true);
        }
    }
}
