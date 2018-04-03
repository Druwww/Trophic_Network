#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>
#include <algorithm>

#include "Node.h"
#include "Vertex.h"

typedef std::pair<Node*, std::vector<Vertex*> > data;

class Graph{
    private:
        std::vector<data> m_data;
        std::vector<Vertex*> m_vertices;

        int getIndexByUid(const std::string& uid) const;

    public:
        Graph();
        ~Graph();

        Node* getNodeByUid(const std::string& uid) const;

        void connect(const std::string& uid1, const std::string& uid2, void* data=nullptr);
        void connect(Node* node1, Node* node2, void* data=nullptr);
        int addNode(Node* node);
        bool hasNode(Node* node) const;

        int getOrder() const;
        std::vector<Vertex*> getConnections(const std::string& uid) const;

        void write(std::ostream& os) const;
        void read(std::istream& is);
};


#endif
