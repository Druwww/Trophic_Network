#ifndef GRAPHHELPER
#define GRAPHHELPER

#include <iostream>

#include "../../entities/animal/include/NodeAttr.h"
#include "../../entities/animal/include/NodeAttr.h"

void onDeleteNode(void* data);
void onDeleteVertex(void* data);
void onSerializeNode(std::ostream& os, void* data);
void onSerializeVertex(std::ostream& os, void* data);
void onDeserializeNode(std::istream& is, void** data);
void onDeserializeVertex(std::istream& is, void** data);

#endif // GRAPHHELPER

