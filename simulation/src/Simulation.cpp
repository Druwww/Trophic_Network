#include "../include/Simulation.h"

Simulation::Simulation() : m_graph(nullptr), m_turn(0){
    //ctor
}

Simulation::Simulation(Graph* graph) : m_graph(graph), m_turn(0){
    //ctor
}

Simulation::~Simulation(){
    //dtor
}
