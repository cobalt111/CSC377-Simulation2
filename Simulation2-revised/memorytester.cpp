#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Memory-v2.h"
#include "FirstFit-v2.h"
#include "NextFit-v2.h"
using namespace std;

void generator(FFMemory& ffMemory, NFMemory& nfMemory);

int main(){
//    Memory testerMem;
//    testerMem.print_list();
//    cout << endl;
//    testerMem.deallocate_mem(0);
//    testerMem.print_list();
//    cout << endl;
//    testerMem.deallocate_mem(-1);
//    testerMem.print_list();
    srand(time(NULL));
    FFMemory ffMemory;
    NFMemory nfMemory;
    generator(ffMemory, nfMemory);
    //First Fit Display

    cout << "First Fit:" << endl;
    ffMemory.print_list();
    cout << endl << "Statistics: " << endl;
    cout << "Current Fragmentations: " << ffMemory.fragment_count() << endl;
    ffMemory.calculate_average_allocationTime();
    ffMemory.calculate_average_fragmentation();
    ffMemory.calculate_percentage_denied();
    cout << "Average Amount of Fragmentations = " << ffMemory.get_average_fragmentation() << endl;
    cout << "Average Allocation Time = " << ffMemory.get_average_allocationTime() << endl;
    cout << "Percentage Denied = " << ffMemory.get_percentage_denied();

    //Next Fit Display
    cout << "\nNext Fit:" << endl;
    nfMemory.print_list();
    cout << endl << "Statistics: " << endl;
    cout << "Current Fragmentations: " << nfMemory.fragment_count() << endl;
    nfMemory.calculate_average_allocationTime();
    nfMemory.calculate_average_fragmentation();
    nfMemory.calculate_percentage_denied();
    cout << "Average Amount of Fragmentations = " << nfMemory.get_average_fragmentation() << endl;
    cout << "Average Allocation Time = " << nfMemory.get_average_allocationTime() << endl;
    cout << "Percentage Denied = " << nfMemory.get_percentage_denied() << endl;
    cout << "Total allocations = " << nfMemory.get_totalAllocations() << endl;
    cout << "Total denied allocations = " << nfMemory.get_totalDeniedAllocations() << endl;
    cout << "Total deallocations = " << nfMemory.get_totalDeallocations();

    return 0;

}

void generator(FFMemory& ffMemory, NFMemory& nfMemory){
    int placeholder = 0, allocationChecker = 0, deallocateIndex = 0, deallocatePID = 0, randnum = 0;
    std::vector<int> process_vectorFF;
    std::vector<int> process_vectorNF;
    for(int i = 0; i < 10000; i++){
        placeholder = rand() % 3;
        if(placeholder != 0){
            randnum = (rand() % 7) + 3;
            cout << "Allocating " << i << " , " << randnum << endl;
            //FFMemory Loop
            allocationChecker = ffMemory.allocate_mem(i,randnum);
            if(allocationChecker != -1){
                process_vectorFF.push_back(i);
                ffMemory.fragment_count();
            }
            //NFMemory Loop
            allocationChecker = nfMemory.allocate_mem(i,randnum);
            if(allocationChecker != -1){
                process_vectorNF.push_back(i);
                nfMemory.fragment_count();

            }
        }
        else{
            cout << "Deallocating...\n";
            if(i > 0){
                //FFMemory Loop
                if(process_vectorFF.size() != 0){
                    deallocateIndex = (rand() % process_vectorFF.size());
                    deallocatePID = process_vectorFF[deallocateIndex];
                    process_vectorFF.erase(process_vectorFF.begin() + deallocateIndex);
                    ffMemory.deallocate_mem(deallocatePID);
                }
                //NFMemory Loop
                if(process_vectorNF.size() != 0){
                    deallocateIndex = (rand() % process_vectorNF.size());
                    deallocatePID = process_vectorNF[deallocateIndex];
                    process_vectorNF.erase(process_vectorNF.begin() + deallocateIndex);
                    nfMemory.deallocate_mem(deallocatePID);
                }
            }

        }
        //ffMemory.print_list();
    }
}
