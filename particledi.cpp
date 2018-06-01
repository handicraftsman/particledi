#include "particledi.hpp"

particledi::dependency::dependency() {}
particledi::dependency::~dependency() {}

void particledi::set_sptr(std::string name, std::shared_ptr<particledi::dependency> dep) {
  deps[name] = dep;
}

std::shared_ptr<particledi::dependency> particledi::get_dep(std::string name) {
  return deps[name];
}
