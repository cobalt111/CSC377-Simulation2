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
 private:
	Node *front;
	Node header;
	Node *current;
	int numElements;
	int num_of_allocations;
	int nodes_traversed;
	int denied_allocations;
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
	Node * walkPointer = front->next;
	int allocateSize = 0;
	int nodesTraversed_local =  0;
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
				return nodesTraversed_local;
			}

		}
		walkPointer = walkPointer->next;
		nodesTraversed_local++;
	}
	denied_allocations++;
	return -1;
}

int FFMemory::deallocate_mem(int process_id) {
    cout << "CALLED DEALLOCATER!\n";
	Node * walkPointer = front->next;
	cout << "walkPointer made\n";
	while (walkPointer->pid != process_id) {
		walkPointer = walkPointer->next;
        cout << "changed walkpointer location!\n";
		if (walkPointer->next == NULL) {
			cout << "\nDidnt find it";
			return -1;
		}
	}
	while (walkPointer->pid == process_id) {
        cout << "DELETING " << process_id << endl;
		walkPointer->pid = 0;
        cout << "MOVING ON\n";
		walkPointer = walkPointer->next;
	}
	return 1;
}
