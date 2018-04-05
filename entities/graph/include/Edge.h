#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include "Node.h"
#include "../../../utils/include/utils.h"

class Edge{
    private:
        std::string m_uid;
        float m_weight;
        bool m_active;
        bool m_processed;

        Node* m_startNode;
        Node* m_endNode;

        void* m_data;

    public:
        Edge();

        std::string getUid() const;
        float getWeight() const;
        bool isActive() const;
        bool isProcessed() const;
        Node* getStartNode() const;
        Node* getEndNode() const;
        void* getData() const;

        void setUid(const std::string& uid);
        void setWeight(const float& weight);
        void setActive(const bool& active);
        void setProcessed(const bool& processed);
        void setStartNode(Node* node);
        void setEndNode(Node* node);
        void setData(void* data);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
