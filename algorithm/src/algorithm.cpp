#include "../include/algorithm.h"

void onDeleteNode(void* data){
    NodeAttr* attr = (NodeAttr*) data;
    delete attr;
}

void onDeleteEdge(void* data){
    EdgeAttr* attr = (EdgeAttr*) data;
    delete attr;
}

void onSerializeNode(std::ostream& os, void* data){
    NodeAttr* attr = (NodeAttr*) data;
    attr->write(os);
}

void onSerializeEdge(std::ostream& os, void* data){
    EdgeAttr* attr = (EdgeAttr*) data;
    attr->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    NodeAttr* attr = new NodeAttr();
    attr->read(is);
    *data = attr;
}

void onDeserializeEdge(std::istream& is, void** data){
    EdgeAttr* attr = new EdgeAttr();
    attr->read(is);
    *data = attr;
}

void onCopyNodeData(void* data, void** copy){
    NodeAttr* attr = (NodeAttr*) data;
    *copy = new NodeAttr(*attr);
}

void onCopyEdgeData(void* data, void** copy){
    EdgeAttr* attr = (EdgeAttr*) data;
    *copy = new EdgeAttr(*attr);
}


Algorithm::Algorithm(){
    m_graph = nullptr;
}

Algorithm::~Algorithm(){
    //dtor
}

Algorithm::Algorithm(Graph* graph): m_graph(graph){
    //ctor
}

////Fonction pr que la creation dans le graphe fonctionne

//////////////////////////////////////////////////////////////



void Algorithm::clearAllMarck(){

    for(int i = 0; i < m_graph->size(); i++){
        data d = m_graph->get(i);
        d.first->setProcessed(false);
        d.first->setGroup(0);
        for(auto & v : d.second.first){
            v->setProcessed(false);
        }
        for(auto & v : d.second.second){
            v->setProcessed(false);
        }
    }
}

