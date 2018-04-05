#include "../include/Graph.h"

Graph::Graph(){
    m_destroyNodeData = nullptr;
    m_destroyEdgeData = nullptr;
    m_serializeNodeData = nullptr;
    m_serializeEdgeData = nullptr;
    m_deserializeNodeData = nullptr;
    m_deserializeEdgeData = nullptr;
}

Graph::~Graph(){
    assert(m_destroyNodeData!=nullptr && m_destroyEdgeData!=nullptr);

    for(unsigned int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getData()!=nullptr){
            (*m_destroyNodeData)(m_data[i].first->getData());
        }
        delete m_data[i].first;

        std::vector<Edge*> in = m_data[i].second.first;
        for(unsigned int j=0 ; j<in.size() ; j++){
            if(in[j]->getData()!=nullptr){
                (*m_destroyEdgeData)(in[j]->getData());
            }
            delete in[j];
        }
    }
}

int Graph::size() const{
    return m_data.size();
}

data Graph::get(int i) const{
    assert(i>=0 && i<m_data.size());
    return m_data[i];
}

Node* Graph::getNodeByUid(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].first;
    }
    return nullptr;
}

int Graph::getIndexByUid(const std::string& uid) const{
    for(unsigned int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getUid()==uid){
            return i;
        }
    }
    return -1;
}

void Graph::subtract(std::vector<Edge*>& v1, const std::vector<Edge*>& v2){
    std::vector<int> index;
    for(unsigned int i=0 ; i<v1.size() ; i++){
        for(unsigned int j=0 ; j<v2.size() ; j++){
            if(v1[i]->getUid()==v2[j]->getUid()){
                index.push_back(i);
            }
        }
    }

    int j=index.size()-1;
    for(unsigned int i=0 ; i<index.size() ; i++){
        v1.erase(v1.begin() + index[j--]);
    }
}

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

    Edge* connection = new Edge();
    connection->setStartNode(node1);
    connection->setEndNode(node2);
    connection->setData(data);
    m_data[index1].second.second.push_back(connection);
    m_data[index2].second.first.push_back(connection);
}

int Graph::addNode(Node* node){
    data d = std::make_pair(node, std::make_pair(std::vector<Edge*>(), std::vector<Edge*>()));
    m_data.push_back(d);
    return m_data.size()-1;
}

bool Graph::removeNode(Node* node){
    return removeNode(node->getUid());
}

bool Graph::removeNode(const std::string& uid){
    assert(m_destroyNodeData!=nullptr && m_destroyEdgeData!=nullptr);

    int index = getIndexByUid(uid);
    if(index==-1){
        return false;
    }

    Node* node = m_data[index].first;
    IO io = m_data[index].second;
    m_data.erase(m_data.begin() + index);

    for(unsigned int i=0 ; i<m_data.size() ; i++){
        subtract(m_data[i].second.first, io.first);
        subtract(m_data[i].second.first, io.second);
        subtract(m_data[i].second.second, io.first);
        subtract(m_data[i].second.second, io.second);
    }

    for(unsigned int i=0 ; i<io.first.size() ; i++){
        (*m_destroyEdgeData)(io.first[i]->getData());
        delete io.first[i];
    }

    for(unsigned int i=0 ; i<io.second.size() ; i++){
        (*m_destroyEdgeData)(io.second[i]->getData());
        delete io.second[i];
    }

    (*m_destroyNodeData)(node->getData());
    delete node;

    return true;
}

bool Graph::hasNode(Node* node) const{
    for(const auto& p : m_data){
        if(p.first->getUid()==node->getUid()){
            return true;
        }
    }
    return false;
}

bool Graph::areConnected(Node* node1, Node* node2) const{
    int index = getIndexByUid(node1->getUid());
    if(index==-1){
        return false;
    }

    std::vector<Edge*> out = m_data[index].second.second;
    for(const auto& e : out){
        if(e->getEndNode()->getUid()==node2->getUid()){
            return true;
        }
    }
    return false;
}

int Graph::getOrder() const{
    return m_data.size();
}

IO Graph::getConnections(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].second;
    }
    return {};
}

IO Graph::getConnections(Node* node) const{
    return getConnections(node->getUid());
}

void Graph::setOnDestroyNodeData(void (*destroyNodeData)(void*)){
    m_destroyNodeData = destroyNodeData;
}

void Graph::setOnDestroyEdgeData(void (*destroyEdgeData)(void*)){
    m_destroyEdgeData = destroyEdgeData;
}

void Graph::setOnSerializeNodeData(void (*serializeNodeData)(std::ostream&, void*)){
    m_serializeNodeData = serializeNodeData;
}

void Graph::setOnSerializeEdgeData(void (*serializeEdgeData)(std::ostream&, void*)){
    m_serializeEdgeData = serializeEdgeData;
}

void Graph::setOnDeserializeNodeData(void (*deserializeNodeData)(std::istream&, void**)){
    m_deserializeNodeData = deserializeNodeData;
}

void Graph::setOnDeserializeEdgeData(void (*deserializeEdgeData)(std::istream&, void**)){
    m_deserializeEdgeData = deserializeEdgeData;
}

void Graph::write(std::ostream& os) const{
    assert(m_serializeNodeData!=nullptr && m_serializeEdgeData!=nullptr);

    os << m_data.size() << std::endl;
    for(auto const& p : m_data){
        Node* node = p.first;
        void* data = node->getData();
        node->write(os);
        os << " " << (data!=nullptr);
        if(data!=nullptr){
            os << " ";
            (*m_serializeNodeData)(os, data);
        }
        os << std::endl;
    }

    for(auto const& p : m_data){
        os << p.second.first.size() << std::endl;
        os << p.first->getUid() << std::endl;

        for(const auto& edge : p.second.first){
            void* data = edge->getData();
            os << edge->getStartNode()->getUid() << " ";
            edge->write(os);
            os << " " << (data!=nullptr);
            if(data!=nullptr){
                os << " ";
                (*m_serializeEdgeData)(os, data);
            }
            os << std::endl;
        }
    }
}

void Graph::read(std::istream& is){
    assert(m_deserializeNodeData!=nullptr && m_deserializeEdgeData!=nullptr);

    std::string line, uid, uid2;
    getline(is, line);
    int order = string_to_int(line);
    m_data = std::vector<data>(order);

    for(unsigned int i=0 ; i<order ; i++){
        getline(is, line);
        std::stringstream ss(line);
        Node* node = new Node();
        bool hasData;

        node->read(ss);
        ss >> hasData;
        if(hasData){
            void *d;
            (*m_deserializeNodeData)(ss, &d);
            node->setData(d);
        }

        m_data[i].first = node;
    }

    for(unsigned int i=0 ; i<order ; i++){
        getline(is, line);
        int length = string_to_int(line);
        getline(is, uid);

        Node* endNode = getNodeByUid(uid);

        for(unsigned int j=0 ; j<length ; j++){
            getline(is, line);
            std::stringstream ss(line);
            Edge* edge = new Edge();
            bool hasData;

            ss >> uid2;
            edge->read(ss);
            ss >> hasData;
            if(hasData){
                void* d;
                (*m_deserializeEdgeData)(ss, &d);
                edge->setData(d);
            }

            Node* startNode = getNodeByUid(uid2);
            edge->setStartNode(startNode);
            edge->setEndNode(endNode);

            m_data[i].second.first.push_back(edge);
            m_data[getIndexByUid(uid2)].second.second.push_back(edge);
        }
    }
}
