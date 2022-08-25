// ---------------------------------------graphl.h-------------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 05/10/2022
// Date of Last Modification: 05/14/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .h file for graphl class contain the contract interface for graphl.cpp file
// ----------------------------------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <climits>

using namespace std;

int const MAX_NODE = 101;

class GraphL{

public:

    // ----------------------------------------Constructor-----------------------------------------------------
    // initialize all private variable of the class to default value
    // Pre: no value initialized or assigned
    // Post: private variable of class being initialized and assigned to default value
    GraphL();

    // --------------------------------------Destructor-----------------------------------------------------
    // destroy all data by calling the helper method
    // Pre: no data deleted
    // Post: all data being destroy and deallocated with the helper method
    virtual ~GraphL();

    // ------------------------------------------buildGraph()---------------------------------------------------
    // scan in data from txt file and input them into the variable being initialized from constructor
    //		Scan data from txt using scanner ifstream& type param
    // Pre: no txt file data scanned, collected, assigned
    // Post: data from txt file are being assigned to appropriate private variable of class
    void buildGraph(ifstream& scan);

    // --------------------------------------------------depthFirstSearch()----------------------------------------
    // perform depthFirstSearch and call helper method to print out the depthFirst ordering path
    // Pre: no depthFirstSearch performed
    // Post: call helper method and perform depthFirst search and print out output to console for path
    void depthFirstSearch();

    // -------------------------------------------displayGraph()-------------------------------------------------
    // print out the graph and data of the array to console to show the name and path, etc.
    // Pre: no output printed
    // Post: print out the graph to console with all of the info from array.
    void displayGraph();

private:
    int size;

    struct EdgeNode;      // forward reference for the compiler
    struct GraphNode {    // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };
    
    GraphNode array[MAX_NODE];

    struct EdgeNode {
        int adjGraphNode;  // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };

    // --------------------------------------depthFirstHelper()-----------------------------------------------
    // a helper method to recursively search for path
    // Pre: no depthFrist search performed
    // Post: perform recursive call to search for the depthFirst ordering path
    void depthFirstHelper(int num);

    // ----------------------------------------destructorHelper()-------------------------------------------------
    // traverse the list and destroy everything
    // Pre: nothing being delete or deallocated
    // Post: traverse list and deallocate all data in the list.
    void destructorHelper();


};

#endif