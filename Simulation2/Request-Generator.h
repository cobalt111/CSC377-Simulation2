
#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

std::vector<int> process_vectorFF;
std::vector<int> process_vectorNF;
//srand(time(NULL)));

int addProcessFF(int process_id){
    process_vectorFF.push_back(process_id);
}

int addProcessNF(int process_id){
    process_vectorNF.push_back(process_id);
}

void removeProcessFF(int processLocation){
    //cout << "Remove element " << processLocation << endl;
    process_vectorFF.erase(process_vectorFF.begin()+processLocation);
}

void removeProcessNF(int processLocation){
    //cout << "Remove element " << processLocation << endl;
    process_vectorNF.erase(process_vectorNF.begin()+processLocation);
}

int generateRequest(){
    return (rand() % 3);
}

int generate_processSize(){
    return ((rand() % 7) + 3);
}

int generate_deallocateNumFF(){
    int number, process;
    if (process_vectorFF.size() == 0){
        //cout << "No Processes Running!" << endl;
        return -1;
    }
    number = ((rand() % process_vectorFF.size()));

    //cout << "Number in process list is: " << number << endl;
    //cout << "Process ID is : " << process_vector[number] << endl;
    process = process_vectorFF[number];
    removeProcessFF(number);

    return process;
}

int generate_deallocateNumNF(){
    int number, process;
    if (process_vectorNF.size() == 0){
        //cout << "No Processes Running!" << endl;
        return -1;
    }
    number = ((rand() % process_vectorNF.size()));

    //cout << "Number in process list is: " << number << endl;
    //cout << "Process ID is : " << process_vector[number] << endl;
    process = process_vectorNF[number];
    removeProcessNF(number);

    return process;
}

void printProcessListFF(){
    cout << "Process list is:";
    for (int i=0; i < process_vectorFF.size(); i++){
        cout << ' ' << process_vectorFF[i];
    }
    cout << endl;
}

void printProcessListNF(){
    cout << "Process list is:";
    for (int i=0; i < process_vectorNF.size(); i++){
        cout << ' ' << process_vectorNF[i];
    }
    cout << endl;
}
