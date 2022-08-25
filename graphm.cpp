// ---------------------------------------graphm.cpp-----------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 05/05/2022
// Date of Last Modification: 05/14/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .cpp file for graphm class, by taking data from txt file
//          store value in 2 dimension array storage, to perform the dijkstra algorithm on finding 
//				shortest path from one node to another
//          have constructor function to initialize the visited, path, dist or cost value of the 2D array T
//          have buildGraph function to do the scanning of txt file and store in the array
//          have insertEdge function to add in new cost of the edge between two node (source and destination)
//				calling findShortestPath after adding to maintain dijkstra characteristic
//			have removeEdge function to remove the edge cost between two node, then set the cost back to
//				default infinity INT_MAX, calling findShortestPath after removing to maintain dijkstra 
//				characteristic
//			have displayAll function to print out all the data to console, including shortest path from one 
//				node to another for all nodes, dist cost
//          have display function to print out the shortest path from one node to another, only print the 
//				node value inputted in the parameter
//			have findShortestPath function to perform the dijkstra algorithm to search for shortest path
//				from one node to another for all nodes in the array
// ----------------------------------------------------------------------------------------------------

#include "graphm.h"

// -------------------------------------------------Constructor-----------------------------------------------
// Initialize the private variable of the class and set all value for those to default value (false for bool type
//		infinitiy for int type cost, 0 for int type path)
// Pre: no variable initialized
// Post: all variable being initialized to default value
GraphM::GraphM() {
	this->size = 0; // no data yet, initialize to zero
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++) {
			T[i][j].dist = INT_MAX; // set distance to infinity (INT_MAX)
			T[i][j].visited = false; // set all visited to false (have not visit anything)
			T[i][j].path = 0; // set all path to 0
			C[i][j] = INT_MAX;
		}
	}
}

// ---------------------------------------buildGraph()--------------------------------------------------------
// scan in data from txt file and input them into the variable being initialized from constructor
//		including the 2 dimension array to store the edge cost info too.
//		Scan data from txt using scanner ifstream& type param
// Pre: no txt file data scanned, collected, assigned
// Post: data from txt file are being assigned to appropriate private variable of class
void GraphM::buildGraph(ifstream& scan) {
	// first line in the data txt file are the size.
	scan >> size;
	string nodeName = "";
	getline(scan, nodeName); // scan the file for data, one input ends when new line is found

	for (int i = 1; i <= size; i++) {
		data[i].setData(scan); // insert name of node in the data name array
	}
	
	int source;
	int dest;
	int cost;

	while (scan >> source >> dest >> cost) {
		// the line starts from 0, end the loop
		if (source == 0) {
			break;
		}
		// fill in cost table
		C[source][dest] = cost;
	}
}

// -------------------------------insertEdge()--------------------------------------------------------------
// insert new edge cost for two different node (source and destination)
//		calling findShortestPath after adjusting the value to insure the dijsktra characteristic still present
// Pre: the edge cost remain the same
// Post: the new edge cost being adjusted between the source and dest node in the param
bool GraphM::insertEdge(int source, int dest, int cost) {
	// Exception Handling to Check the validity of source and dest
	if (source > size || source < 1) {
		return false;
	}
	if (dest > size || dest < 1) {
		return false;
	}
	if (cost < 0) {
		return false;
	}
	C[source][dest] = cost;
	findShortestPath(); // find shortest path again (dijkstra)
	return true;
}

// ------------------------------------------------removeEdge()---------------------------------------------
// remove the value of cost of the Edge between two node in the param (Source and Dest)
//		set the cost of the edge to default value of infinity (INT_MAX), then call findShortestPath() later
//		to insure the dijkstra characteristic
// Pre: edge cost remain unaltered
// Post: edge cost being adjusted to infinity, representing no value
bool GraphM::removeEdge(int source, int dest) {
	if (source > size || source < 1) {
		return false;
	}
	if (dest > size || dest < 1) {
		return false;
	}
	C[source][dest] = INT_MAX; //set the cost back to infinity
	findShortestPath(); // update shortest path again (dijkstra)
	return true;
}

