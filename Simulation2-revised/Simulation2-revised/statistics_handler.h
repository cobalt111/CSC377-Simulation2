void display_ff(FFMemory& ffMemory){
    cout << "\nCurrent Fragmentations: " << ffMemory.fragment_count() << endl;
    ffMemory.calculate_average_allocationTime();
    ffMemory.calculate_average_fragmentation();
    ffMemory.calculate_percentage_denied();
    cout << "Average Amount of Fragmentations = " << ffMemory.get_average_fragmentation() << endl;
    cout << "Average Allocation Time = " << ffMemory.get_average_allocationTime() << endl;
    cout << "Percentage Denied = " << ffMemory.get_percentage_denied() << endl;
    cout << "Total allocations = " << ffMemory.get_totalAllocations() << endl;
    cout << "Total denied allocations = " << ffMemory.get_totalDeniedAllocations() << endl;
    cout << "Total deallocations = " << ffMemory.get_totalDeallocations() << endl;

}

void display_nf(NFMemory& nfMemory){
    cout << "\nCurrent Fragmentations: " << nfMemory.fragment_count() << endl;
    nfMemory.calculate_average_allocationTime();
    nfMemory.calculate_average_fragmentation();
    nfMemory.calculate_percentage_denied();
    cout << "Average Amount of Fragmentations = " << nfMemory.get_average_fragmentation() << endl;
    cout << "Average Allocation Time = " << nfMemory.get_average_allocationTime() << endl;
    cout << "Percentage Denied = " << nfMemory.get_percentage_denied() << endl;
    cout << "Total allocations = " << nfMemory.get_totalAllocations() << endl;
    cout << "Total denied allocations = " << nfMemory.get_totalDeniedAllocations() << endl;
    cout << "Total deallocations = " << nfMemory.get_totalDeallocations() << endl;
}

void display_bf(BFMemory& bfMemory){
	cout << "\nCurrent Fragmentations: " << bfMemory.fragment_count() << endl;
	bfMemory.calculate_average_allocationTime();
	bfMemory.calculate_average_fragmentation();
	bfMemory.calculate_percentage_denied();
	cout << "Average Amount of Fragmentations = " << bfMemory.get_average_fragmentation() << endl;
	cout << "Average Allocation Time = " << bfMemory.get_average_allocationTime() << endl;
	cout << "Percentage Denied = " << bfMemory.get_percentage_denied() << endl;
	cout << "Total allocations = " << bfMemory.get_totalAllocations() << endl;
	cout << "Total denied allocations = " << bfMemory.get_totalDeniedAllocations() << endl;
	cout << "Total deallocations = " << bfMemory.get_totalDeallocations() << endl;
}

void display_wf(WFMemory& wfMemory){
	cout << "\nCurrent Fragmentations: " << wfMemory.fragment_count() << endl;
	wfMemory.calculate_average_allocationTime();
	wfMemory.calculate_average_fragmentation();
	wfMemory.calculate_percentage_denied();
	cout << "Average Amount of Fragmentations = " << wfMemory.get_average_fragmentation() << endl;
	cout << "Average Allocation Time = " << wfMemory.get_average_allocationTime() << endl;
	cout << "Percentage Denied = " << wfMemory.get_percentage_denied() << endl;
	cout << "Total allocations = " << wfMemory.get_totalAllocations() << endl;
	cout << "Total denied allocations = " << wfMemory.get_totalDeniedAllocations() << endl;
	cout << "Total deallocations = " << wfMemory.get_totalDeallocations() << endl;
}
