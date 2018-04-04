#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "../../../utils/include/utils.h"
#include <string>
#include <iostream>

class Node{
    private:
        std::string m_uid;
        bool m_processed;

        void* m_data;

    public:
        Node();
        Node(const std::string& uid);
        Node(const Node& node);

        std::string getUid() const;
        bool isProcessed() const;
        void* getData() const;

        void setProcessed(const bool& processed);
        void setData(void* data);

        void write(std::ostream& os) const;
        void read(std::istream& is);
};

#endif
