#pragma once
#include <iostream>
using namespace std;

//Struct that will be the building block of the memory linked list.
struct Node{
    int process_id;             //Used to determine if a process is currently occupying this struct block. -1 means that the block is currently not in use.
    Node* next;                 //Pointer that points to the next node in the linked list.
};

//Parent memory linked list that other sorting algorithms will inherit from.
class Memory{
public:
    //Constructor and Destructor Functions.
    Memory();
    ~Memory();

    //Setter/Getter Functions. This are limited so that main cannot break the memory. Mostly used to get statistical information.
    const float get_average_fragmentation();
    const float get_average_allocationTime();
    const float get_percentage_denied();
    const int get_totalAllocations(){return num_of_allocations;}
    const int get_totalDeallocations(){return total_deallocations;}
    const int get_totalDeniedAllocations(){return denied_allocations;}
    //Statistical Functions. These will be used frequently to keep the statistics up to date. WIll be utilized by the statistics display component.
    void calculate_average_fragmentation();
    void calculate_average_allocationTime();
    void calculate_percentage_denied();

    //Memory control functions
    virtual int allocate_mem(int process_id, int num_units);        //This will always be overwritten by the algorithm that is using the memory class, but here for completeness.
    int deallocate_mem(int process_id);                             //This will be the same for every algorithm. Memory takes care of deallocation.
    int fragment_count();                                           //Returns number of fragments currently in memory.
    void print_list();
protected:
    //3 Default Pointers that allow for manipulating the Memory regardless of Algorithm.
    Node* front_ptr;            //Points to the front of the memory linked list.
    Node* walkList_ptr;         //Pointer used to walk through the list.
    Node* emptyBlock_ptr;       //Pointer used to save the start of empty blocks when they are found/Remember where to start in Next-Fit.

    //Variables used for statistic calculations of the memory at any given moment during execution.
    int num_of_allocations;         //Total number of allocations including the denied ones.
    int nodes_traversed;            //Total number of nodes_traversed.
    int denied_allocations;
    int total_fragments;            //Total number of fragments after each allocation operation thus far.
    int total_deallocations;

    //Variables that store the statistics from the statistic calculations as execution continues.
    float average_fragmentation;                //Stores the average fragmentation after each allocation operation: = fragmentations / num_of_allocations.
    float average_allocationTime;               //Stores the average allocation time after each allocation operation: = nodes_traversed / num_of_allocations.
    float percentage_denied;                    //Percentage of allocations that were denied. = denied_allocations / num_of_allocations.

    //Variable that will decide the size of the linked list/memory size.
    int num_elements;
};

//Memory will set all of the values and use the default num_elements of 128. It will also create the linked list in its entirety.
Memory::Memory(){
    //Set initial values
    num_of_allocations = 0;
    nodes_traversed = 0;
    denied_allocations = 0;
    total_fragments = 0;
    total_deallocations = 0;

    num_elements = 128;

    //Begin filling the memory with nodes.
    Node* constructorNode = new Node;
    front_ptr = constructorNode;
    walkList_ptr = constructorNode;
    constructorNode->process_id = -1;
    constructorNode->next = NULL;
    //Loop to fill the rest of the nodes in;
    for(int i = 0; i < num_elements - 1; i++){
        //Make the new node
        constructorNode = new Node;
        constructorNode->process_id = -1;
        constructorNode->next = NULL;
        //Connect it to the existing list
        walkList_ptr->next = constructorNode;
        walkList_ptr = constructorNode;
    }
    //Reset walkList_ptr for allocation algorithms.
    walkList_ptr = front_ptr;
}

Memory::~Memory(){

}

const float Memory::get_average_fragmentation(){return average_fragmentation;}
const float Memory::get_average_allocationTime(){return average_allocationTime;}
const float Memory::get_percentage_denied(){ return percentage_denied;}

void Memory::calculate_average_fragmentation(){
    average_fragmentation = (float)total_fragments / (float)num_of_allocations;
}
void Memory::calculate_average_allocationTime(){
    average_allocationTime = (float)nodes_traversed / ((float)num_of_allocations - (float)denied_allocations);
}
void Memory::calculate_percentage_denied(){
	// changed this to multiply by 100 so it would be a percentage
    percentage_denied = ((float)denied_allocations / (float)num_of_allocations) * 100;
}

int Memory::allocate_mem(int process_id, int num_units){
    return -1;
}

int Memory::deallocate_mem(int process_id){
    walkList_ptr = front_ptr;

    while(walkList_ptr != NULL && walkList_ptr->process_id != process_id){
        //check to see that we haven't ran into the end of the list without finding the pid

        walkList_ptr = walkList_ptr->next;
        //if we did then return that the deallocation failed
    }
    //Check to make sure there wasn't a failure. If there was don't continue.
    if(walkList_ptr == NULL){
        walkList_ptr = front_ptr;
        total_deallocations++;
        return -1;
    }
    //If  you have found the section to be removed then replace them.
    while(walkList_ptr != NULL && walkList_ptr->process_id == process_id){
            walkList_ptr->process_id = -1;      //set it back to a free block.
            walkList_ptr = walkList_ptr->next;
    }
    //Reset walkList_ptr for the next allocate/deallocate
    walkList_ptr = front_ptr;
    total_deallocations++;
    return 1;
}

int Memory::fragment_count(){
    int fragment = 0, currentCount = 0;
    walkList_ptr = front_ptr;
    //cout << "Starting fragment counting..." << endl;
    while(walkList_ptr != NULL){
        currentCount = 0;
        if(walkList_ptr->process_id == -1){
            //cout << "Empty block found..." << endl;
            while(walkList_ptr != NULL && walkList_ptr->process_id == -1){
                //cout << "Incrementing count..." << endl;
                currentCount++;
                walkList_ptr = walkList_ptr->next;
            }
            //cout << "End of empty block reached. Size " << currentCount << endl;
            if(currentCount > 0 && currentCount < 3){
                //cout << "Fragment found..." << endl;
                fragment++;

            }
            if(walkList_ptr == NULL){
                total_fragments += fragment;
                return fragment;
            }
        }
        //cout << "Block not empty. Moving on..." << endl;
        walkList_ptr = walkList_ptr->next;

    }
    total_fragments += fragment;
    return fragment;
}

void Memory::print_list(){
    //Create a new pointer so there is no need to mess with the essential ptrs
    Node* printPointer = front_ptr;
    //Counter is used for labeling data blocks.
    int counter = 0;
    while(printPointer != NULL){
        cout << counter << ":\t" << printPointer->process_id << endl;
        printPointer = printPointer->next;
        counter++;
    }
}
