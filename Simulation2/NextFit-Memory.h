#pragma once

#include <iostream>
using namespace std;


struct Node {
	int pid;

	Node *next;
};

class NFMemory {
public:
	NFMemory();
	~NFMemory();
	void initializeList();
	void printList();
private:
	Node *front;
	Node header;
	Node *current;
	int numElements;
};

NFMemory::NFMemory() {
	front = current = &header;
	header.next = NULL;
	numElements = 128;
}

NFMemory::~NFMemory() {

};

void NFMemory::initializeList() {
	Node * newNode = new Node;
	current = newNode;
	//Node * currentNode = newNode;
	front->next = newNode;
	newNode->pid = 0;
	newNode->next = NULL;

	for (int i = 0; i < numElements - 1; i++) {
		newNode = new Node;
		newNode->pid = 0;
		newNode->next = NULL;
		current->next = newNode;
		current = newNode;
		//currentNode->next = newNode;
		//currentNode = newNode;
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