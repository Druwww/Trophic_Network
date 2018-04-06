#include "../include/Simulation.h"

Simulation::Simulation() : m_graph(nullptr), m_turn(0){
    //ctor
}

Simulation::Simulation(Graph* graph) : m_graph(graph), m_turn(0){
    //ctor
}

Simulation::~Simulation(){
    //dtor
}

int Simulation::numberDegreEatNode(Node* node){
    return (m_graph->get(m_graph->getIndexByUid(node->getUid()))).second.second.size();
}

template <typename T>
void Simulation::clearVecteur(std::vector<T>& vec){
    while(!vec.empty()){
        vec.pop_back();
    }
}

void Simulation::generateVecIndexOrdre(){
    clearVecteur(m_vecIndexOrdre);

    for(int i = 0; i < m_graph->size(); i++){
        m_vecIndexOrdre.push_back(i);
    }

    for(int i = 0; i < m_graph->size(); i++){
        for(int j = 0; j < m_graph->size() - 1 ; j++){
            if(  numberDegreEatNode(m_graph->get(m_vecIndexOrdre[j]).first) > numberDegreEatNode(m_graph->get(m_vecIndexOrdre[j + 1]).first)){
                int tempo = m_vecIndexOrdre[j];
                m_vecIndexOrdre[j] = m_vecIndexOrdre[j+1];
                m_vecIndexOrdre[j+1] = tempo;
            }
        }
    }
    // std::cout << "Ordre : \n";
    // for(auto l : m_vecIndexOrdre){
    //     std::cout << "\t" << l << "\n";
    // }
    //
    // std::cout << "\n\n";
}

void Simulation::nextYearNode(Node* nodeUpdate){
    NodeAttr* dataNode = nodeUpdate->getData;

    ///EQUA MISE A JOUR

}

void Simulation::nextYearNodes(){

}
