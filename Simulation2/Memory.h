#pragma once

#include <iostream>
using namespace std;


struct Node {
	int pid;
	Node *next;
};

class Memory {
public:
	Memory();
	~Memory();
	void initializeList();
	void printList();
	virtual int allocate_memory(int process_id, int num_units);
	int deallocate_mem(int process_id);
	int fragment_count();
protected:
	Node *front;
	Node header;
	Node *current;
	int numElements;
	int num_of_allocations;
	int nodes_traversed;
	int denied_allocations;
};

Memory::Memory() {
	front = current = &header;
	header.next = NULL;
	numElements = 128;
	num_of_allocations = 0;
	nodes_traversed = 0;
	denied_allocations = 0;
}

Memory::~Memory() {

};

void Memory::initializeList() {
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

void Memory::printList() {
	Node * walkPointer = front;
	walkPointer = walkPointer->next;
	for (int i = 0; i < numElements; i++) {
		cout << i << ": " << walkPointer->pid << endl;
		walkPointer = walkPointer->next;
	}

	cout << "Number of Fragments: " << fragment_count() << endl << endl;
}

int Memory::allocate_memory(int process_id, int num_units) {
	return -1;
}



int Memory::deallocate_mem(int process_id) {
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

int Memory::fragment_count() {

	Node * walkPointer = front->next;
	int numHoles = 0;
	int currentHole = 0;


	while (walkPointer->next)
	{
		// if a 0 is found
		if (walkPointer->pid == 0) {

			// loop to count the number of contiguous 0s
			while (walkPointer->pid == 0) {
				currentHole++;
				if (walkPointer->next) {
					walkPointer = walkPointer->next;
				}
				else break;
			}

			// if the number of contiguous 0s was 1 or 2
			if (currentHole < 3 && currentHole > 0) {
				numHoles++;
			}

			// reset counter
			currentHole = 0;

		}

		if (walkPointer->next) {
			walkPointer = walkPointer->next;
		}
		else return numHoles;

	}
}