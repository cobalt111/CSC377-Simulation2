void generator(FFMemory& ffMemory, NFMemory& nfMemory, BFMemory & bfMemory, WFMemory & wfMemory, int run_amount){
    int placeholder = 0, allocationChecker = 0, deallocateIndex = 0, deallocatePID = 0, randnum = 0;
    std::vector<int> process_vectorFF;
    std::vector<int> process_vectorNF;
	std::vector<int> process_vectorBF;
	std::vector<int> process_vectorWF;
    for(int i = 0; i < run_amount; i++){
        placeholder = rand() % 3;
        if(placeholder != 0){
            randnum = (rand() % 7) + 3;
            //cout << "Allocating " << i << " , " << randnum << endl;
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
            //cout << "Deallocating...\n";
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
