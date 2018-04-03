#include "../include/GraphData.h"

GraphData::GraphData(){}

GraphData::~GraphData(){
    for(int i=0 ; i<m_data.size() ; i++){
        delete m_data[i].first;
        for(int j=0 ; j<m_data[i].second.size() ; j++){
            delete m_data[i].second[j];
        }
    }
}

Node* GraphData::getNodeByUid(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].first;
    }
    return nullptr;
}

int GraphData::getIndexByUid(const std::string& uid) const{
    for(int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getUid()==uid){
            return i;
        }
    }
    return -1;
}

void GraphData::connect(const std::string& uid1, const std::string& uid2){
    Node* node1 = getNodeByUid(uid1);
    Node* node2 = getNodeByUid(uid2);
    if(node1==nullptr){
        node1 = addNode(Node(uid1));
    }
    if(node2==nullptr){
        node2 = addNode(Node(uid2));
    }

    Vertex* connection = new Vertex();
    connection->setStartNode(node1);
    connection->setEndNode(node2);
    int index1 = getIndexByUid(node1->getUid());
    int index2 = getIndexByUid(node2->getUid());
    m_data[index1].second.push_back(connection);
    m_data[index2].second.push_back(connection);
}

Node* GraphData::addNode(const Node& node){
    if(!hasNode(node)){
        Node* n = new Node(node);
        std::vector<Vertex*> empty;
        data d = std::make_pair(n, empty);
        m_data.push_back(d);
        return n;
    }
    return nullptr;
}

bool GraphData::hasNode(const Node& node) const{
    for(const auto& p : m_data){
        if(p.first->getUid()==node.getUid()){
            return true;
        }
    }
    return false;
}

int GraphData::getOrder() const{
    return m_data.size();
}

void GraphData::write(std::ostream& os) const{
    os << m_data.size() << std::endl;
    // for(const auto& p : m_data){
    //     p.first->write(os);
    //     os << std::endl;
    // }

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

void GraphData::read(std::istream& is){
    std::string line;
    getline(is, line);
    int order = std::stoi(line);
    m_data = std::vector<data>(order);

    // for(int i=0 ; i<order ; i++){
    //     Node *node = new Node();
    //     node->read(is);
    //     m_data[i].first = node;
    // }

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
