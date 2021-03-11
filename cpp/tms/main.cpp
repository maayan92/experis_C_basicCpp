#include "tms.hpp"

typedef experis::Tms Tms;
typedef Tms::TmsArgs TmsArgs;

int main(int a_argc, char* a_argv[]) {
    TmsArgs tmsArgs;

    tmsArgs.push_back(const_cast<char*>("-tolow"));
    tmsArgs.push_back(const_cast<char*>("-out"));
    //tmsArgs.push_back(const_cast<char*>("outTolow.txt"));
    tmsArgs.push_back(const_cast<char*>("-toup"));
    //tmsArgs.push_back(const_cast<char*>("-hfjdfjdhf"));
    tmsArgs.push_back(const_cast<char*>("-out"));
    tmsArgs.push_back(const_cast<char*>("outToup.txt"));
    tmsArgs.push_back(const_cast<char*>("file.txt"));

    Tms tms(tmsArgs);
/*  
    for(int position = 1 ; position < a_argc ; ++position) {
        tmsArgs.push_back(const_cast<char*>(a_argv[position]));
    }
*/

    try {
        tms.Run();
    }catch(const std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}