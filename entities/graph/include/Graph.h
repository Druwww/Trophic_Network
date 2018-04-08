#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Node.h"
#include "Edge.h"
#include "../../data/include/DataInterface.h"

typedef std::pair<std::vector<Edge*>, std::vector<Edge*> > IO;
typedef std::pair<Node*, IO> data;

class Graph{
    private:
        std::vector<data> m_data;
        DataInterface m_nodeItf;
        DataInterface m_edgeItf;

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
        DataInterface* getNodeInterface();
        DataInterface* getEdgeInterface();

        void connect(const std::string& uid1, const std::string& uid2, void* data=nullptr);
        void connect(Node* node1, Node* node2, void* data=nullptr);
        int addNode(Node* node);
        bool removeNode(Node* node);
        bool removeNode(const std::string& uid);
        bool removeEdge(Edge* edge);

        void print() const;
        void write(std::ostream& os) const;
        void read(std::istream& is);
};


#endif
