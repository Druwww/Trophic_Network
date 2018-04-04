#ifndef GRAPHHELPER
#define GRAPHHELPER

#include <iostream>

#include "../../entities/animal/include/Animal.h"
#include "../../entities/animal/include/NaturalLaw.h"

void onDeleteNode(void* data);
void onDeleteEdge(void* data);
void onSerializeNode(std::ostream& os, void* data);
void onSerializeEdge(std::ostream& os, void* data);
void onDeserializeNode(std::istream& is, void** data);
void onDeserializeEdge(std::istream& is, void** data);

#endif // GRAPHHELPER

