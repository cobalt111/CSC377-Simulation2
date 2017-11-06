#pragma once

#include <iostream>
using namespace std;


//struct Node {
//	int pid;
//	Node *next;
//};

class NFMemory {
public:
	NFMemory();
	~NFMemory();
	void initializeList();
	void printList();
	int allocate_memory(int process_id, int num_units);
	int deallocate_mem(int process_id);
private:
	Node *front;
	Node header;
	Node *current;
	// need lastNode pointer from previous nextfit 
	Node * lastNode;
	int numElements;
	int num_of_allocations;
	int nodes_traversed;
	int denied_allocations;
};

NFMemory::NFMemory() {
	front = current = &header;
	header.next = NULL;
	numElements = 128;
	num_of_allocations = 0;
	nodes_traversed = 0;
	denied_allocations = 0;

	// if lastNode has never been used, set to front
	if (lastNode == NULL) {
		lastNode = front;
	}
}

NFMemory::~NFMemory() {

};

void NFMemory::initializeList() {
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

void NFMemory::printList() {
	Node * walkPointer = front;
	walkPointer = walkPointer->next;
	for (int i = 0; i < numElements; i++) {
		cout << i << ": " << walkPointer->pid << endl;
		walkPointer = walkPointer->next;
	}
}

int NFMemory::allocate_memory(int process_id, int num_units) {
	// walkpointer is set to the last node used in the last operation
	Node * walkPointer = lastNode;
	int allocateSize = 0;
	int nodesTraversed_local = 0;
	if (num_units < 3 || num_units > 10) {
		return -1;
	}
	for (int i = 0; i < numElements; i++) {
		if (walkPointer->pid == 0) {
			current = walkPointer; //Save starting location of empty block
			while (walkPointer->pid == 0) {
				allocateSize++;
				if (allocateSize == num_units) {
					break;
				}
				walkPointer = walkPointer->next;
				nodesTraversed_local++;
			}
			if (allocateSize >= num_units) {
				walkPointer = current;
				for (int z = 0; z < num_units; z++) {
					walkPointer->pid = process_id;
					walkPointer = walkPointer->next;
				}
				num_of_allocations++;
				nodes_traversed += nodesTraversed_local;
				// change lastNode to the successful current
				lastNode = current;
				return nodesTraversed_local;
			}

		}
		walkPointer = walkPointer->next;
		nodesTraversed_local++;
	}
	denied_allocations++;
	return -1;
}

int NFMemory::deallocate_mem(int process_id) {
	Node * walkPointer = front->next;
	while (walkPointer->pid != process_id) {
		walkPointer = walkPointer->next;
		if (walkPointer->next == NULL) {
			return -1;
		}
	}
	while (walkPointer->pid == process_id) {
		walkPointer->pid = 0;
		walkPointer = walkPointer->next;
	}
	return 1;
}