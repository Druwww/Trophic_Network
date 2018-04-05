#include "../include/Node.h"

Node::Node(){
    m_uid = genUid();
    m_processed = false;
    m_data = nullptr;
}

Node::Node(const std::string& uid){
    m_uid = uid;
    m_processed = false;
    m_data = nullptr;
}

Node::Node(const Node& node){
    m_uid = node.m_uid;
    m_processed = node.m_processed;
    m_data = node.m_data;
}

std::string Node::getUid() const{
    return m_uid;
}

bool Node::isProcessed() const{
    return m_processed;
}

void* Node::getData() const{
    return m_data;
}

void Node::setProcessed(const bool& processed){
    m_processed = processed;
}

void Node::setData(void* data){
    m_data = data;
}

void Node::write(std::ostream& os) const{
    os << m_uid << " " << m_processed;
}

void Node::read(std::istream& is){
    is >> m_uid;
    is >> m_processed;
}