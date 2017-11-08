#include <iostream>
#include"FirstFit-Memory.h"
using namespace std;

int main(){
    FirstFit ffMemory;
    ffMemory.initializeList();
    for(int i = 1; i < 13; i++)
        ffMemory.allocate_memory(i,10);
    ffMemory.allocate_memory(13, 8);
    ffMemory.printList();
    return 0;
}
