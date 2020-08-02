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
    }catch(const experis::ExcValueTooBig& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcInterruptedBySignalHandler& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcTimeOutBeforeLocked& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcMaximumAllowableValue& exc) {
        std::cout << exc.what() << std::endl;
    }
    
    return 0;
}