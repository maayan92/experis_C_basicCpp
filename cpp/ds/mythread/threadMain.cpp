#include "thread.hpp"
#include <iostream>

namespace experis {

class HelloDoer : public Runnable {
public:
    //HelloDoer() = default;
    //~HelloDoer() = default;
    virtual void Do() {
        std::cout << "Hello" << std::endl;
    }
};

} // experis

int main() {
    experis::HelloDoer hello;

    try {
        experis::Thread t1(hello);
        experis::Thread t2(hello);

    }catch(const std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}