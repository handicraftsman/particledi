#include "particledi.hpp"

#include <iostream>

class foo : public particledi::dependency {
public:
  foo(std::string _bar)
  : bar(_bar)
  {
    std::cout << "hi" << std::endl;
  }

  virtual ~foo() {
    std::cout << "bye" << std::endl;
  }

  void print_message() {
    std::cout << bar << std::endl;
  }

  std::string bar;
};

int main(int argc, char** argv) {
  particledi dm;
  dm.set("foo", new foo("Hello, World!"));

  dm.get<foo>("foo")->print_message();

  return 0;
}
