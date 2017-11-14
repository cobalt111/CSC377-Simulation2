#pragma once
#include <iostream>
#include "Memory.h"
using namespace std;

class FirstFit : public Memory {
public:
	// overriding allocate memory
	int allocate_memory(int process_id, int num_units) override;
private:
};

int FirstFit::allocate_memory(int process_id, int num_units) {

	Node * walkPointer = front->next;	//walkPointer will be used to traverse the memory linked-list
	int allocateSize = 0;			//allocateSize will be used to keep track of how large an empty space is
	int nodesTraversed_local = 0;		//nodesTraversed_local will keep track of how many nodes we had to walk through
						//and will be returned as required when there is a success
	bool bigEnough = false;			//bigEnough is used to break out of the first loop and begin overwriting
						//the empty space that has been found.

	// check input for error/follows specs
	if (num_units < 3 || num_units > 10) { return -1; }
	//Main loop that will be used to walk through the entire memory linked list
	for (int i = 0; i < numElements; i++) {
		
		// check if walkPointer is free/an empty space has been found.
		if (walkPointer->pid == 0) {	
			//Save starting location of empty block
			current = walkPointer;
			allocateSize = 0;
			// loop to check if the found empty block is a large enough size.
			while (walkPointer->pid == 0) {
				allocateSize++;
				// if the size is big enough break and begin filling space 
				if (allocateSize == num_units) {
					bigEnough = true;
					break;
				}
				//If it isn't big enough yet keep walking as long as you havent hit the end yet
				else if (walkPointer->next != NULL) {
					walkPointer = walkPointer->next;
					nodesTraversed_local++;
				}
				//If you have hit the end stop the whole process because there wasn't a space large enough
				else{
				    denied_allocations++;
				    return -1;
		                }
			}

			// if a big enough block was found
			if (bigEnough) {

				// set walkPointer back to start of open space and enter a loop to fill the space
				walkPointer = current;

				// fill in the open space with pid
				for (int z = 0; z < num_units; z++) {
					walkPointer->pid = process_id;
					walkPointer = walkPointer->next;
				}
				//After successfully allocated update statistic sizes and return the number of nodes
				num_of_allocations++;
				nodes_traversed += nodesTraversed_local;
				return nodesTraversed_local;
			}

		} 
		else{
			// if pid found was not 0
			if (walkPointer->next != NULL){
                		walkPointer = walkPointer->next;
                		nodesTraversed_local++;
			}
			//break because you have hit the end of memory and there wasn't a space
			else{
				denied_allocations++;
                		return -1;
			}
		}
	}
	// upon failure to find space
	denied_allocations++;
	return -1;
}



//
//
//struct Node {
//	int pid;
//
//	Node *next;
//};
//
//class FFMemory {
//public:
//	FFMemory();
//	~FFMemory();
//	void initializeList();
//	void printList();
//	int allocate_memory(int process_id, int num_units);
//	int deallocate_mem(int process_id);
// private:
//	Node *front;
//	Node header;
//	Node *current;
//	int numElements;
//	int num_of_allocations;
//	int nodes_traversed;
//	int denied_allocations;
//};
//
//FFMemory::FFMemory() {
//	front = current = &header;
//	header.next = NULL;
//	numElements = 128;
//	num_of_allocations = 0;
//	nodes_traversed = 0;
//	denied_allocations = 0;
//}
//
//FFMemory::~FFMemory() {
//
//};
//
//void FFMemory::initializeList() {
//	Node * newNode = new Node;
//	current = newNode;
//	front->next = newNode;
//	newNode->pid = 0;
//	newNode->next = NULL;
//
//	for (int i = 0; i < numElements - 1; i++) {
//		newNode = new Node;
//		newNode->pid = 0;
//		newNode->next = NULL;
//		current->next = newNode;
//		current = newNode;
//	}
//
//
//}
//
//void FFMemory::printList() {
//	Node * walkPointer = front;
//	walkPointer = walkPointer->next;
//	for (int i = 0; i < numElements; i++) {
//		cout << i << ": " << walkPointer->pid << endl;
//		walkPointer = walkPointer->next;
//	}
//}
//
//int FFMemory::allocate_memory(int process_id, int num_units) {
//	Node * walkPointer = front->next;
//	int allocateSize = 0;
//	int nodesTraversed_local =  0;
//	if (num_units < 3 || num_units > 10) {
//		return -1;
//	}
//	for (int i = 0; i < numElements; i++) {
//		if (walkPointer->pid == 0) {
//			current = walkPointer; //Save starting location of empty block
//			while (walkPointer->pid == 0) {
//				allocateSize++;
//				if (allocateSize == num_units) {
//					break;
//				}
//				walkPointer = walkPointer->next;
//				nodesTraversed_local++;
//			}
//			if (allocateSize >= num_units) {
//				walkPointer = current;
//				for (int z = 0; z < num_units; z++) {
//					walkPointer->pid = process_id;
//					walkPointer = walkPointer->next;
//				}
//				num_of_allocations++;
//				nodes_traversed += nodesTraversed_local;
//				return nodesTraversed_local;
//			}
//
//		}
//		walkPointer = walkPointer->next;
//		nodesTraversed_local++;
//	}
//	denied_allocations++;
//	return -1;
//}
//
//int FFMemory::deallocate_mem(int process_id) {
//	Node * walkPointer = front->next;
//	while (walkPointer->pid != process_id) {
//		walkPointer = walkPointer->next;
//		if (walkPointer->next == NULL) {
//			return -1;
//		}
//	}
//	while (walkPointer->pid == process_id) {
//		walkPointer->pid = 0;
//		walkPointer = walkPointer->next;
//	}
//	return 1;
//}
