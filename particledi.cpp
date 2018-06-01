#include "particledi.hpp"

particledi::dependency::dependency() {}
particledi::dependency::~dependency() {}

particledi::no_such_dependency::no_such_dependency(std::string w) : std::runtime_error(w) {}
particledi::already_registered::already_registered(std::string w) : std::runtime_error(w) {}

particledi::dm::dm() {}
particledi::dm::~dm() {}

std::shared_ptr<particledi::dm> particledi::dm::create() {
  return std::shared_ptr<particledi::dm>(new particledi::dm());
}

void particledi::dm::set_sptr(std::string name, std::shared_ptr<particledi::dependency> dep) {
  if (deps.find(name) != deps.end()) {
    throw particledi::already_registered("");
  } else {
    deps[name] = dep;
  }
}

std::shared_ptr<particledi::dependency> particledi::dm::get_dep(std::string name) {
  if (deps.find(name) == deps.end()) {
    throw particledi::no_such_dependency("");
  } else {
    return deps[name];
  }
}
