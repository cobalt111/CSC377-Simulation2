#pragma once

#include <iostream>
#include "Memory.h"

using namespace std;


class BestFit : public Memory {
public:
	int allocate_memory(int process_id, int num_units) override;
};

int BestFit::allocate_memory(int process_id, int num_units) {
	Node * walkPointer = front->next;
	int allocateSize = 0;
	int nodesTraversed_local = 0;
	int currentBestSize = 0;
	bool bigEnough = false;


	// check input for error
	if (num_units < 3 || num_units > 10) {
		return -1;
	}


	for (int i = 0; i < numElements; i++) {

		// check if walkPointer is free
		if (walkPointer->pid == 0) {

			//Save starting location of empty block
			current = walkPointer;

			// loop to check if the empty block is large enough
			while (walkPointer->pid == 0) {

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
			}

			// if a big enough block was found
			if (bigEnough) {

				// set walkPointer back to start of open space
				walkPointer = current;

				// fill in the open space with pid
				for (int z = 0; z < num_units; z++) {
					walkPointer->pid = process_id;
					walkPointer = walkPointer->next;
				}

				num_of_allocations++;
				nodes_traversed += nodesTraversed_local;

				return nodesTraversed_local;
			}

		}

		// if pid found was not 0
		walkPointer = walkPointer->next;
		nodesTraversed_local++;
	}

	// upon failure to find space
	denied_allocations++;
	return -1;
}
}







//struct Node {
//	int pid;
//
//	Node *next;
//};
//
//class BFMemory {
//public:
//	BFMemory();
//	~BFMemory();
//	void initializeList();
//	void printList();
//private:
//	Node *front;
//	Node header;
//	Node *current;
//	int numElements;
//};
//
//BFMemory::BFMemory() {
//	front = current = &header;
//	header.next = NULL;
//	numElements = 128;
//}
//
//BFMemory::~BFMemory() {
//
//};
//
//void BFMemory::initializeList() {
//	Node * newNode = new Node;
//	current = newNode;
//	//Node * currentNode = newNode;
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
//		//currentNode->next = newNode;
//		//currentNode = newNode;
//	}
//
//
//}
//
//void BFMemory::printList() {
//	Node * walkPointer = front;
//	walkPointer = walkPointer->next;
//	for (int i = 0; i < numElements; i++) {
//		cout << i << ": " << walkPointer->pid << endl;
//		walkPointer = walkPointer->next;
//	}
//}