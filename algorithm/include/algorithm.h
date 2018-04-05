#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "../../entities/graph/include/Graph.h"
#include "../../entities/animal/include/Animal.h"
#include "../../entities/animal/include/NaturalLaw.h"

void clearAllMarck(Graph& graph);

bool checkAllNodeMarck(Graph& graph);

void processedThreeOfNodeByNode(Graph& graph, Node* nodeWork);

void processedThreeRecursive(Graph& graph, data& d, bool down);

///Fonction temporaire
void displayNodeProssed(Graph& graph);

#endif
