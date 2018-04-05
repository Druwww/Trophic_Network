#include "graphhelper.h"

void onDeleteNode(void* data){
    NodeAttr* animal = (NodeAttr*) data;
    delete animal;
}

void onDeleteEdge(void* data){
<<<<<<< HEAD
    NaturalLaw* law = (NaturalLaw*) data;
=======
    EdgeAttr* law = (EdgeAttr*) data;
>>>>>>> 5c0b17156589dce552c5467fae2617bc230c5bd9
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    NodeAttr* animal = (NodeAttr*) data;
    animal->write(os);
}

void onSerializeEdge(std::ostream& os, void* data){
<<<<<<< HEAD
    NaturalLaw* law = (NaturalLaw*) data;
=======
    EdgeAttr* law = (EdgeAttr*) data;
>>>>>>> 5c0b17156589dce552c5467fae2617bc230c5bd9
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    NodeAttr* animal = new NodeAttr();
    animal->read(is);
    *data = animal;
}

void onDeserializeEdge(std::istream& is, void** data){
<<<<<<< HEAD
    NaturalLaw* law = new NaturalLaw();
=======
    EdgeAttr* law = new EdgeAttr();
>>>>>>> 5c0b17156589dce552c5467fae2617bc230c5bd9
    law->read(is);
    *data = law;
}
