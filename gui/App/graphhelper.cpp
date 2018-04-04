#include "graphhelper.h"

void onDeleteNode(void* data){
    Animal* animal = (Animal*) data;
    delete animal;
}

void onDeleteEdge(void* data){
    NaturalLaw* law = (NaturalLaw*) data;
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    Animal* animal = (Animal*) data;
    animal->write(os);
}

void onSerializeEdge(std::ostream& os, void* data){
    NaturalLaw* law = (NaturalLaw*) data;
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    Animal* animal = new Animal();
    animal->read(is);
    *data = animal;
}

void onDeserializeEdge(std::istream& is, void** data){
    NaturalLaw* law = new NaturalLaw();
    law->read(is);
    *data = law;
}
