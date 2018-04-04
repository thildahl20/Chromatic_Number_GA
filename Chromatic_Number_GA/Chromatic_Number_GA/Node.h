///////////////////////////////////
// Author: Tristan Hildahl
// Artificial Intelligence: Genetic Algorithm to solve for the chromatic number of a graph
// Creates a Node object to represent each individual location on a graph, has a color represented by a number
// Last Updated Algorithm: 3/22/2018
///////////////////////////////////

#ifndef NODE_H_
#define NODE_H_

class Node {
private:
	//This is an integer that represents the color, so each unique integer is a unique color
	int color;
public:
	Node() {}

	//Getters and mutators
	int getColor() { return color; }
	void setColor(int c) { color = c; }

};

#endif 