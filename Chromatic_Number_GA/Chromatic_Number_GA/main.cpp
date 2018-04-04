///////////////////////////////////
// Author: Tristan Hildahl
// Artificial Intelligence: Genetic Algorithm to solve for the chromatic number of a graph
// Test file to create the graphs and run the genetic algorithm
// Last Updated Algorithm: 4/3/2018
///////////////////////////////////

#include <iostream>
#include "Graph.h"

int main() {
	const int numTests = 100;	//Number of graphs in a single generation
								//Recommend more graphs (100 works fine for this instance) as it is less likely to get stuck on a local maximum
	srand(time(NULL));

	//There are 10 graphs in each generation represented by testGraph
	Graph testGraph[numTests]; 

	//Create all the graphs, they should all be the same graph structure, but with unique nodes and thus unique colors
	for (int i = 0; i < numTests; i++) {
		//Creating the graph values
		Node *n1 = new Node(), *n2 = new Node(), *n3 = new Node(), *n4 = new Node(),
			*n5 = new Node(), *n6 = new Node(), *n7 = new Node(), *n8 = new Node();

		Edge e1(n1, n2);
		Edge e2(n2, n3);
		Edge e3(n2, n4);
		Edge e4(n3, n4);
		Edge e5(n1, n5);
		Edge e6(n5, n7);
		Edge e7(n6, n7);
		Edge e8(n6, n8);
		Edge e9(n7, n8);

		//Adding values to the graph
		testGraph[i].addNode(n1);
		testGraph[i].addNode(n2);
		testGraph[i].addNode(n3);
		testGraph[i].addNode(n4);
		testGraph[i].addNode(n5);
		testGraph[i].addNode(n6);
		testGraph[i].addNode(n7);
		testGraph[i].addNode(n8);

		testGraph[i].addEdge(e1);
		testGraph[i].addEdge(e2);
		testGraph[i].addEdge(e3);
		testGraph[i].addEdge(e4);
		testGraph[i].addEdge(e5);
		testGraph[i].addEdge(e6);
		testGraph[i].addEdge(e7);
		testGraph[i].addEdge(e8);
		testGraph[i].addEdge(e9);

		testGraph[i].randomizeColors();
	}

	//generations are the maximum number of times it loops to find an optimal solution
	const int generations = 50;

	//currentBest is the last generation string, and repeat is a counter such that 
	//	if the best generation is the same multiple generations in a row the loop can be stopped
	string currentBest;
	int repeat = 1;

	//loop for number of specified generations
	for (int i = 0; i < generations; i++) {

		int maxFitness = 0;
		//Set the fitness value and the string representation for each graph while keeping track of the max fitness score
		for (int j = 0; j < numTests; j++) {
			int fit = testGraph[j].setFitness();

			//Update max fitness score
			if (fit > maxFitness)
				maxFitness = fit;

			testGraph[j].buildString();
		}

		///////////////////////////////////////////////
		//This represents the vector of parent graphs in string form, with more of each starting graph if they had a lower/better fitness score
		vector<string> parents;
		//This represents the array of child graphs, which will be made from parent strings, 
		//	but will limited to have the same number as the starting number of graphs
		string children[numTests];

		//Place each graph in the parent vector a given amount of times, with more for lower/better fitness scores
		for (int j = 0; j < numTests; j++) {
			///Fitness function:
			//Fitness score will be the sum of the estimated chromatic number and the current number of errors (maximum chromatic number to make it a viable graph)
			//Amount of times a graph is put in the parent vector is 
			//	the difference between the max fitness score and the score for that graph with at least 1 instance
			for (int k = 0; k < (maxFitness - testGraph[j].getFitness() + 1); k++) {
				parents.push_back(testGraph[j].getString());
			}
		}


		///////////////////////////////////////////////
		//Create all child graphs by randomly choosing 2 parents to crossover, with a very small chance of mutation after
		for (int j = 0; j < numTests / 2; j++) {
			int rand1 = rand() % parents.size();
			string parent1 = parents[rand1];
			int rand2 = rand() % parents.size();
			string parent2 = parents[rand2];

			//Default 2 children to opposite parents, 
			//then for each char in string there is an equal chance of switching the color of that nodde between the children
			string child1 = parent1;
			string child2 = parent2;

			for (int k = 0; k < child1.size(); k++) {
				///Crossover: switch values between parents/children at random
				int crossover = rand() % 2;
				if (crossover == 1) {
					child1[k] = parent2[k];
					child2[k] = parent1[k];
				}
				
				///Mutate: randomize a single value
				int mutate = rand() % 100;
				if (mutate == 0) {	//1% chance of mutating

					//Randomly select which child to mutate
					bool change_kid1 = rand() % 2;
					///Important! In order to use strings in this manner, chromatic number for graph must be 9 or less
					///Thus, the random mutation must also be within range and must be taken from a random location on a different graph
					//Select a random location in a string
					int find = rand() % parents[0].size();
					//Get a random value from one of the graphs by using that graph's string and the random location from find
					int mutation = testGraph[rand() % numTests].getString()[find];

					//Assign that value a different random number that is less than the current max chromatic number for all graphs
					if (change_kid1)
						child1[k] = mutation;
					else
						child2[k] = mutation;
				}

				children[j] = child1;
				children[j + (numTests / 2)] = child2;
			}
		}

			//////////////////////////////////////////
			//Set all of the graphs to be children graphs
			for (int j = 0; j < numTests; j++)
				testGraph[j].newGraph(children[j]);


			///////////////////////////////////////////
			//Output graph information
			//Best is the current smallest chromatic number
			int best = 999999999999;/// testGraph[0].getNodesSize() + 1;
			//bestGraph is the array index for the graph with the smallest chromatic number
			int bestGraph = 0;
			//Search all current graphs to find the one with the current lowest fitness function (and thus lowest chromatic number)
			for (int j = 0; j < numTests; j++) {
				if (testGraph[j].getFitness() <= best) {
					bestGraph = j;
					best = testGraph[j].getFitness();
				}
			}
			//Output the information for that best graph
			std::cout << "Best graph for generation " << i + 1 << 
				" has a chromatic number of : " << testGraph[bestGraph].getFitness() << std::endl;
			testGraph[bestGraph].showColors();


			////////////////////////////////////////
			//If the same pattern is found multiple times in a row, it is most likely the chromatic number and can stop algorithm
			//Count number of times best graph is repeated
			if (currentBest == testGraph[bestGraph].getString())
				repeat++;
			//If it is different, set to a new best graph and reset repeats
			else {
				currentBest = testGraph[bestGraph].getString();
				repeat = 1;
			}

			//If repeated 5 times in a row, break from loop
			if (repeat == 5)
				break;
		}

	

	//Delete all dynamically allocated nodes (delete graph now that computation is finished
	for (int i =0; i<numTests; i++)
		testGraph[i].deleteNodes();

}