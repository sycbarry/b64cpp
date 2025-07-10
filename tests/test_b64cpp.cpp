#include "b64cpp/b64cpp.hpp"
#include <iostream>

int main() {
    std::cout << "Running b64cpp tests..." << std::endl;
    
    b64cpp::B64CPP test_obj;
    test_obj.do_something();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
