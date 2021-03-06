#include "../include/Graph.h"

Graph::Graph(){}

Graph::Graph(const Graph& graph){
    m_nodeItf = graph.m_nodeItf;
    m_edgeItf = graph.m_edgeItf;

    m_data.resize(graph.m_data.size());
    for(unsigned int i=0 ; i<m_data.size() ; i++){
        Node* node = new Node(*graph.m_data[i].first, m_nodeItf.m_copyData);
        m_data[i].first = node;
    }

    for(unsigned int i=0 ; i<m_data.size() ; i++){
        IO io = graph.m_data[i].second;
        for(unsigned int j=0 ; j<io.first.size() ; j++){
            Edge* edge = new Edge(*io.first[j], m_edgeItf.m_copyData);
            int startNodeIndex = getIndexByUid(edge->getStartNode()->getUid());
            edge->setStartNode(m_data[startNodeIndex].first);
            edge->setEndNode(m_data[i].first);
            m_data[i].second.first.push_back(edge);
            m_data[startNodeIndex].second.second.push_back(edge);
        }
    }
}

Graph::~Graph(){
    assert(m_nodeItf.m_destroyData!=nullptr
        && m_edgeItf.m_destroyData!=nullptr);

    for(unsigned int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getData()!=nullptr){
            (*m_nodeItf.m_destroyData)(m_data[i].first->getData());
        }
        delete m_data[i].first;

        std::vector<Edge*> in = m_data[i].second.first;
        for(unsigned int j=0 ; j<in.size() ; j++){
            if(in[j]->getData()!=nullptr){
                (*m_edgeItf.m_destroyData)(in[j]->getData());
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
    assert(m_nodeItf.m_destroyData!=nullptr
        && m_edgeItf.m_destroyData!=nullptr);

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
        (*m_edgeItf.m_destroyData)(io.first[i]->getData());
        delete io.first[i];
    }

    for(unsigned int i=0 ; i<io.second.size() ; i++){
        (*m_edgeItf.m_destroyData)(io.second[i]->getData());
        delete io.second[i];
    }

    (*m_nodeItf.m_destroyData)(node->getData());
    delete node;

    return true;
}

bool Graph::removeEdge(Edge* edge){
    Node* start = edge->getStartNode();
    Node* end = edge->getEndNode();
    int startIndex = getIndexByUid(start->getUid());
    int endIndex = getIndexByUid(end->getUid());

    if(startIndex==-1 || endIndex==-1){
        return false;
    }

    int c = 0;

    for(unsigned int i=0 ; i<m_data[startIndex].second.second.size() ; i++){
        if(m_data[startIndex].second.second[i]->getUid()==edge->getUid()){
            m_data[startIndex].second.second.erase(
                m_data[startIndex].second.second.begin() + i
            );
            c++;
            break;
        }
    }

    for(unsigned int i=0 ; i<m_data[endIndex].second.first.size() ; i++){
        if(m_data[endIndex].second.first[i]->getUid()==edge->getUid()){
            m_data[endIndex].second.first.erase(
                m_data[endIndex].second.first.begin() + i
            );
            c++;
            break;
        }
    }

    return c==2;
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

DataInterface* Graph::getNodeInterface(){
    return &m_nodeItf;
}

DataInterface* Graph::getEdgeInterface(){
    return &m_edgeItf;
}

void Graph::print() const{
    for(unsigned int i=0 ; i<m_data.size() ; i++){
        data d = m_data[i];
        std::cout << d.first->getUid() << std::endl;
        for(const auto& e : d.second.first){
            std::cout << "\t<- " << e->getUid() << " ";
            std::cout << e->getStartNode()->getUid() << std::endl;
        }
        for(const auto& e : d.second.second){
            std::cout << "\t-> " << e->getUid() << " ";
            std::cout << e->getEndNode()->getUid() << std::endl;
        }
    }
}

void Graph::write(std::ostream& os) const{
    assert(m_nodeItf.m_serializeData!=nullptr
        && m_edgeItf.m_serializeData!=nullptr);

    os << m_data.size() << std::endl;
    for(auto const& p : m_data){
        Node* node = p.first;
        void* data = node->getData();
        node->write(os);
        os << " " << (data!=nullptr);
        if(data!=nullptr){
            os << " ";
            (*m_nodeItf.m_serializeData)(os, data);
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
                (*m_edgeItf.m_serializeData)(os, data);
            }
            os << std::endl;
        }
    }
}

void Graph::read(std::istream& is){
    assert(m_nodeItf.m_deserializeData!=nullptr
        && m_edgeItf.m_deserializeData!=nullptr);

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
            (*m_nodeItf.m_deserializeData)(ss, &d);
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
                (*m_edgeItf.m_deserializeData)(ss, &d);
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
