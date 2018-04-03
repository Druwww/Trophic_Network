#ifndef GRAPHDATA_H_INCLUDED
#define GRAPHDATA_H_INCLUDED

#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Node.h"
#include "Vertex.h"

typedef std::pair<Node*, std::vector<Vertex*> > data;

class GraphData{
    private:
        std::vector<data> m_data;

        Node* getNodeByUid(const std::string& uid) const;
        int getIndexByUid(const std::string& uid) const;

    public:
        GraphData();
        ~GraphData();

        void connect(const std::string& uid1, const std::string& uid2);
        Node* addNode(const Node& node);
        bool hasNode(const Node& node) const;

        int getOrder() const;

        void write(std::ostream& os) const;
        void read(std::istream& is);
};


#endif
