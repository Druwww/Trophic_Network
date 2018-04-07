#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Node.h"
#include "Edge.h"

typedef std::pair<std::vector<Edge*>, std::vector<Edge*> > IO;
typedef std::pair<Node*, IO> data;

class Graph{
    private:
        std::vector<data> m_data;
        void (*m_destroyNodeData)(void*);
        void (*m_destroyEdgeData)(void*);
        void (*m_serializeNodeData)(std::ostream&, void*);
        void (*m_serializeEdgeData)(std::ostream&, void*);
        void (*m_deserializeNodeData)(std::istream&, void**);
        void (*m_deserializeEdgeData)(std::istream&, void**);

        void subtract(std::vector<Edge*>& v1, const std::vector<Edge*>& v2);

    public:
        Graph();
        Graph(const Graph& graph);
        ~Graph();

        int size() const;
        data get(int i) const;
        int getOrder() const;
        bool hasNode(Node* node) const;
        bool areConnected(Node* node1, Node* node2) const;
        int getIndexByUid(const std::string& uid) const;
        Node* getNodeByUid(const std::string& uid) const;
        IO getConnections(const std::string& uid) const;
        IO getConnections(Node* node) const;

        void connect(const std::string& uid1, const std::string& uid2, void* data=nullptr);
        void connect(Node* node1, Node* node2, void* data=nullptr);
        int addNode(Node* node);
        bool removeNode(Node* node);
        bool removeNode(const std::string& uid);
        bool removeEdge(Edge* edge);

        void setOnDestroyNodeData(void (*destroyNodeData)(void*));
        void setOnDestroyEdgeData(void (*destroyEdgeData)(void*));
        void setOnSerializeNodeData(void (*serializeNodeData)(std::ostream&, void*));
        void setOnSerializeEdgeData(void (*serializeEdgeData)(std::ostream&, void*));
        void setOnDeserializeNodeData(void (*deserializeNodeData)(std::istream&, void**));
        void setOnDeserializeEdgeData(void (*deserializeEdgeData)(std::istream&, void**));

        void print() const;
        void write(std::ostream& os) const;
        void read(std::istream& is);
};


#endif
