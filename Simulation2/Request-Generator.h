#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

std::vector<int> process_vector;
//srand(time(NULL)));

int addProcess(int process_id){
    process_vector.push_back(process_id);
}

void removeProcess(int processLocation){
    cout << "Remove element " << processLocation << endl;
    process_vector.erase(process_vector.begin()+processLocation);
}

int generateRequest(){
    return (rand() % 2);
}

int generate_processSize(){
    return ((rand() % 7) + 3);
}

int generate_deallocateNum(){
    int number, process;
    if (process_vector.size() == 0){
        cout << "No Processes Running!" << endl;
        return -1;
    }
    number = ((rand() % process_vector.size()));

    cout << "Number in process list is: " << number << endl;
    cout << "Process ID is : " << process_vector[number] << endl;
    process = process_vector[number];
    removeProcess(number);

    return process;
}

void printProcessList(){
    cout << "Process list is:";
    for (int i=0; i < process_vector.size(); i++){
        cout << ' ' << process_vector[i];
    }
    cout << endl;
}
