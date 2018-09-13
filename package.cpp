#include <particlepm.hpp>

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("particledi");
  p->version(PPM::Version("v0.3.2"));
  p->description("A simple Dependency Injection helper");
  p->github(PPM::GitHub("handicraftsman", "particledi"));
  p->license(PPM::License("MIT", "https://github.com/handicraftsman/particledi/blob/master/LICENSE.txt"));

  PPM::TargetPtr lib = p->library("particledi");
  lib->cpp("c++11");
  lib->cpp_files(std::vector<std::string> {
    "particledi.cpp"
  });
}