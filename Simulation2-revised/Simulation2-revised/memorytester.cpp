#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Memory-v2.h"
#include "FirstFit-v2.h"
#include "NextFit-v2.h"
#include "BestFit-v2.h"
#include "WorstFit-v2.h"
using namespace std;

void generator(FFMemory& ffMemory, NFMemory& nfMemory, BFMemory & bfMemory, WFMemory & wfMemory);

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
	BFMemory bfMemory;
	WFMemory wfMemory;
    generator(ffMemory, nfMemory, bfMemory, wfMemory);
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
    cout << "Percentage Denied = " << ffMemory.get_percentage_denied() << endl;

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
    cout << "Total deallocations = " << nfMemory.get_totalDeallocations() << endl;

	//Best Fit Display
	cout << "\nBest Fit:" << endl;
	bfMemory.print_list();
	cout << endl << "Statistics: " << endl;
	cout << "Current Fragmentations: " << bfMemory.fragment_count() << endl;
	bfMemory.calculate_average_allocationTime();
	bfMemory.calculate_average_fragmentation();
	bfMemory.calculate_percentage_denied();
	cout << "Average Amount of Fragmentations = " << bfMemory.get_average_fragmentation() << endl;
	cout << "Average Allocation Time = " << bfMemory.get_average_allocationTime() << endl;
	cout << "Percentage Denied = " << bfMemory.get_percentage_denied() << endl;
	cout << "Total allocations = " << bfMemory.get_totalAllocations() << endl;
	cout << "Total denied allocations = " << bfMemory.get_totalDeniedAllocations() << endl;
	cout << "Total deallocations = " << bfMemory.get_totalDeallocations() << endl;

	//Worst Fit Display
	cout << "\nWorst Fit:" << endl;
	wfMemory.print_list();
	cout << endl << "Statistics: " << endl;
	cout << "Current Fragmentations: " << wfMemory.fragment_count() << endl;
	wfMemory.calculate_average_allocationTime();
	wfMemory.calculate_average_fragmentation();
	wfMemory.calculate_percentage_denied();
	cout << "Average Amount of Fragmentations = " << wfMemory.get_average_fragmentation() << endl;
	cout << "Average Allocation Time = " << wfMemory.get_average_allocationTime() << endl;
	cout << "Percentage Denied = " << wfMemory.get_percentage_denied() << endl;
	cout << "Total allocations = " << wfMemory.get_totalAllocations() << endl;
	cout << "Total denied allocations = " << wfMemory.get_totalDeniedAllocations() << endl;
	cout << "Total deallocations = " << wfMemory.get_totalDeallocations() << endl;


    return 0;

}

void generator(FFMemory& ffMemory, NFMemory& nfMemory, BFMemory & bfMemory, WFMemory & wfMemory){
    int placeholder = 0, allocationChecker = 0, deallocateIndex = 0, deallocatePID = 0, randnum = 0;
    std::vector<int> process_vectorFF;
    std::vector<int> process_vectorNF;
	std::vector<int> process_vectorBF;
	std::vector<int> process_vectorWF;
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
			//BFMemory Loop
			allocationChecker = bfMemory.allocate_mem(i, randnum);
			if (allocationChecker != -1) {
				process_vectorBF.push_back(i);
				bfMemory.fragment_count();
			}
			//WFMemory Loop
			allocationChecker = wfMemory.allocate_mem(i, randnum);
			if (allocationChecker != -1) {
				process_vectorWF.push_back(i);
				wfMemory.fragment_count();
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
				//BFMemory Loop
				if (process_vectorBF.size() != 0) {
					deallocateIndex = (rand() % process_vectorBF.size());
					deallocatePID = process_vectorBF[deallocateIndex];
					process_vectorBF.erase(process_vectorBF.begin() + deallocateIndex);
					bfMemory.deallocate_mem(deallocatePID);
				}
				//WFMemory Loop
				if (process_vectorWF.size() != 0) {
					deallocateIndex = (rand() % process_vectorWF.size());
					deallocatePID = process_vectorWF[deallocateIndex];
					process_vectorWF.erase(process_vectorWF.begin() + deallocateIndex);
					wfMemory.deallocate_mem(deallocatePID);
				}
            }

        }
        //ffMemory.print_list();
    }
}
