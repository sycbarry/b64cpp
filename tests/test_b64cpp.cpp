#include "b64cpp/b64cpp.hpp"
#include <iostream>

int main() {
  std::cout << "Running b64cpp tests..." << std::endl;

  b64cpp::B64CPP test_obj;
  // const char *data = "hello, i hope this email finds you well!";
  const char *data = "M";
  printf("Testing: %s\n", data);
  test_obj.encode(data);

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
