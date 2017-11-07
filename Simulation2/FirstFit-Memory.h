#pragma once

#include <iostream>
using namespace std;


struct Node {
	int pid;

	Node *next;
};

class FFMemory {
public:
	FFMemory();
	~FFMemory();
	void initializeList();
	void printList();
	int allocate_memory(int process_id, int num_units);
	int deallocate_mem(int process_id);
	float avg_allocateTime();
	float percent_denied();
 private:
	Node *front;
	Node header;
	Node *current;
	int numElements;
	float num_of_allocations;
	float nodes_traversed;
	float denied_allocations;
};

FFMemory::FFMemory() {
	front = current = &header;
	header.next = NULL;
	numElements = 128;
	num_of_allocations = 0;
	nodes_traversed = 0;
	denied_allocations = 0;
}

FFMemory::~FFMemory() {

};

void FFMemory::initializeList() {
	Node * newNode = new Node;
	current = newNode;
	front->next = newNode;
	newNode->pid = 0;
	newNode->next = NULL;

	for (int i = 0; i < numElements - 1; i++) {
		newNode = new Node;
		newNode->pid = 0;
		newNode->next = NULL;
		current->next = newNode;
		current = newNode;
	}


}

void FFMemory::printList() {
	Node * walkPointer = front;
	walkPointer = walkPointer->next;
	for (int i = 0; i < numElements; i++) {
		cout << i << ": " << walkPointer->pid << endl;
		walkPointer = walkPointer->next;
	}
}

int FFMemory::allocate_memory(int process_id, int num_units) {
	Node * walkPointer = front->next;                       //Create a pointer to walk-through memory. Start it 1 node after the header
	int allocateSize = 0;                                   //allocateSize will keep track of how large the empty space we are traversing is
	int nodesTraversed_local =  0;                          //nodesTraversed will be returned if the allocation is successful. Used to statistical information

	if (num_units < 3 || num_units > 10) {                  //Ensures that the num_units being used is within the allowed parameters for the simulation
		return -1;
	}

	for (int i = 0; i < numElements; i++) {                 //Begin walking through the memory linked list from the first node
        allocateSize = 0;                                   //Reset allocate size for the next empty space found.
		if (walkPointer->pid == 0) {                        //Check the node currently on. If it is empty begin checking to see if it is large enough for the process
			current = walkPointer;                          //Save starting location of empty block
                                                            //Current will be returned to if this area is used to write the process to.
			while (walkPointer->pid == 0) {                 //Start of loop to walk through open space

				allocateSize++;                             //Increase size of allocateSize first because we want this to start at 1, not 0.

				if (allocateSize == num_units) {            //Check to see if allocateSize has counted a space large enough for us to put the process in
					break;                                  //If it is break this while loop, there is no need to continue counting this huge empty space
				}
				if (walkPointer->next == NULL){             //If allocateSize isn't big enough yet, check to make sure we haven't already hit the end of the memory
                    denied_allocations++;                   //If we have increase the denied_allocations for statistical reasons
                    return -1;                              //Return to the main program, there isn't space to put this process as of right now.
				}
				walkPointer = walkPointer->next;            //If we haven't reached the end of the string, but we still need more space for the process move to the next space and
				nodesTraversed_local++;                     //check to see we are still in an empty space. Inc nodesTravelled each time for statistics.
			}

			if (allocateSize >= num_units) {                //If we have found a space big enough, prepare to write the new process into memory.
				walkPointer = current;                      //Return to the start of the empty space

				for (int z = 0; z < num_units; z++) {       //This loop will write the empty space with the process.
					walkPointer->pid = process_id;
					walkPointer = walkPointer->next;
				}

				num_of_allocations++;                       //Inc total number of allocations for statistical reasons
				nodes_traversed += nodesTraversed_local;    //Keep track of the total number of nodes traversed successfully for statistical reasons
				return nodesTraversed_local;                //return the local amount of nodes traversed for just this allocation to the main program as required in specs
			}

		}
        if (walkPointer->next == NULL){             //If allocateSize isn't big enough yet, check to make sure we haven't already hit the end of the memory
            denied_allocations++;                   //If we have increase the denied_allocations for statistical reasons
            return -1;                              //Return to the main program, there isn't space to put this process as of right now.
        }
		walkPointer = walkPointer->next;                    //If that area wasn't big enough for the process, or a empty space hasn't been reached yet, continue walking through memory
		nodesTraversed_local++;                             //Inc nodes traversed each time. This doesn't count as double because when a blank space is found we dont reset walkpointer ever
	}
	denied_allocations++;                                   //somehow if we make it all the way through the string and end the for loop this catches and counts it as a denial
	return -1;
}

int FFMemory::deallocate_mem(int process_id) {
    //cout << "CALLED DEALLOCATER!\n";
	Node * walkPointer = front->next;
	//cout << "walkPointer made\n";
	while (walkPointer->pid != process_id) {
		walkPointer = walkPointer->next;
        //cout << "changed walkpointer location!\n";
		if (walkPointer->next == NULL) {
			//cout << "\nDidnt find it";
			return -1;
		}
	}
	while (walkPointer->pid == process_id) {
        //cout << "DELETING " << process_id << endl;
		walkPointer->pid = 0;
        //cout << "MOVING ON\n";
        if (walkPointer->next == NULL){
            break;
        }
		walkPointer = walkPointer->next;
	}
	return 1;
}

float FFMemory::avg_allocateTime(){
    float average;
    //cout << endl << nodes_traversed << endl;
    //cout << num_of_allocations << endl;
    average = nodes_traversed / num_of_allocations;
    //cout << average;
    return average;
}


float FFMemory::percent_denied(){
    float percentage;
    percentage = denied_allocations / (denied_allocations + num_of_allocations);
    //cout << " " << denied_allocations << "/(" << denied_allocations << "+" << num_of_allocations << ")";
    return percentage;
}
