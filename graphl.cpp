// ---------------------------------------graphl.cpp-----------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 05/10/2022
// Date of Last Modification: 05/14/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .cpp file for graphl class, by scanning data from txt file
//          store value in array storage
//          have constructor function to initialize all private variable to default value
//			have virtual destructor functions that call helper method to clear out all data
//			have buildGraph function to do the scanning of txt file and store in the array
//			have depthFirstSearch Function to find the depthFirst ordering path from one node to all other node
//				this will perform the find the depthFirst path for all node, one at a time
//			have displayGraph Function to print out the Node info and edge info to console
//			have depthFirstHelper Function to recursively traverse the list for path finding
//			have destructorHelper Function to traverse the list and delete every element or datas
// ----------------------------------------------------------------------------------------------------

#include "graphl.h"

// ----------------------------------------Constructor-----------------------------------------------------
// initialize all private variable of the class to default value
// Pre: no value initialized or assigned
// Post: private variable of class being initialized and assigned to default value
GraphL::GraphL() {
	// default size, nothing scanned in, so the default is 0
	size = 0;
	for (int i = 1; i < MAX_NODE; i++) {
		// initialize everything to default value
		array[i].visited = false;
		array[i].edgeHead = nullptr;
		array[i].data = nullptr;
	}
}

// --------------------------------------Destructor-----------------------------------------------------
// destroy all data by calling the helper method
// Pre: no data deleted
// Post: all data being destroy and deallocated with the helper method
GraphL::~GraphL() {
	destructorHelper();
}

// ------------------------------------------buildGraph()---------------------------------------------------
// scan in data from txt file and input them into the variable being initialized from constructor
//		Scan data from txt using scanner ifstream& type param
// Pre: no txt file data scanned, collected, assigned
// Post: data from txt file are being assigned to appropriate private variable of class
void GraphL::buildGraph(ifstream& scan) {
	// first line is the size of the nodes (total # of nodes)
	scan >> size;
	string nodeName = "";
	// read the line
	getline(scan, nodeName); 
	
	// inserting the node names to the array
	for (int i = 1; i <= size; i++) {
		getline(scan, nodeName);
		NodeData* tmp = new NodeData(nodeName);
		array[i].data = tmp;
	}

	int source;
	int dest;

	while (scan >> source >> dest) {
		// when new scan value is 0, it represents the end of docs, end while with break;
		if (source == 0) {
			break;
		}
		// no data yet, the very first node
		if (array[source].edgeHead == nullptr) {
			// create a new pointer item
			EdgeNode* newNode = new EdgeNode;
			// set the adjacent to the destination (inserting)
			newNode->adjGraphNode = dest;
			// set the head of the array to be the newNode
			array[source].edgeHead = newNode;
			// the next of the head of the array is nullptr (to be assigned the next item)
			array[source].edgeHead->nextEdge = nullptr;
		}
		// there are some data in the array, assign the next item in
		else {
			// new node pointer item
			EdgeNode* newNode = new EdgeNode;
			// inserting adjacent node
			newNode->adjGraphNode = dest;
			// update pointer
			newNode->nextEdge = array[source].edgeHead;
			array[source].edgeHead = newNode;
		}
	}
}

// --------------------------------------------------depthFirstSearch()----------------------------------------
// perform depthFirstSearch and call helper method to print out the depthFirst ordering path
// Pre: no depthFirstSearch performed
// Post: call helper method and perform depthFirst search and print out output to console for path
void GraphL::depthFirstSearch() {
	cout << "\nDepth-First ordering:";
	// depth first scan on unvisited node
	for (int i = 1; i <= size; i++) {
		// check if the node has been visited yet, if not yet, depth first search
		if (array[i].visited == false) {
			depthFirstHelper(i);
		}
	}
	cout << endl;
}

// -------------------------------------------displayGraph()-------------------------------------------------
// print out the graph and data of the array to console to show the name and path, etc.
// Pre: no output printed
// Post: print out the graph to console with all of the info from array.
void GraphL::displayGraph() {
	cout << "\nGraph:" << endl;
	// print out all the data of array
	for (int i = 1; i <= size; i++) {
		// name printing
		cout << "Node" << i << "         " << *array[i].data << endl;
		cout << endl;

		// setup curr pointer to traverse
		EdgeNode* curr = array[i].edgeHead;

		// traversing and printing info
		while (curr != nullptr) {
			cout << "  edge  " << i << "  " << curr->adjGraphNode << endl;
			// update the pointer
			curr = curr->nextEdge;
		}
	}
}

// --------------------------------------depthFirstHelper()-----------------------------------------------
// a helper method to recursively search for path
// Pre: no depthFrist search performed
// Post: perform recursive call to search for the depthFirst ordering path
void GraphL::depthFirstHelper(int num) {
	cout << "  " << num;
	// mark them as visited
	array[num].visited = true;
	// setup a curr pointer to traverse the list
	EdgeNode* curr = array[num].edgeHead;
	// traversing
	while (curr != nullptr) {
		// checking if the next adjacent is visited yet, if not yet, proceed the recursion
		if (array[curr->adjGraphNode].visited == false) {
			depthFirstHelper(curr->adjGraphNode);
		}
		// updating the curr pointer.
		curr = curr->nextEdge;
	}
}

// ----------------------------------------destructorHelper()-------------------------------------------------
// traverse the list and destroy everything
// Pre: nothing being delete or deallocated
// Post: traverse list and deallocate all data in the list.
void GraphL::destructorHelper() {
	for (int i = 1; i <= size; i++) {
		// set all the visited value to default false
		array[i].visited = false;
		// delete the node name data to prevent leak
		delete array[i].data;
		// set the data to nullptr to prevent dangling ptrs
		array[i].data = nullptr;

		// if the head is not null, it contains data
		if (array[i].edgeHead != nullptr) {
			// curr pointer used to traverse the list
			EdgeNode* curr = array[i].edgeHead;
			// traversing
			while (curr != nullptr) {
				array[i].edgeHead = array[i].edgeHead->nextEdge;
				// removing action to prevent leak
				delete curr;
				// to prevent dangling
				curr = nullptr;
				// update curr to next
				curr = array[i].edgeHead;
			}
		}
	}
}