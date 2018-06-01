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

# A simple example

```cpp
#include <particledi.hpp>

#include <iostream>

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
  particledi::dm dm; // creates a dependency manager

  dm.set("foo", new foo("Hello, World")); // registers an instance of foo as a foo
  
  dm.get<foo>("foo")->print_message(); // gets the foo and prints it's messsage

  return 0; // all objects are destroyed properly because they're stored in std::shared_ptr instances
}

// To use it as a dependency itself:
int main(int argc, char** argv) {
  particledi::dm_ptr dm = particledi::dm::create();
  dm->set("foo", new foo("Hello, World!"));

  dm->get<foo>("foo")->print_message();

  return 0;
}
```

Build and run this to see this:

```
hi
Hello, World!
bye
```

# A Dependency Injection example

Also demonstrates nameless setter/getter syntax.

```cpp
#include <particledi.hpp>

#include <iostream>

// A dependency to inject
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

// A class which will use the dependency above
class a_class {
public:
  a_class(particledi::dm_ptr dm)
  : ps(dm->get<print_service>()) // getting a print_service from the dm
  {
    std::cout << "a_class initialized" << std::endl;
  }

  ~a_class() {
    std::cout << "a_class destroyed" << std::endl;
  }

  void do_something() {
    ps->print("Hello, World!"); // using the print_service
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
``` 

This is the output:

```
print_service initialized
a_class initialized
Hello, World!
a_class destroyed
print_service destroyed
```