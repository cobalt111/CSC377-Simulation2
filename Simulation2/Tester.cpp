#include <iostream>
#include <cstdlib>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
using namespace std;

int generateAllocate_Deallocate(){
    int number = rand() % 2;
    return number;

}

int main() {
    int placeholder;
    int catcher;
    FFMemory ffList;
	ffList.initializeList();
//	ffList.allocate_memory(11, 3);
//	ffList.printList();
    for(int i = 1; i < 10001; i++){
        placeholder = generateAllocate_Deallocate();
        cout << "GENERATED: " << placeholder << endl;
        if(placeholder == 1){
            ffList.allocate_memory(i, ((rand() % 7) + 3));
        }
        else{
            catcher = ffList.deallocate_mem((rand() % i) + 1);
        }
        cout << "Loop " << i << ":\n";
        ffList.printList();
    }

//	FFMemory ffList;
//	ffList.initializeList();
//	cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
//	ffList.allocate_memory(1, 8);
//	fList.printList();
//	cout << "NUMBER 2:\n";
//	ffList.allocate_memory(2, 10);
//	ffList.printList();
//	cout << "GETTING RID OF PROCESS 1\n";
//	ffList.deallocate_mem(1);
//	ffList.printList();
//	cout << "PUTTING SOMETHING SMALLER IN:\n";
//	ffList.allocate_memory(3, 6);
//	ffList.printList();
//	cout << "PUTTING SIZE 3 IN NOW:\n";
//	ffList.allocate_memory(4, 3);
//	ffList.printList();

//	NFMemory nfList;
//	nfList.initializeList();
//	cout << "THIS IS THE FIRST ALLOCATION I PROMISE:\n";
//	nfList.allocate_memory(1, 8);
//	nfList.printList();
//	cout << "NUMBER 2:\n";
//	nfList.allocate_memory(2, 10);
//	nfList.printList();
//	cout << "GETTING RID OF PROCESS 1\n";
//	nfList.deallocate_mem(1);
//	nfList.printList();
//	cout << "PUTTING SOMETHING SMALLER IN:\n";
//	nfList.allocate_memory(3, 6);
//	nfList.printList();
//	cout << "PUTTING SIZE 3 IN NOW:\n";
//	nfList.allocate_memory(4, 3);
//	nfList.printList();


	return 0;
}


