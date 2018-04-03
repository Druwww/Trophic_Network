#include "../include/Graph.h"

Graph::Graph(){
    m_destroyNodeListener = nullptr;
    m_destroyVertexListener = nullptr;
}

Graph::~Graph(){
    for(int i=0 ; i<m_data.size() ; i++){
        if(m_destroyNodeListener!=nullptr){
            (*m_destroyNodeListener)(m_data[i].first->getData());
        }
        delete m_data[i].first;
    }

    for(int i=0 ; i<m_vertices.size() ; i++){
        if(m_destroyVertexListener!=nullptr){
            (*m_destroyVertexListener)(m_vertices[i]->getData());
        }
        delete m_vertices[i];
    }
}

Node* Graph::getNodeByUid(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].first;
    }
    return nullptr;
}

int Graph::getIndexByUid(const std::string& uid) const{
    for(int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getUid()==uid){
            return i;
        }
    }
    return -1;
}

#include <iostream>
void Graph::connect(const std::string& uid1, const std::string& uid2, void* data){
    int index1 = getIndexByUid(uid1);
    int index2 = getIndexByUid(uid2);
    Node* node1 = index1==-1?new Node(uid1):m_data[index1].first;
    Node* node2 = index2==-1?new Node(uid2):m_data[index2].first;
    connect(node1, node2, data);
}

void Graph::connect(Node* node1, Node* node2, void* data){
    int index1 = hasNode(node1)?getIndexByUid(node1->getUid()):addNode(node1);
    int index2 = hasNode(node2)?getIndexByUid(node2->getUid()):addNode(node2);

    Vertex* connection = new Vertex();
    connection->setStartNode(node1);
    connection->setEndNode(node2);
    connection->setData(data);
    m_data[index1].second.push_back(connection);
    m_data[index2].second.push_back(connection);
    m_vertices.push_back(connection);
}

int Graph::addNode(Node* node){
    data d = std::make_pair(node, std::vector<Vertex*>());
    m_data.push_back(d);
    return m_data.size()-1;
}

bool Graph::hasNode(Node* node) const{
    for(const auto& p : m_data){
        if(p.first->getUid()==node->getUid()){
            return true;
        }
    }
    return false;
}

int Graph::getOrder() const{
    return m_data.size();
}

std::vector<Vertex*> Graph::getConnections(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].second;
    }
    return {};
}

void Graph::setOnDestroyNodeData(void (*destroyNodeListener)(void*)){
    m_destroyNodeListener = destroyNodeListener;
}

void Graph::setOnDestroyVertexData(void (*destroyVertexListener)(void*)){
    m_destroyVertexListener = destroyVertexListener;
}

void Graph::write(std::ostream& os) const{
    os << m_data.size() << std::endl;

    for(auto const& p : m_data){
        os << p.second.size() << std::endl;
        for(const auto& v : p.second){
            v->write(os);
            os << " ";
            v->getStartNode()->write(os);
            os << " ";
            v->getEndNode()->write(os);
            os << std::endl;
        }
    }
}

void Graph::read(std::istream& is){
    std::string line;
    getline(is, line);
    int order = std::stoi(line);
    m_data = std::vector<data>(order);

    for(int i=0 ; i<order ; i++){
        getline(is, line);
        int length = std::stoi(line);
        for(int j=0 ; j<length ; j++){
            getline(is, line);
            std::stringstream ss(line);

            Vertex* vertex = new Vertex();
            Node* start = new Node();
            Node* end = new Node();

            vertex->read(ss);
            start->read(ss);
            end->read(ss);
            vertex->setStartNode(start);
            vertex->setEndNode(end);

            m_data[i].first = start;
            m_data[i].second.push_back(vertex);
        }
    }
}
