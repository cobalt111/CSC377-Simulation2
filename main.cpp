#include <iostream>
#include "FirstFit-Memory.h"
#include "NextFit-Memory.h"
#include "BestFit-Memory.h"
#include "WorstFit-Memory.h"
#include "Request-Generator.h"



int main(){
    srand(time( NULL ));
    FirstFit ffMemory;
    NextFit nfMemory;
    ffMemory.initializeList();
    nfMemory.initializeList();
    int placeholder, successTesterFF, successTesterNF;
    int deallocate = 0, allocate = 0, allocateSuccess = 0;

    for(int i = 1; i < 10001; i++){
        cout << "Loop: " << i << endl;
        if(generateRequest() != 0){
            allocate++;
            placeholder = generate_processSize();
            cout << "Allocate Process " << i << ", Size  " << placeholder << endl;
            successTesterFF = ffMemory.allocate_memory(i, placeholder);
            if(successTesterFF != -1){
                addProcessFF(i);
            }
            successTesterNF = nfMemory.allocate_memory(i, placeholder);
            if(successTesterNF != -1){
                addProcessNF(i);
            }

        }
        else{
            deallocate++;
            cout << "Deallocating... " << endl;
            placeholder = generate_deallocateNumFF();
            cout << "Deallocate Process FF " << placeholder << endl;
            ffMemory.deallocate_mem(placeholder);
            cout << "Deallocating..." << endl;
            placeholder = generate_deallocateNumNF();
            cout << "Deallocate Process NF " << placeholder << endl;
            nfMemory.deallocate_mem(placeholder);
        }


    }
    cout << "\nFirst Fit List:\n";
    ffMemory.printList();
    cout << "Fragments: " << ffMemory.fragment_count() << endl;
    printProcessListFF();
    cout << "\nNext Fit List:\n";
    nfMemory.printList();
    cout << "Fragments: " << nfMemory.fragment_count() << endl;
    printProcessListNF();
    cout << "Number of Allocations: " << allocate << endl;
    //cout << "Number of Successful Allocations: " << allocateSuccess << endl;
    cout << "Number of Deallocations: " << deallocate << endl;


    return 0;
}
