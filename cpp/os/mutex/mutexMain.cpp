#include "mutex.hpp"
#include <iostream>

int main() {
    try {
        experis::Mutex mutex;

        mutex.Lock();
        mutex.Unlock();

    }catch(const experis::ExcNotEnoughPermission& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcNotEnoughSyncResources& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const std::bad_alloc& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcMutexIsAlreadyLocked& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcDoesNotOwnCurrentMutex& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}