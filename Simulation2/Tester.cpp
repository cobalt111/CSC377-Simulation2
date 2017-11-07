#include <iostream>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
#include "BestFit-Memory.h"
#include "WorstFit-Memory.h"

using namespace std;


int main() {

	//FirstFit newList;
	//newList.initializeList();
	//cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
	//newList.allocate_memory(1, 8);
	//newList.printList();
	//cout << "NUMBER 2:\n";
	//newList.allocate_memory(2, 10);
	//newList.printList();
	//cout << "GETTING RID OF PROCESS 1\n";
	//newList.deallocate_mem(1);
	//newList.printList();
	//cout << "PUTTING SOMETHING SMALLER IN:\n";
	//newList.allocate_memory(3, 6);
	//newList.printList();
	//cout << "PUTTING SIZE 3 IN NOW:\n";
	//newList.allocate_memory(4, 3);
	//newList.printList();

	//NextFit newList;
	//newList.initializeList();
	//cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
	//newList.allocate_memory(1, 8);
	//newList.printList();
	//cout << "NUMBER 2:\n";
	//newList.allocate_memory(2, 10);
	//newList.printList();
	//cout << "GETTING RID OF PROCESS 1\n";
	//newList.deallocate_mem(1);
	//newList.printList();
	//cout << "PUTTING SOMETHING SMALLER IN:\n";
	//newList.allocate_memory(3, 6);
	//newList.printList();
	//cout << "PUTTING SIZE 3 IN NOW:\n";
	//newList.allocate_memory(4, 3);
	//newList.printList();

	BestFit newList;
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
	cout << "PUTTING SIZE 7 IN NOW:\n";
	newList.allocate_memory(5, 7);
	newList.printList();
	cout << "GETTING RID OF PROCESS 4\n";
	newList.deallocate_mem(4);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(6, 3);
	newList.printList();


	return 0;
}