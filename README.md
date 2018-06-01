# ParticleDI

# Building and installing

```bash
$ git clone https://github.com/handicraftsman/particledi
$ cd particledi
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release # Or Debug if you're a developer
$ make
$ sudo make install
```

# Using in your programs

ParticleDI provides a .pc file for pkg-config. This means that you can use it
as a dependency in any build system which supports pkg-config. This will be
`dependency('particledi')` in Meson
and `pkg_search_module(ParticleDI REQUIRED particledi)` in CMake.

Code sample:

```cpp
#include <particledi.hpp>

// A sample class. All injectable classes must inherit from particledi::dependency.
// This is required to ensure that all objects are destroyed correctly.
class foo : public particledi::dependency {
public:
  foo(std::string _bar)
  : bar(_bar)
  {
    std::cout << "hi" << std::endl;
  }

  virtual ~foo() {
    // Destructors MUST be virtual because dependencies are stored as pointers to
    // particledi::dependency instances.
    std::cout << "bye" << std::endl;
  }

  void print_message() {
    std::cout << bar << std::endl;
  }

  std::string bar;
};

int main(int argc, char** argv) {
  particledi dm; // creates a dependency manager (or a service holder)

  dm.set("foo", new foo("Hello, World")); // registers an instance of foo as a foo
  
  dm.get<foo>("foo")->print_message(); // gets the foo and prints it's messsage

  return 0; // all objects are destroyed properly because they're stored in std::shared_ptr instances
}
```

Build and run this to see this:

```
hi
Hello, World!
bye
```