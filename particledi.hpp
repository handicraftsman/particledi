#pragma once

#include <map>
#include <memory>
#include <typeinfo>

namespace particledi {
  class dependency {
  public:
    dependency();
    virtual ~dependency();
  };

  class no_such_dependency : virtual std::runtime_error {
  public:
    no_such_dependency(std::string w);
  };
  class already_registered : virtual std::runtime_error {
  public:
    already_registered(std::string w);
  };

  class dm : public dependency {
  public:
    dm();
    ~dm();
    
    static std::shared_ptr<dm> create();

    std::map<std::string, std::shared_ptr<dependency>> deps;

    void set_sptr(std::string name, std::shared_ptr<dependency> dep);
    inline void set(std::string name, dependency* dptr) {
      set_sptr(name, std::shared_ptr<dependency>(dptr));
    }
    template<class T>
    void set(dependency* dptr) {
      set_sptr(std::string(typeid(T).name()), std::shared_ptr<dependency>(dptr));
    }
    template<class T>
    void set_sptr(std::shared_ptr<dependency> dep) {
      set_sptr(std::string(typeid(T).name()), dep);
    }

    template<class T>
    std::shared_ptr<T> get(std::string name) {
      return std::dynamic_pointer_cast<T>(get_dep(name));
    }
    template<typename T>
    std::shared_ptr<T> get() {
      return get<T>(std::string(typeid(T).name()));
    }
    std::shared_ptr<dependency> get_dep(std::string name);
  };

  typedef std::shared_ptr<particledi::dm> dm_ptr;
}

// todo: throw an exception if there's no such dependency
