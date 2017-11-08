#include <iostream>
#include "Request-Generator.h"

int main(){
    for (int i = 0; i < 10; i++){
        addProcess(i);
    }
    printProcessList();
    removeProcess(3);
    printProcessList();
    return 0;
}
