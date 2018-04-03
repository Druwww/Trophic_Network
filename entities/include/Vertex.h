#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include "Node.h"

class Vertex{
    private:
        int m_id;
        float m_weight;
        bool m_active;
        bool m_processed;

        Node* m_startNode;
        Node* m_endNode;

    public:
        Vertex();

        int getId() const;
        float getWeight() const;
        bool isActive() const;
        bool isProcessed() const;
        Node* getStartNode() const;
        Node* getEndNode() const;

        void setId(int id);
        void setWeight(float weight);
        void setActive(bool active);
        void setProcessed(bool processed);
        void setStartNode(Node* node);
        void setEndNode(Node* node);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