void Algorithm::clearAllMarck(Graph& graph){

    for(int i = 0; i < graph.size(); i++){
        data d = graph.get(i);
        d.first->setProcessed(false);
        d.first->setGroup(0);
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

int Algorithm::updateEdgesActive(Graph& graph){

    int nb_changement = 0;

    // clearAllMarck();

    for(int i = 0; i < graph.size(); i++){
        data d =graph.get(i);

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

    // clearAllMarck();

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
    updateEdgesActive(*m_graph);
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

    processedEdgeByPointeur(m_vecLiaisonGraph, m_vecIndexCombinaison);
}

void Algorithm::processedEdgeByPointeur(const std::vector<Edge*>& vecEdge, const std::vector<int>& vecIndex){
    if(!vecIndex.empty()){
        for(auto l : vecIndex){
            Edge* edge = vecEdge[l];
            edge->setProcessed(true);
        }
    }
}

void Algorithm::BFSConnexity(data d, Graph& graphProssed, bool normal){
    d.first->setProcessed(true);

    if(normal){
        for(auto& l : d.second.second){
            if(!l->getEndNode()->isProcessed() && l->isActive()){
                BFSConnexity(graphProssed.get(graphProssed.getIndexByUid(l->getEndNode()->getUid())), graphProssed, normal);
            }
        }
    }
    else{
        for(auto& l : d.second.first){
            if(!l->getStartNode()->isProcessed() && l->isActive()){
                BFSConnexity(graphProssed.get(graphProssed.getIndexByUid(l->getStartNode()->getUid())), graphProssed, normal);
            }
        }
    }
}

void Algorithm::emptyConnexity(int numero, Graph& graph1, Graph& graph2, Graph& graphData){

    for(int i = 0; i < graphData.size(); i++){
        data dEtude = graphData.get(i);

        if(graph1.get(i).first->isProcessed() && graph2.get(i).first->isProcessed()){
            dEtude.first->setGroup(numero);
        }
    }

    clearAllMarck(graph1);
    clearAllMarck(graph2);
}

int Algorithm::testStillConnexe0(Graph& graph){
    for(int i = 0; i < graph.size(); i++){
        if(graph.get(i).first->getGroup() == 0){
            return i;
        }
    }

    return -1;
}

void Algorithm::algoForteConnexity(Graph& graphData){

    for(int i = 0; i < graphData.size(); i++){
        graphData.get(i).first->setGroup(0);
    }

    updateEdgesActive(graphData);

    ////////////////////Changer le constructeur
    Graph graph1(graphData);
    Graph graph2(graphData);
    /////////////////////

    int numeroGroupe = 0;

    while(testStillConnexe0(graphData) != -1){
        int i = testStillConnexe0(graphData);

        numeroGroupe++;

        BFSConnexity(graph1.get(i), graph1, true);
        BFSConnexity(graph2.get(i), graph2, false);

        emptyConnexity(numeroGroupe, graph1, graph2, graphData);
    }


    std::cout << "Done !\n";
}

bool Algorithm::testIdenticForteConnexity(Graph& graph1, Graph& graph2){

    for(int i = 0; i < graph1.size(); i++){
        if(graph1.get(i).first->getGroup() != graph2.get(i).first->getGroup()){
            return false;
        }
    }
    return true;
}

//Code inspiré puis repris de : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
bool Algorithm::goKEdgeminConnexity(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination) {
    if (k == 0) {
      return testCombinaisonKEdgeminConnexity(combination);
    }
    for (int i = offset; i <= vecIndex.size() - k; ++i) {
      combination.push_back(vecIndex[i]);

      if(goKEdgeminConnexity(i+1, k-1, vecIndex, combination)){
          reviveEdgeByIndex(combination);
          return true;
      }
      combination.pop_back();
    }

    return false;

}

bool Algorithm::testCombinaisonKEdgeminConnexity(std::vector<int> vectest){

    std::cout << "\tTest : ";
    for(auto l : vectest){
        std::cout << " " << l;
    }
    std::cout << "\n";

    killEdgeByIndex(vectest);


    //////////////////Changer constr
    Graph graphTest(*m_graph);

    algoForteConnexity(graphTest);

    std::cout << "Coucou2\n";

    bool resul = testIdenticForteConnexity(*m_graph, graphTest);
    std::cout << "\tResulte : " << resul << "\n";
    reviveEdgeByIndex(vectest);

    return resul;
}

void Algorithm::findKEdgeminConnexity(){

    std::vector<int> vecIndex;
    std::vector<int> combination;

    clearVecteur<Edge*>(m_vecLiaisonGraph);
    clearVecteur<Edge*>(m_vecKEdgeMin);

    clearAllMarck(*m_graph);

    algoForteConnexity(*m_graph);

    std::cout << "Coucou1\n";

    makeVecEdgeGraph();

    for(int i = 0; i < m_vecLiaisonGraph.size(); i++){
        vecIndex.push_back(i);
    }

    int KminConnexity = 1;



    std::cout << "K :" << KminConnexity << "\n";
    while(!goKEdgeminConnexity(0,KminConnexity , vecIndex, combination)){
        KminConnexity ++;
        std::cout << "K :" << KminConnexity << "\n";
    }

    std::cout<< "Done : KminConnexity = " << KminConnexity  << "\n Combinaison :";

    for(const auto l : combination){
        std::cout << "\n\t[ " << m_vecLiaisonGraph[l]->getStartNode()->getUid() << " , " <<  m_vecLiaisonGraph[l]->getEndNode()->getUid() << " ]";
    }

    std::cout << "\n\n";

    processedEdgeByPointeur(m_vecLiaisonGraph,combination);
}

//Code inspiré puis repris de : https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
bool Algorithm::goKminConnexity(int offset, int k, std::vector<int> vecIndex, std::vector<int>& combination) {
    if (k == 0) {
      return testCombinaisonKminConnexity(combination);
    }
    for (int i = offset; i <= vecIndex.size() - k; ++i) {
      combination.push_back(vecIndex[i]);

      if(goKminConnexity(i+1, k-1, vecIndex, combination)){
          m_vecIndexCombinaison = combination;
          ReviveNodeAttrsByIndex(combination);
          return true;
      }
      combination.pop_back();
    }

    return false;
}

bool Algorithm::testCombinaisonKminConnexity(std::vector<int> vectest){
    killNodeAttrsByIndex(vectest);
    updateEdgesActive(*m_graph);
    //////////////////Changer constr
    Graph graphTest(*m_graph);

    algoForteConnexity(graphTest);

    bool resul = testIdenticForteConnexity(*m_graph, graphTest);
    ReviveNodeAttrsByIndex(vectest);
    updateEdgesActive(*m_graph);

    return resul;
}

void Algorithm::findKminConnexity(){

    clearAllMarck(*m_graph);

    algoForteConnexity(*m_graph);

    std::vector<int> vecIndex;
    std::vector<int> combination;

    clearVecteur<int>(m_vecIndexCombinaison);

    for(int i = 0; i < m_graph->size(); i++){
        vecIndex.push_back(i);
    }

    int kmin = 1;

    while(!goKminConnexity(0,kmin, vecIndex, combination)){
        kmin++;
    }

    std::cout<< "Done : Kmin = " << kmin << "\n Combinaison : [ ";

    for(const auto l : m_vecIndexCombinaison){
        std::cout << l << " ,";
    }

    std::cout << "]\n\n";

    processedKmin();
}
