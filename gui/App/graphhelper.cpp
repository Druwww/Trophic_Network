#include "graphhelper.h"

void onDeleteNode(void* data){
    NodeAttr* animal = (NodeAttr*) data;
    delete animal;
}

void onDeleteVertex(void* data){
    NodeAttr* law = (NodeAttr*) data;
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    NodeAttr* animal = (NodeAttr*) data;
    animal->write(os);
}

void onSerializeVertex(std::ostream& os, void* data){
    NodeAttr* law = (NodeAttr*) data;
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    NodeAttr* animal = new NodeAttr();
    animal->read(is);
    *data = animal;
}

void onDeserializeVertex(std::istream& is, void** data){
    NodeAttr* law = new NodeAttr();
    law->read(is);
    *data = law;
}
