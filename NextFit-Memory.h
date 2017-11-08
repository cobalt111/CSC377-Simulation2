#pragma once

#include <iostream>
#include "Memory.h"

using namespace std;

class NextFit : public Memory {
public:
	NextFit();
	~NextFit();
	int allocate_memory(int process_id, int num_units) override;
protected:
	Node * lastNode;
};

NextFit::NextFit(): Memory() {
	// set last node to the front on construction
	lastNode = front;
}

NextFit::~NextFit() {

}

int NextFit::allocate_memory(int process_id, int num_units) {
	// walkpointer is set to the last node used in the last operation
	cout << "Setting walkpointer..." << endl;
	Node * walkPointer = lastNode;
	int allocateSize = 0;
	int nodesTraversed_local = 0;
	bool bigEnough = false;

    cout << "Checking specs..." << endl;
	// check input for error
	if (num_units < 3 || num_units > 10) {
		return -1;
	}

    cout << "Starting Loop..." << endl;
	for (int i = 0; i < numElements; i++) {

		// check if walkPointer is free
		if (walkPointer->pid == 0) {
            cout << "0 Found..." << endl;
			//Save starting location of empty block
			current = walkPointer;

			allocateSize = 0;
            cout << "Starting to determine size...";
			// loop to check if the empty block is large enough
			while (walkPointer->pid == 0 && walkPointer->next != current) {

				allocateSize++;

				// if the size is big enough
				if (allocateSize == num_units) {
					bigEnough = true;
					break;
				}
				else if (walkPointer->next != NULL) {
					walkPointer = walkPointer->next;
					nodesTraversed_local++;
				}
				else {
					walkPointer = front->next;
					nodesTraversed_local++;
				}
			}

			// if a big enough block was found
			if (bigEnough) {

				// set walkPointer back to start of open space
				walkPointer = current;

				// fill in the open space with pid
				for (int z = 0; z < num_units; z++) {
                    walkPointer->pid = process_id;
					if (walkPointer->next != NULL){
						walkPointer = walkPointer->next;
					}
					else break;
				}

				num_of_allocations++;
				nodes_traversed += nodesTraversed_local;

				return nodesTraversed_local;
			}

		}
		else if (walkPointer->next != NULL) {

			// if pid found was not 0
			walkPointer = walkPointer->next;
			nodesTraversed_local++;
		}
		else {
			denied_allocations++;
			return -1;
		}

	}

	// upon failure to find space
	denied_allocations++;
	return -1;
}






// old code


//class NFMemory {
//public:
//	NFMemory();
//	~NFMemory();
//	void initializeList();
//	void printList();
//	int allocate_memory(int process_id, int num_units);
//	int deallocate_mem(int process_id);
//private:
//	Node *front;
//	Node header;
//	Node *current;
//	// need lastNode pointer from previous nextfit
//	Node * lastNode;
//	int numElements;
//	int num_of_allocations;
//	int nodes_traversed;
//	int denied_allocations;
//};
//
//NFMemory::NFMemory() {
//	front = current = &header;
//	header.next = NULL;
//	numElements = 128;
//	num_of_allocations = 0;
//	nodes_traversed = 0;
//	denied_allocations = 0;
//
//	// if lastNode has never been used, set to front
//	if (lastNode == NULL) {
//		lastNode = front;
//	}
//}
//
//NFMemory::~NFMemory() {
//
//};
//
//void NFMemory::initializeList() {
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
//void NFMemory::printList() {
//	Node * walkPointer = front;
//	walkPointer = walkPointer->next;
//	for (int i = 0; i < numElements; i++) {
//		cout << i << ": " << walkPointer->pid << endl;
//		walkPointer = walkPointer->next;
//	}
//}
//
//int NFMemory::allocate_memory(int process_id, int num_units) {
//	// walkpointer is set to the last node used in the last operation
//	Node * walkPointer = lastNode;
//	int allocateSize = 0;
//	int nodesTraversed_local = 0;
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
//				// change lastNode to the successful current
//				lastNode = current;
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
//int NFMemory::deallocate_mem(int process_id) {
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
