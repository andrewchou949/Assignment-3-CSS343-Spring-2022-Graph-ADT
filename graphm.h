// ---------------------------------------poly.h-------------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 05/05/2022
// Date of Last Modification: 05/14/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .h file for graphm class contain the contract interface for graphm.cpp file
// ----------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <climits>

using namespace std;

int const MAXNODES = 101;

class GraphM{


public: 
    // -------------------------------------------------Constructor-----------------------------------------------
    // Initialize the private variable of the class and set all value for those to default value (false for bool type
    //		infinitiy for int type cost, 0 for int type path)
    // Pre: no variable initialized
    // Post: all variable being initialized to default value
    GraphM();

    // ---------------------------------------buildGraph()--------------------------------------------------------
    // scan in data from txt file and input them into the variable being initialized from constructor
    //		including the 2 dimension array to store the edge cost info too.
    //		Scan data from txt using scanner ifstream& type param
    // Pre: no txt file data scanned, collected, assigned
    // Post: data from txt file are being assigned to appropriate private variable of class
    void buildGraph(ifstream& scan);

    // -------------------------------insertEdge()--------------------------------------------------------------
    // insert new edge cost for two different node (source and destination)
    //		calling findShortestPath after adjusting the value to insure the dijsktra characteristic still present
    // Pre: the edge cost remain the same
    // Post: the new edge cost being adjusted between the source and dest node in the param
    bool insertEdge(int source, int dest, int cost);

    // ------------------------------------------------removeEdge()---------------------------------------------
    // remove the value of cost of the Edge between two node in the param (Source and Dest)
    //		set the cost of the edge to default value of infinity (INT_MAX), then call findShortestPath() later
    //		to insure the dijkstra characteristic
    // Pre: edge cost remain unaltered
    // Post: edge cost being adjusted to infinity, representing no value
    bool removeEdge(int source, int dest);

    // -------------------------------------------findShortestPath()-------------------------------------------
    // Function to perform the dijkstra algorithm on all nodes in the array to find the shortest cost from one node 
    //		to another. Following and implemented from the pseudocode provided in the assignment question docs
    // Pre: no shortest cost found for all nodes
    // Post: found shortest cost between all nodes, two nodes at a time and store them in the private variable of the
    //		the class
    void findShortestPath();

    // ------------------------------displayAll()-----------------------------------------------------------------
    // print all the output to console including the shortest path from one node to another
    // Pre: no output printed
    // Post: print all the output to console, the output is similar to the sample out TXT files provided
    void displayAll();

    // ------------------------------------------display()---------------------------------------------------------
    // print out one line info of shortestPath between two nodes asked in the param
    // Pre: no output printed
    // Post: print out the output to console including the shortest path from one node to another node from params
    void display(int source, int dest);


private:
    struct TableType {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source known so far
        int path;              // previous node in path of min dist
    };
    
    NodeData data[MAXNODES];              // data for graph nodes, data = node name
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path


    // -----------------------------------------printData()-----------------------------------------------------
    // a helper method to print the name of the node to console (the street name)
    // Pre: no node name printed
    // Post: print node name to console accordingly, with new line char added for better visibility
    void printData(int source, int dest);

    // --------------------------------------printPath()----------------------------------------------------
    // a helper method to print the path between two nodes to console
    // Pre: no path printed
    // Post: print the path to the console, with appropriate spacing added for better visibility
    void printPath(int source, int dest);
};

#endif