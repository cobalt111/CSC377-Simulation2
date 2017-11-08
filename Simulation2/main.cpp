#include <iostream>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
#include "BestFit-Memory.h"
#include "WorstFit-Memory.h"
#include "Request-Generator.h"



int main(){
    srand(time( NULL ));
    FirstFit ffMemory;
    ffMemory.initializeList();
    int placeholder, successTester;
    //int deallocate = 0, allocate = 0, allocateSuccess = 0;

    for(int i = 1; i < 50001; i++){
        cout << "Loop: " << i << endl;
        if(generateRequest() == 1){
            //allocate++;
            placeholder = generate_processSize();
            cout << "Allocate Process " << i << ", Size  " << placeholder << endl;
            successTester = ffMemory.allocate_memory(i, placeholder);
            if(successTester != -1){
                addProcess(i);
            }
        }
        else{
            //deallocate++;
            cout << "Deallocating... " << endl;
            placeholder = generate_deallocateNum();
            cout << "Deallocate Process " << placeholder << endl;
            ffMemory.deallocate_mem(placeholder);
        }

//        cout << "Number of Allocations: " << allocate << endl;
//        cout << "Number of Successful Allocations: " << allocateSuccess << endl;
//        cout << "Number of Deallocations: " << deallocate << endl;
    }
    ffMemory.printList();
    cout << "Fragments: " << ffMemory.fragment_count() << endl;
    printProcessList();

    return 0;
}
