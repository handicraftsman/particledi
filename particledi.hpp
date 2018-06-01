#include <map>
#include <memory>

namespace particledi {
  class dependency {
  public:
    dependency();
    virtual ~dependency();
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
    std::shared_ptr<T> get(std::string name) {
      return std::dynamic_pointer_cast<T>(get_dep(name));
    }
    std::shared_ptr<dependency> get_dep(std::string name);
  };
}