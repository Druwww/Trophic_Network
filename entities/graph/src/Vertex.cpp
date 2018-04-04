#include "../include/Vertex.h"

Vertex::Vertex(){
    m_uid = genUid();
    m_weight = 0;
    m_active = false;
    m_processed = false;
    m_startNode = nullptr;
    m_endNode = nullptr;
    m_data = nullptr;
}

std::string Vertex::getUid() const{
    return m_uid;
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

void* Vertex::getData() const{
    return m_data;
}

void Vertex::setUid(const std::string& uid){
    m_uid = uid;
}

void Vertex::setWeight(const float& weight){
    m_weight = weight;
}

void Vertex::setActive(const bool& active){
    m_active = active;
}

void Vertex::setProcessed(const bool& processed){
    m_processed = processed;
}

void Vertex::setStartNode(Node* node){
    m_startNode = node;
}

void Vertex::setEndNode(Node* node){
    m_endNode = node;
}

void Vertex::setData(void* data){
    m_data = data;
}

void Vertex::write(std::ostream& os) const{
    os << m_uid << " ";
    os << m_weight << " ";
    os << m_active << " ";
    os << m_processed;
}

void Vertex::read(std::istream& is){
    is >> m_uid;
    is >> m_weight;
    is >> m_active;
    is >> m_processed;
}
