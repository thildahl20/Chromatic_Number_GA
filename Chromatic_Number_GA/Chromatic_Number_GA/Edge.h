///////////////////////////////////
// Author: Tristan Hildahl
// Artificial Intelligence: Genetic Algorithm to solve for the chromatic number of a graph
// Creates an edge object with pointers to its 2 adjacent nodes: used in building the graph
// Last Updated Algorithm: 3/22/2018
///////////////////////////////////

#ifndef EDGE_H_
#define EDGE_H_

#include "Node.h"

class Edge {
private:
	//These are the 2 nodes that the edge is connected to
	Node* node1;
	Node* node2;
public:
	Edge(Node* n1, Node* n2) { node1 = n1; node2 = n2; }

	//If the colors of the 2 nodes are the same, there is an edge error so it returns true
	bool edgeError() {
		if (node1->getColor() == node2->getColor())
			return true;
		else
			return false;
	}
};

#endif