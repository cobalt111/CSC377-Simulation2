#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;

#include "Memory-v2.h"
#include "FirstFit-v2.h"
#include "NextFit-v2.h"
#include "BestFit-v2.h"
#include "WorstFit-v2.h"
#include "request_generator.h"
#include "statistics_handler.h"

int main(){
    srand(time(NULL));
    FFMemory ffMemory;
    NFMemory nfMemory;
	BFMemory bfMemory;
	WFMemory wfMemory;
	int generation_num = 10000;

    generator(ffMemory, nfMemory, bfMemory, wfMemory, generation_num);
    cout << "Statistics with " << generation_num << " generations:\n\n";
    //First Fit Display
    cout << "First Fit:";
    ffMemory.print_list();
    display_ff(ffMemory);

    //Next Fit Display
    cout << "\nNext Fit:";
    nfMemory.print_list();
    display_nf(nfMemory);

    //Best Fit Display
    cout << "\nBest Fit:";
    bfMemory.print_list();
    display_bf(bfMemory);

    //Worst Fit Display
    cout << "\nWorst Fit:";
    wfMemory.print_list();
    display_wf(wfMemory);
    cout << endl;

    return 0;

}

