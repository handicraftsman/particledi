#include "particledi.hpp"

#include <iostream>

class print_service : public particledi::dependency {
public:
  print_service() {
    std::cout << "print_service initialized" << std::endl;
  }

  virtual ~print_service() {
    std::cout << "print_service destroyed" << std::endl;
  }

  void print(std::string msg) {
    std::cout << msg << std::endl;
  }
};

class a_class {
public:
  a_class(particledi::dm_ptr dm)
  : ps(dm->get<print_service>())
  {
    std::cout << "a_class initialized" << std::endl;
  }

  ~a_class() {
    std::cout << "a_class destroyed" << std::endl;
  }

  void do_something() {
    ps->print("Hello, World!");
  }

  std::shared_ptr<print_service> ps;
};

int main(int argc, char** argv) {
  particledi::dm_ptr dm = particledi::dm::create();
  dm->set<print_service>(new print_service());

  a_class c(dm);
  c.do_something();

  return 0;
}
