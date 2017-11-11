#pragma once
#include <iostream>
#include "Memory-v2.h"
using namespace std;

class FFMemory : public Memory{
public:
    int allocate_mem(int process_id, int num_units);
private:
};

int FFMemory::allocate_mem(int process_id, int num_units){

    walkList_ptr = front_ptr;
    int allocateSize = 0, nodesTraversed_local = 0;

    if (num_units < 3 || num_units > 10) { return -1; }

    for(int i = 0; i < num_elements; i++){

        allocateSize = 0;

        if(walkList_ptr == NULL){
            denied_allocations++;
            num_of_allocations++;
            return -1;
        }

        if(walkList_ptr->process_id == -1){
            emptyBlock_ptr = walkList_ptr;

            while(walkList_ptr != NULL && walkList_ptr->process_id == -1 && allocateSize < num_units){
                allocateSize++;
                walkList_ptr = walkList_ptr->next;
                nodesTraversed_local++;

            }
            if(allocateSize == num_units){

                walkList_ptr = emptyBlock_ptr;

                while(allocateSize != 0){
                    walkList_ptr->process_id = process_id;
                    walkList_ptr = walkList_ptr->next;
                    allocateSize--;
                }
                num_of_allocations++;
                nodes_traversed += nodesTraversed_local;
                return nodesTraversed_local;
            }

            if(walkList_ptr == NULL){
                denied_allocations++;
                num_of_allocations++;
                return -1;
            }



        }

        walkList_ptr = walkList_ptr->next;
        nodesTraversed_local++;
    }
}
