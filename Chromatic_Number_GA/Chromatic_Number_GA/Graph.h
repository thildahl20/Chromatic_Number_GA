///////////////////////////////////
// Author: Tristan Hildahl
// Artificial Intelligence: Genetic Algorithm to solve for the chromatic number of a graph
// The Graph class definition: Creates a graph object to represent a graph with edges nodes and a chromatic number
// Last Updated Algorithm: 4/3/2018
///////////////////////////////////

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include "Edge.h"

//using namespace std;
using std::string;
using std::vector;

class Graph {
private:
	//This is the chromatic number that should be optimized
	int chromaticNumber = 0;

	//This is the fitness score for this graph based on chromatic and number of errors
	//Will represent the chromatic number for tests
	int fitness;

	//This is the string representation of a graph, with n numbers (where n is the number of nodes) being the color for each node of the graph
	//and the rest of the string is the fitness score for that graph
	string ga;		//(ga for genetic algorithm)

	//The nodes and edges the make up the graph
	vector<Node*> nodes;
	vector<Edge> edges;
public:
	Graph() {}

	//Places a pointer to a new node into the vector of nodes
	void addNode(Node* n);
	//Creates a new edge with pointers to two nodes, which should already be in the nodes vector for the graph
	void addEdge(Edge e);

	//Randomizes each node to a different color, based on the current max color
	//Used to create the first set of graphs
	void randomizeColors();

	//Uses the node index to get color
	int getColor(int n);

	//Getters
	int getFitness();
	string getString();
	int getNodesSize();


	//Outputs the colors of all nodes
	void showColors();

	//This sets the fitness function for the graph by summing the chromatic number with the number of errors (same colors adjacent) in the graph
	int setFitness();

	//This builds a string of all of the int values for the colors of the nodes of the graph
	///Important! Graph must be small such that the chromatic number for a node does not exceed 9
	///(Needed to use strings, which is why implementation is built in this manner)
	void buildString();

	//This inputs the string (child string) and tailors the values for this graph to that of the childs
	//@param newString is the string for a graph (child for algorithm) that this graph is set to match
	void newGraph(string newString);

	//Deletes all nodes for the graph
	void deleteNodes();
};

#endif