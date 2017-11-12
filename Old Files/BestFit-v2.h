#pragma once

#include <iostream>
#include <limits.h>
#include "Memory-v2.h"

using namespace std;


class BFMemory : public Memory {
public:
	int allocate_mem(int process_id, int num_units) override;
};

int BFMemory::allocate_mem(int process_id, int num_units) {

	walkList_ptr = front_ptr;
	Node * nextStartPoint = walkList_ptr;
	Node * bestLocation = NULL;
	int allocateSize = 0;
	int nodesTraversed_local = 0;
	int currentBestSize = INT_MAX;
	bool currentBigEnough = false;
	bool bigEnough = false;



	// check input for error
	if (num_units < 3 || num_units > 10) {
		return -1;
	}


	while (walkList_ptr->next != NULL) {

		walkList_ptr = nextStartPoint;

		currentBigEnough = false;
		
		// check if walkList_ptr is free
		if (walkList_ptr->process_id == -1) {

			//Save starting location of empty block
			emptyBlock_ptr = walkList_ptr;
			allocateSize = 0;

			// loop to check if the empty block is large enough
			while (walkList_ptr->process_id == -1) {
				allocateSize++;

				// if the size is big enough
				if (allocateSize >= num_units) {
					currentBigEnough = true;
					bigEnough = true;
				}

				if (walkList_ptr->next != NULL && walkList_ptr->next->process_id != -1) {
					nextStartPoint = walkList_ptr->next;
					nodesTraversed_local++;
					break;
				}
				else if (walkList_ptr->next != NULL) {
					walkList_ptr = walkList_ptr->next;
					nodesTraversed_local++;
				}
				else break;
			}

			// change best size to new block size if it's smaller
			if (currentBigEnough && allocateSize < currentBestSize) {
				currentBestSize = allocateSize;
				bestLocation = emptyBlock_ptr;
			}
		} 
		else if (walkList_ptr->next != NULL) {
			walkList_ptr = walkList_ptr->next;
			nextStartPoint = walkList_ptr;
			nodesTraversed_local++;
		}
		else break;
	}

	// if finished with list and a big enough space was found
	if (bigEnough) {
		// set walkList_ptr back to start of open space
		walkList_ptr = bestLocation;

		// fill in the open space with process_id
		for (int z = 0; z < num_units; z++) {
			walkList_ptr->process_id = process_id;
			if (walkList_ptr->next != NULL) {
				walkList_ptr = walkList_ptr->next;
			}
		}

		num_of_allocations++;
		nodes_traversed += nodesTraversed_local;
		return nodesTraversed_local;
	}
	else {
		num_of_allocations++;
		denied_allocations++;
		return -1;
	}

	

	// upon failure to find space
	return -1;
}







//struct Node {
//	int process_id;
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
//	Node *emptyBlock_ptr;
//	int numElements;
//};
//
//BFMemory::BFMemory() {
//	front = emptyBlock_ptr = &header;
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
//	emptyBlock_ptr = newNode;
//	//Node * emptyBlock_ptrNode = newNode;
//	front->next = newNode;
//	newNode->process_id = 0;
//	newNode->next = NULL;
//
//	for (int i = 0; i < numElements - 1; i++) {
//		newNode = new Node;
//		newNode->process_id = 0;
//		newNode->next = NULL;
//		emptyBlock_ptr->next = newNode;
//		emptyBlock_ptr = newNode;
//		//emptyBlock_ptrNode->next = newNode;
//		//emptyBlock_ptrNode = newNode;
//	}
//
//
//}
//
//void BFMemory::printList() {
//	Node * walkList_ptr = front;
//	walkList_ptr = walkList_ptr->next;
//	for (int i = 0; i < numElements; i++) {
//		cout << i << ": " << walkList_ptr->process_id << endl;
//		walkList_ptr = walkList_ptr->next;
//	}
//}