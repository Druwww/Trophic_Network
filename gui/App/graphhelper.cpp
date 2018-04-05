#include "graphhelper.h"

void onDeleteNode(void* data){
    NodeAttr* animal = (NodeAttr*) data;
    delete animal;
}

void onDeleteEdge(void* data){
    EdgeAttr* law = (EdgeAttr*) data;
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    NodeAttr* animal = (NodeAttr*) data;
    animal->write(os);
}

void onSerializeEdge(std::ostream& os, void* data){
    EdgeAttr* law = (EdgeAttr*) data;
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    NodeAttr* animal = new NodeAttr();
    animal->read(is);
    *data = animal;
}

void onDeserializeEdge(std::istream& is, void** data){
    EdgeAttr* law = new EdgeAttr();
    law->read(is);
    *data = law;
}
