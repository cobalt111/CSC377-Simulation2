#include <iostream>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
using namespace std;


int main() {

	FFMemory newList;
	newList.initializeList();
	cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
	newList.allocate_memory(1, 8);
	newList.printList();
	cout << "NUMBER 2:\n";
	newList.allocate_memory(2, 10);
	newList.printList();
	cout << "GETTING RID OF PROCESS 1\n";
	newList.deallocate_mem(1);
	newList.printList();
	cout << "PUTTING SOMETHING SMALLER IN:\n";
	newList.allocate_memory(3, 6);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(4, 3);
	newList.printList();

	NFMemory newList;
	newList.initializeList();
	cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
	newList.allocate_memory(1, 8);
	newList.printList();
	cout << "NUMBER 2:\n";
	newList.allocate_memory(2, 10);
	newList.printList();
	cout << "GETTING RID OF PROCESS 1\n";
	newList.deallocate_mem(1);
	newList.printList();
	cout << "PUTTING SOMETHING SMALLER IN:\n";
	newList.allocate_memory(3, 6);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(4, 3);
	newList.printList();


	return 0;
}