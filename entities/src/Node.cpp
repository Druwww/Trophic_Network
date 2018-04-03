#include "../include/Node.h"

Node::Node(){
    m_uid = genUid();
    m_processed = false;
}

Node::Node(const std::string& uid){
    m_uid = uid;
    m_processed = false;
}

Node::Node(const Node& node){
    m_uid = node.m_uid;
    m_processed = node.m_processed;
}

std::string Node::getUid() const{
    return m_uid;
}

bool Node::isProcessed() const{
    return m_processed;
}

void Node::setProcessed(bool processed){
    m_processed = processed;
}

void Node::write(std::ostream& os) const{
    os << m_uid << " " << m_processed;
}

void Node::read(std::istream& is){
    is >> m_uid;
    is >> m_processed;
}
