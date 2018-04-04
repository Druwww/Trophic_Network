#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Node.h"
#include "Edge.h"

typedef std::pair<Node*, std::vector<Edge*> > data;

class Graph{
    private:
        std::vector<data> m_data;
        std::vector<Edge*> m_edges;
        void (*m_destroyNodeListener)(void*);
        void (*m_destroyEdgeListener)(void*);
        void (*m_serializeNodeData)(std::ostream&, void*);
        void (*m_serializeEdgeData)(std::ostream&, void*);
        void (*m_deserializeNodeData)(std::istream&, void**);
        void (*m_deserializeEdgeData)(std::istream&, void**);

        int getIndexByUid(const std::string& uid) const;

    public:
        Graph();
        ~Graph();

        int size() const;
        data get(int i) const;
        int getOrder() const;
        bool hasNode(Node* node) const;
        Node* getNodeByUid(const std::string& uid) const;
        std::vector<Edge*> getEdges() const;
        std::vector<Edge*> getConnections(const std::string& uid) const;
        std::vector<Edge*> getConnections(Node* node) const;

        void connect(const std::string& uid1, const std::string& uid2, void* data=nullptr);
        void connect(Node* node1, Node* node2, void* data=nullptr);
        int addNode(Node* node);

        void setOnDestroyNodeData(void (*destroyNodeListener)(void*));
        void setOnDestroyEdgeData(void (*destroyEdgeListener)(void*));
        void setOnSerializeNodeData(void (*serializeNodeData)(std::ostream&, void*));
        void setOnSerializeEdgeData(void (*serializeEdgeData)(std::ostream&, void*));
        void setOnDeserializeNodeData(void (*deserializeNodeData)(std::istream&, void**));
        void setOnDeserializeEdgeData(void (*deserializeEdgeData)(std::istream&, void**));

        void write(std::ostream& os) const;
        void read(std::istream& is);
};


#endif
