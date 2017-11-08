#pragma once
#include <iostream>
#include "Memory.h"
using namespace std;

class FirstFit : public Memory {
public:
	// overriding allocate memory
	int allocate_memory(int process_id, int num_units) override;
	bool findHole(Node* startPoint);
	bool determineSize(int size_in);
	void fillSpace(int process_id, int process_size);

private:
};

//int FirstFit::allocate_memory(int process_id, int num_units) {
//
//	Node * walkPointer = front->next;	//walkPointer will be used to traverse the memory linked-list
//	int allocateSize = 0;			//allocateSize will be used to keep track of how large an empty space is
//	int nodesTraversed_local = 0;		//nodesTraversed_local will keep track of how many nodes we had to walk through
//						//and will be returned as required when there is a success
//	bool bigEnough = false;			//bigEnough is used to break out of the first loop and begin overwriting
//						//the empty space that has been found.
//
//	// check input for error/follows specs
//	if (num_units < 3 || num_units > 10) { return -1; }
//	//Main loop that will be used to walk through the entire memory linked list
//	for (int i = 0; i < numElements; i++) {
//
//		// check if walkPointer is free/an empty space has been found.
//		if (walkPointer->pid == 0) {
//			//Save starting location of empty block
//			current = walkPointer;
//			allocateSize = 0;
//			// loop to check if the found empty block is a large enough size.
//			while (walkPointer->pid == 0) {
//				allocateSize++;
//				// if the size is big enough break and begin filling space
//				if (allocateSize == num_units) {
//					bigEnough = true;
//					break;
//				}
//				//If it isn't big enough yet keep walking as long as you havent hit the end yet
//				else if (walkPointer->next != NULL) {
//					walkPointer = walkPointer->next;
//					nodesTraversed_local++;
//				}
//				//If you have hit the end stop the whole process because there wasn't a space large enough
//				else{
//				    denied_allocations++;
//				    return -1;
//		                }
//			}
//
//			// if a big enough block was found
//			if (bigEnough) {
//
//				// set walkPointer back to start of open space and enter a loop to fill the space
//				walkPointer = current;
//
//				// fill in the open space with pid
//				for (int z = 0; z < num_units; z++) {
//					walkPointer->pid = process_id;
//					walkPointer = walkPointer->next;
//				}
//				//After successfully allocated update statistic sizes and return the number of nodes
//				num_of_allocations++;
//				nodes_traversed += nodesTraversed_local;
//				return nodesTraversed_local;
//			}
//
//		}
//		else{
//			// if pid found was not 0
//			if (walkPointer->next != NULL){
//                		walkPointer = walkPointer->next;
//                		nodesTraversed_local++;
//			}
//			//break because you have hit the end of memory and there wasn't a space
//			else{
//				denied_allocations++;
//                		return -1;
//			}
//		}
//	}
//	// upon failure to find space
//	denied_allocations++;
//	return -1;
//}

int FirstFit::allocate_memory(int process_id, int num_units){
    Node* walkPointer = front;
    while(walkPointer->next != NULL){
        if (findHole(walkPointer) == true){
            if(determineSize(num_units) == true){
                fillSpace(process_id, num_units);
                break;
            }
        }
        else{
            return -1;
        }
    }
    return -1;
}

bool FirstFit::findHole(Node* startPoint){
    emptyStart = startPoint;
    while(emptyStart->pid != 0){
        if(emptyStart->next == NULL){
            return false;
        }
        emptyStart = emptyStart->next;
        nodes_traversed++;

    }
    startPoint = emptyStart;
    return true;
}

bool FirstFit::determineSize(int size_in){
    int size_counter = 0;
    Node* temp = emptyStart;
    while(size_counter < size_in){
        size_counter++;
        if(temp->next == NULL){
            return false;
        }
        else if (temp->pid != 0){
            return false;
        }
        else{
            temp = temp->next;
            nodes_traversed++;
        }
    }
    return true;
}

void FirstFit::fillSpace(int process_id, int process_size){
    for(int i = 0; i < process_size; i++){
        emptyStart->pid = process_id;
        if(emptyStart->next != NULL)
            emptyStart = emptyStart->next;
        else break;
    }
}
