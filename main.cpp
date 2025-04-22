#ifndef MAX_DATA
#define MAX_DATA 10000
#endif

#include "subroutines.hpp"
#include <memory>

int main(){
    auto data_ptr = std::make_unique<ProgramData<MAX_DATA>>();
    
    ProgramData_exec(data_ptr);
}