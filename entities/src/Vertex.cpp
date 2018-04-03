#include "../include/Vertex.h"

Vertex::Vertex(){
    m_id = -1;
    m_weight = 0;
    m_active = false;
    m_processed = false;
    m_startNode = nullptr;
    m_endNode = nullptr;
}

int Vertex::getId() const{
    return m_id;
}

float Vertex::getWeight() const{
    return m_weight;
}

bool Vertex::isActive() const{
    return m_active;
}

bool Vertex::isProcessed() const{
    return m_processed;
}

Node* Vertex::getStartNode() const{
    return m_startNode;
}

Node* Vertex::getEndNode() const{
    return m_endNode;
}

void Vertex::setId(int id){
    m_id = id;
}

void Vertex::setWeight(float weight){
    m_weight = weight;
}

void Vertex::setActive(bool active){
    m_active = active;
}

void Vertex::setProcessed(bool processed){
    m_processed = processed;
}

void Vertex::setStartNode(Node* node){
    m_startNode = node;
}

void Vertex::setEndNode(Node* node){
    m_endNode = node;
}

void Vertex::write(std::ostream& os) const{
    os << m_id << " ";
    os << m_weight << " ";
    os << m_active << " ";
    os << m_processed;
}

void Vertex::read(std::istream& is){
    is >> m_id;
    is >> m_weight;
    is >> m_active;
    is >> m_processed;
}
