#include "particledi.hpp"

particledi::dependency::dependency() {}
particledi::dependency::~dependency() {}

particledi::dm::dm() {}
particledi::dm::~dm() {}

std::shared_ptr<particledi::dm> particledi::dm::create() {
  return std::shared_ptr<particledi::dm>(new particledi::dm());
}

void particledi::dm::set_sptr(std::string name, std::shared_ptr<particledi::dependency> dep) {
  deps[name] = dep;
}

std::shared_ptr<particledi::dependency> particledi::dm::get_dep(std::string name) {
  return deps[name];
}
