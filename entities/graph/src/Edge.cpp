#include "../include/Edge.h"

Edge::Edge(){
    m_uid = genUid();
    m_weight = 0;
    m_active = true;
    m_processed = false;
    m_startNode = nullptr;
    m_endNode = nullptr;
    m_data = nullptr;
}

std::string Edge::getUid() const{
    return m_uid;
}

float Edge::getWeight() const{
    return m_weight;
}

bool Edge::isActive() const{
    return m_active;
}

bool Edge::isProcessed() const{
    return m_processed;
}

Node* Edge::getStartNode() const{
    return m_startNode;
}

Node* Edge::getEndNode() const{
    return m_endNode;
}

void* Edge::getData() const{
    return m_data;
}

void Edge::setUid(const std::string& uid){
    m_uid = uid;
}

void Edge::setWeight(const float& weight){
    m_weight = weight;
}

void Edge::setActive(const bool& active){
    m_active = active;
}

void Edge::setProcessed(const bool& processed){
    m_processed = processed;
}

void Edge::setStartNode(Node* node){
    m_startNode = node;
}

void Edge::setEndNode(Node* node){
    m_endNode = node;
}

void Edge::setData(void* data){
    m_data = data;
}

void Edge::write(std::ostream& os) const{
    os << m_uid << " ";
    os << m_weight << " ";
    os << m_active << " ";
    os << m_processed;
}

void Edge::read(std::istream& is){
    is >> m_uid;
    is >> m_weight;
    is >> m_active;
    is >> m_processed;
}
