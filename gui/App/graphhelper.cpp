#include "graphhelper.h"

void onDeleteNode(void* data){
    NodeAttr* attr = (NodeAttr*) data;
    delete attr;
}

void onDeleteEdge(void* data){
    EdgeAttr* law = (EdgeAttr*) data;
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    NodeAttr* attr = (NodeAttr*) data;
    attr->write(os);
}

void onSerializeEdge(std::ostream& os, void* data){
    EdgeAttr* law = (EdgeAttr*) data;
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    NodeAttr* attr = new NodeAttr();
    attr->read(is);
    *data = attr;
}

void onDeserializeEdge(std::istream& is, void** data){
    EdgeAttr* law = new EdgeAttr();
    law->read(is);
    *data = law;
}
