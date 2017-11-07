#include <iostream>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
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

	NextFit newList;
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

	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(5, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(6, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(7, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(8, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(9, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(10, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(11, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(12, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(13, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(14, 10);
	newList.printList();
	cout << "PUTTING SIZE 3 IN NOW:\n";
	newList.allocate_memory(15, 10);
	newList.printList();
	//cout << "PUTTING SIZE 3 IN NOW:\n";
	//newList.allocate_memory(5, 10);
	//newList.printList();


	return 0;
}