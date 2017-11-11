#pragma once
#include <iostream>
#include "Memory-v2.h"
using namespace std;

class NFMemory : public Memory{
public:
    NFMemory();
    int allocate_mem(int process_id, int num_units);
private:
    Node* lastPos_ptr;
};

NFMemory::NFMemory(){
    lastPos_ptr = front_ptr;
}


int NFMemory::allocate_mem(int process_id, int num_units){
    //Set the pointer that will be used to walk through the loop equal to the pointer that stores the location we last stopped at.
    walkList_ptr = lastPos_ptr;
    //allocateSize will be used to count the size of empty blocks. nodesTraversed_local will be returned as specified
    //pastPtr_checker is for the unique case that the lastPos ptr is in the middle of an empty stop preventing potential false
    //denied allocations
    int allocateSize = 0, nodesTraversed_local = 0, pastPtr_checker = 0;
    //Start again keeps track of whether we have looped around already or not, to prevent an infinite loop.
    bool startedAgain = false;

    //This is just a check to makes sure the size of the allocation request is within specification.
    if (num_units < 3 || num_units > 10) { return -1; }
    //This is the outer loop that will always be running as long as the allocation hasn't been accepted or denied.
    while(true){
        //allocateSize and pastPtr need to be reset after each failed traverse so that spaces aren't miscounted.
        allocateSize = 0;
        pastPtr_checker = 0;

        //This if statement checks if the spot we are currently on is the start of an empty block or not.
        //IF it is then we move on to this next big loop that checks the size and also allocates the space.
        //The only time you would leave this loop after finding an empty space is if it 1. Wasnt big enough 2. We hit the null pointer and have to restart.
        if(walkList_ptr->process_id == -1){
            //Save the start of the empty block so that if it's large enough we can return here to begin allocating.
            emptyBlock_ptr = walkList_ptr;

            //This is the loop that checks the size of the empty block. We only break from it if we hit NULL, hit a process before we had enough space
            //or we found a big enough block.
            while(walkList_ptr != NULL && walkList_ptr->process_id == -1 && allocateSize < num_units){
                //We start the loop with inc allocateSize because we have to count the starting area as one of the empty blocks.
                allocateSize++;
                //Walk forward one space and inc necessary things.
                walkList_ptr = walkList_ptr->next;
                nodesTraversed_local++;
                //If we happened to hit the rare case that we are starting at a block thats empty and the lastPos pointer
                //is in the middle of it, we can still check if there is enough allocation size to still allocate past
                //the pointer instead of instantly denying.
                if(walkList_ptr == lastPos_ptr){
                    //This is the start of the loop to check past the lastPos pointer and see if it's large enough to allocate still.
                    //Break only if we hit NULL (meaning the space wasnt big enough), We hit an area already allocated (meaning also it wasn't big enough)
                    //OR we actually found an area that was big enough
                    while((walkList_ptr != NULL) && (walkList_ptr->process_id == -1) && ((allocateSize + pastPtr_checker) < num_units)){
                        //This pastPTR will be used to check the size after the pastPos pointer.
                        pastPtr_checker++;
                        //Walk to the next space after the pastPos ptr and continue on so forth until the while loop breaks
                        walkList_ptr = walkList_ptr -> next;
                        nodesTraversed_local++;
                    }
                    //This subsequent logic handles the two cases of passing or failure. If it failed then we break the entire allocation
                    //Process returning the necessary information and increasing stat counters.
                    if((pastPtr_checker + allocateSize) < num_units){
                        num_of_allocations++;
                        denied_allocations++;
                        return -1;
                    }
                    //This is the case that it was successful, then we go back to emptyBlock start and allocate like normally.
                    else{
                        walkList_ptr = emptyBlock_ptr;
                        allocateSize += pastPtr_checker;
                        while(allocateSize != 0){
                            walkList_ptr->process_id = process_id;
                            walkList_ptr = walkList_ptr->next;
                            allocateSize--;
                        }
                        if(walkList_ptr == NULL){
                            walkList_ptr = front_ptr;
                        }
                        num_of_allocations++;
                        nodes_traversed += nodesTraversed_local;
                        lastPos_ptr = walkList_ptr;
                        return nodesTraversed_local;
                    }
                }
            }
            //This checks to see if the last block we just checked was large enough.
            //If it was then we allocate like normal.
            if(allocateSize == num_units){
                walkList_ptr = emptyBlock_ptr;
                while(allocateSize != 0){
                    walkList_ptr->process_id = process_id;
                    walkList_ptr = walkList_ptr->next;
                    allocateSize--;
                }
                if(walkList_ptr == NULL){
                    walkList_ptr = front_ptr;
                }
                num_of_allocations++;
                nodes_traversed += nodesTraversed_local;
                lastPos_ptr = walkList_ptr;
                return nodesTraversed_local;
            }
            //Checks to see if our lost move resulted in us hitting a null pointer.
            //If we did and this was our first time that means we just need to start again until
            //we hit lastPos ptr meaning there wasn't a space large enough.
            if(walkList_ptr == NULL){
                if(startedAgain){
                    num_of_allocations++;
                    denied_allocations++;
                    return -1;
                }
                else startedAgain = true;
                walkList_ptr = front_ptr;
                nodesTraversed_local++;
            }
        }

        //Even though its way down here. This is the first walk we do while not actually walking through an empty block.

        if(startedAgain != true){
            walkList_ptr = walkList_ptr->next;
            nodesTraversed_local++;
        }
        else if(startedAgain == true && walkList_ptr != front_ptr){
            walkList_ptr = walkList_ptr->next;
            nodesTraversed_local++;
        }else if(startedAgain == true && walkList_ptr == front_ptr && walkList_ptr->process_id != -1){
            walkList_ptr = walkList_ptr->next;
            nodesTraversed_local++;
        }


        if(walkList_ptr == NULL){
                if(startedAgain){
                    num_of_allocations++;
                    denied_allocations++;
                    return -1;
                }
                else startedAgain = true;
                walkList_ptr = front_ptr;
                nodesTraversed_local++;
            }
        }
}
