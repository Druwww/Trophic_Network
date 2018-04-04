#include "../include/Graph.h"

Graph::Graph(){
    m_destroyNodeListener = nullptr;
    m_destroyVertexListener = nullptr;
    m_serializeNodeData = nullptr;
    m_serializeVertexData = nullptr;
    m_deserializeNodeData = nullptr;
    m_deserializeVertexData = nullptr;
}

Graph::~Graph(){
    assert(m_destroyNodeListener!=nullptr && m_destroyVertexListener!=nullptr);

    for(int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getData()!=nullptr){
            (*m_destroyNodeListener)(m_data[i].first->getData());
        }
        delete m_data[i].first;
    }

    for(int i=0 ; i<m_vertices.size() ; i++){
        if(m_vertices[i]->getData()!=nullptr){
            (*m_destroyVertexListener)(m_vertices[i]->getData());
        }
        delete m_vertices[i];
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
    for(int i=0 ; i<m_data.size() ; i++){
        if(m_data[i].first->getUid()==uid){
            return i;
        }
    }
    return -1;
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

std::vector<Vertex*> Graph::getConnections(Node* node) const{
    return getConnections(node->getUid());
}

int Graph::getDegreByUid(const std::string& uid) const{
    int index = getIndexByUid(uid);
    if(index!=-1){
        return m_data[index].second.size();
    }
    return {};
}

int Graph::getDegreByNode(Node* node) const{
    return getDegreByUid(node->getUid());
}

void Graph::setOnDestroyNodeData(void (*destroyNodeListener)(void*)){
    m_destroyNodeListener = destroyNodeListener;
}

void Graph::setOnDestroyVertexData(void (*destroyVertexListener)(void*)){
    m_destroyVertexListener = destroyVertexListener;
}

void Graph::setOnSerializeNodeData(void (*serializeNodeData)(std::ostream&, void*)){
    m_serializeNodeData = serializeNodeData;
}

void Graph::setOnSerializeVertexData(void (*serializeVertexData)(std::ostream&, void*)){
    m_serializeVertexData = serializeVertexData;
}

void Graph::setOnDeserializeNodeData(void (*deserializeNodeData)(std::istream&, void**)){
    m_deserializeNodeData = deserializeNodeData;
}

void Graph::setOnDeserializeVertexData(void (*deserializeVertexData)(std::istream&, void**)){
    m_deserializeVertexData = deserializeVertexData;
}

void Graph::write(std::ostream& os) const{
    assert(m_serializeNodeData!=nullptr && m_serializeVertexData!=nullptr);

    os << m_data.size() << std::endl;

    for(auto const& p : m_data){
        os << p.second.size() << std::endl;
        os << p.first->getUid() << std::endl;

        for(const auto& v : p.second){
            v->write(os);
            void* v_data = v->getData();
            os << " " << (v_data!=nullptr) << " ";
            if(v_data!=nullptr){
                (*m_serializeVertexData)(os, v_data);
                os << " ";
            }

            v->getStartNode()->write(os);
            void* sn_data = v->getStartNode()->getData();
            os << " " << (sn_data!=nullptr) << " ";
            if(sn_data!=nullptr){
                (*m_serializeNodeData)(os, sn_data);
                os << " ";
            }

            v->getEndNode()->write(os);
            void* en_data = v->getEndNode()->getData();
            os << " " << (en_data!=nullptr) << " ";
            if(en_data!=nullptr){
                (*m_serializeNodeData)(os, en_data);
            }
            os << std::endl;
        }
    }
}

void Graph::read(std::istream& is){
    assert(m_deserializeNodeData!=nullptr && m_deserializeVertexData!=nullptr);

    std::string line, uid;
    getline(is, line);
    int order = string_to_int(line);
    m_data = std::vector<data>(order);

    for(int i=0 ; i<order ; i++){
        getline(is, line);
        int length = string_to_int(line);
        getline(is, uid);

        for(int j=0 ; j<length ; j++){
            getline(is, line);
            std::stringstream ss(line);

            Vertex* vertex = new Vertex();
            Node* start = new Node();
            Node* end = new Node();
            bool has_v_data;
            bool has_sn_data;
            bool has_en_data;
            void *d;

            vertex->read(ss);
            ss >> has_v_data;
            if(has_v_data){
                (*m_deserializeVertexData)(ss, &d);
                vertex->setData(d);
            }

            start->read(ss);
            ss >> has_sn_data;
            if(has_sn_data){
                (*m_deserializeNodeData)(ss, &d);
                start->setData(d);
            }

            end->read(ss);
            ss >> has_en_data;
            if(has_en_data){
                (*m_deserializeNodeData)(ss, &d);
                end->setData(d);
            }

            vertex->setStartNode(start);
            vertex->setEndNode(end);

            m_data[i].first = (start->getUid()==uid?start:end);
            m_data[i].second.push_back(vertex);
        }
    }
}