// -------------------------------------------findShortestPath()-------------------------------------------
// Function to perform the dijkstra algorithm on all nodes in the array to find the shortest cost from one node 
//		to another. Following and implemented from the pseudocode provided in the assignment question docs
// Pre: no shortest cost found for all nodes
// Post: found shortest cost between all nodes, two nodes at a time and store them in the private variable of the
//		the class
void GraphM::findShortestPath() {
	for (int source = 1; source <= size; source++) {
		T[source][source].dist = 0;
		T[source][source].visited = true; // node visited
		for (int i = 1; i <= size; i++) {
			// find appropriate path, if the C is infinity, path not exist
			// if found, add the cost to dist of T
			// add path as well.
			if (C[source][i] != INT_MAX) {
				T[source][i].dist = C[source][i];
				T[source][i].path = source;
			}
		}
		// default node with 0 value
		int v = 0; // nodes with shortest distance from source
		do {
			int minTracker = INT_MAX;
			v = 0;
			for (int i = 1; i <= size; i++) {
				if ((T[source][i].visited == false) && (C[source][i] < minTracker)) {
					minTracker = C[source][i];
					v = i;
				}
			}
			if (v == 0) {
				break;
			}
			T[source][v].visited = true;
			for (int w = 1; w <= size; w++) {
				// if the node is visited, no action, go to next iteration
				if (T[source][w].visited == true) {
					continue;
				}
				// if the cost is infinity, no path, go to next iteration
				if (C[v][w] == INT_MAX) {
					continue;
				}
				// if it is in diagonal, no action, go to next iteration
				if (v == w) {
					continue;
				}
				if (T[source][w].dist > T[source][v].dist + C[v][w]) {
					T[source][w].dist = T[source][v].dist + C[v][w];
					T[source][w].path = v;
				}
			}
		} while (v != 0);
	}
}

// ------------------------------displayAll()-----------------------------------------------------------------
// print all the output to console including the shortest path from one node to another
// Pre: no output printed
// Post: print all the output to console, the output is similar to the sample out TXT files provided
void GraphM::displayAll() {
	cout << "Description         From node   To node   Dijkstra's     Path      " << endl;
	for (int i = 1; i <= size; i++) {
		cout << data[i] << endl;
		cout << endl;
		for (int j = 1; j <= size; j++) {
			if (T[i][j].dist != 0) {
				cout << "                        " << i;
				cout << "         " << j;
				if (T[i][j].dist == INT_MAX) {
					cout << "        ----" << endl; // go to new line directly, no path found
				}
				else {
					cout << "        " << T[i][j].dist;
					cout << "            ";
					printPath(i, j);
					cout << endl;
				}
			}
		}
	}
}

// ------------------------------------------display()---------------------------------------------------------
// print out one line info of shortestPath between two nodes asked in the param
// Pre: no output printed
// Post: print out the output to console including the shortest path from one node to another node from params
void GraphM::display(int source, int dest) {
	if ((source > size || source < 0) || (dest > size || dest < 0)) {
		cout << "    " << source << "         " << dest << "      ----" << endl;
		return;
	}
	cout << "    " << source << "         " << dest;

	if (T[source][dest].dist != INT_MAX) {
		cout << "        " << T[source][dest].dist << "            ";
		printPath(source, dest);
		cout << endl;
		printData(source, dest);
	}
	else {
		cout << "      ----" << endl;
	}
	cout << endl;
}

// -----------------------------------------printData()-----------------------------------------------------
// a helper method to print the name of the node to console (the street name)
// Pre: no node name printed
// Post: print node name to console accordingly, with new line char added for better visibility
void GraphM::printData(int source, int dest) {
	if (T[source][dest].dist == INT_MAX) {
		return;
	}
	if (source == dest) {
		cout << data[source] << endl;
		cout << endl;
		return;
	}
	int node = dest;
	printData(source, dest = T[source][dest].path);
	cout << data[node] << endl;
	cout << endl;
}

// --------------------------------------printPath()----------------------------------------------------
// a helper method to print the path between two nodes to console
// Pre: no path printed
// Post: print the path to the console, with appropriate spacing added for better visibility
void GraphM::printPath(int source, int dest) {
	// if the cost is infinity, no path
	if (T[source][dest].dist == INT_MAX) {
		return;
	}
	if (source == dest) {
		cout << dest << " ";
		return;
	}
	int path = dest;
	printPath(source, dest = T[source][dest].path);

	cout << path << " ";
}