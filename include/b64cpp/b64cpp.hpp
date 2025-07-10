#pragma once

namespace b64cpp {

class B64CPP {

public:
  B64CPP();
  B64CPP(B64CPP &&) = default;
  B64CPP(const B64CPP &) = default;
  B64CPP &operator=(B64CPP &&) = default;
  B64CPP &operator=(const B64CPP &) = default;
  void do_something();
  ~B64CPP();

private:
};

} // namespace b64cpp
