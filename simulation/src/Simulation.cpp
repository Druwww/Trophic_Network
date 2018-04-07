#include "../include/Simulation.h"

Simulation::Simulation(){
    m_graph = nullptr;
    m_turn = 0;
}

Simulation::Simulation(Graph* graph){
    m_graph = graph;
    m_turn = 0;
}

void Simulation::nextTurn(){
    for(unsigned int i=0 ; i<m_graph->size() ; i++){
        data d = m_graph->get(i);
        updateDataNode(d);
    }
    m_turn++;
}

void Simulation::updateDataNode(data& d) const{
    int a=0, b=0;

    NodeAttr* attr = (NodeAttr*) d.first->getData();
    if(attr==nullptr){
        return;
    }

    attr->m_quantity = attr->m_quantity + attr->m_birthRate*attr->m_quantity;

    for(auto& l : d.second.second){
        EdgeAttr* e_attr = (EdgeAttr*) l->getData();
        NodeAttr* n_attr = (NodeAttr*) l->getEndNode()->getData();
        if(e_attr!=nullptr && n_attr!=nullptr){
            a += n_attr->m_quantity * e_attr->m_survivalRate;
        }
    }

    for(auto& l : d.second.first){
        EdgeAttr* e_attr = (EdgeAttr*) l->getData();
        NodeAttr* n_attr = (NodeAttr*) l->getStartNode()->getData();
        if(e_attr!=nullptr && n_attr!=nullptr){
            b += n_attr->m_quantity * e_attr->m_survivalRate;
        }
    }

    attr->m_quantity += (a-b);
}

Graph* Simulation::getGraph() const{
    return m_graph;
}

int Simulation::getTurn() const{
    return m_turn;
}

void Simulation::setGraph(Graph* graph){
    m_graph = graph;
}

void Simulation::setTurn(int turn){
    m_turn = turn;
}
