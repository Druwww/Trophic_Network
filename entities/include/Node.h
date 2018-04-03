#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "../../utils/include/utils.h"
#include <string>
#include <iostream>

class Node{
    private:
        std::string m_uid;
        bool m_processed;

    public:
        Node();
        Node(const std::string& uid);
        Node(const Node& node);

        std::string getUid() const;
        bool isProcessed() const;

        void setProcessed(bool processed);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
