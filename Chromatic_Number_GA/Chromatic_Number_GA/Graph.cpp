///////////////////////////////////
// Author: Tristan Hildahl
// Artificial Intelligence: Genetic Algorithm to solve for the chromatic number of a graph
// The Graph class implementation: Creates a graph object to represent a graph with edges nodes and a chromatic number
// Last Updated Algorithm: 4/3/2018
///////////////////////////////////

#include "Graph.h"

//Places a pointer to a new node into the vector of nodes
void Graph::addNode(Node* n) { nodes.push_back(n); }
//Creates a new edge with pointers to two nodes, which should already be in the nodes vector for the graph
void Graph::addEdge(Edge e) { edges.push_back(e); }

//Randomizes each node to a different color, based on the current max color
//Used to create the first set of graphs
void Graph::randomizeColors() {
	for (int i = 0; i < nodes.size(); i++) {	//For all nodes
		int c = rand() % (chromaticNumber + 1);
		nodes[i]->setColor(c);					//Give them a random color less than or equal to the current chromatic number

		if (c == chromaticNumber) //Whenever the the biggest number is used, expand the maximum chromatic number to allow for larger numbers
			chromaticNumber++;
	}

}

//Uses the node index to get color
int Graph::getColor(int n) { return nodes[n]->getColor(); }

//Getters
int Graph::getFitness() { return fitness; }
string Graph::getString() { return ga; }
int Graph::getNodesSize() { return nodes.size(); }


//Outputs the colors of all nodes
void Graph::showColors() {
	for (int i = 0; i < nodes.size(); i++) {
		std::cout << "\tNode " << i + 1 << " has color " << nodes[i]->getColor() + 1 << std::endl;
	}
}

//This sets the fitness function for the graph by summing the chromatic number with the number of errors (same colors adjacent) in the graph
int Graph::setFitness() {
	fitness = chromaticNumber;
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].edgeError())
			fitness++;
	}
	return fitness;
}

//This builds a string of all of the int values for the colors of the nodes of the graph
///Important! Graph must be small such that the chromatic number for a node does not exceed 9
///(Needed to use strings, which is why implementation is built in this manner)
void Graph::buildString() {
	string newString = "";
	for (int i = 0; i < nodes.size(); i++) {
		newString.append(std::to_string(nodes[i]->getColor()));
	}

	ga = newString;
}

//This inputs the string (child string) and tailors the values for this graph to that of the childs
//@param newString is the string for a graph (child for algorithm) that this graph is set to match
void Graph::newGraph(string newString) {
	ga = newString;

	int max = 0;

	//Take the value for the color for each node from the string and set the value on the node
	for (int i = 0; i < nodes.size(); i++) {
		int n = newString[i] - 48;	//-48 to convert back out of ascii code from the string
		nodes[i]->setColor(n);

		if (n > max)
			max = n;
	}

	chromaticNumber = max + 1;	//+1 to avoid 0
	setFitness();
}

//Deletes all nodes for the graph
void Graph::deleteNodes() {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}