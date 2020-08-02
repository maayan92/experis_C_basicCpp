#include "mutex.hpp"
#include <iostream>

int main() {

    try {
        experis::Mutex mutex;

        mutex.Lock();
        mutex.Unlock();

    }catch(const experis::ExcMutexInitFailed& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcLockFailed& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcUnLockFailed& exc) {
        std::cout << exc.what() << std::endl;
    }


    return 0;
}