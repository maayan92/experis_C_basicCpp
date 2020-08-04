#include "semaphore.hpp"
#include <iostream>

int main() {
    try {
        experis::Semaphore semaphore(5);
        experis::Semaphore semaphoreBinary;

        semaphore.Wait();
        semaphore.Post();
        semaphoreBinary.Wait();
        semaphoreBinary.Post();
    }catch(const std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }
    
    return 0;
}