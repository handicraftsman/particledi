#include <map>
#include <memory>

class particledi {
public:
  class dependency {
  public:
    dependency();
    virtual ~dependency();
  };

  std::map<std::string, std::shared_ptr<dependency>> deps;

  void set_sptr(std::string name, std::shared_ptr<dependency> dep);
  inline void set(std::string name, dependency* dptr) {
    set_sptr(name, std::shared_ptr<dependency>(dptr));
  }

  template<class T>
  std::shared_ptr<T> get(std::string name) {
    return std::dynamic_pointer_cast<T>(get_dep(name));
  }
  std::shared_ptr<dependency> get_dep(std::string name);
};
