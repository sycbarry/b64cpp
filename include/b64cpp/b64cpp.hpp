#pragma once

#include <cstddef>
#include <string>

namespace b64cpp {

class B64CPP {

public:
  B64CPP();
  B64CPP(B64CPP &&) = default;
  B64CPP(const B64CPP &) = default;
  B64CPP &operator=(B64CPP &&) = default;
  B64CPP &operator=(const B64CPP &) = default;
  void encode(const char *data);
  ~B64CPP();

private:
  int findSizeOfData(const char *data);
  std::vector<int> catoAscii(const char *data, size_t size);
  std::string asciiToBitStream(std::vector<int> ascii);
  std::vector<std::string> chunkBSTo6Bits(const std::string &bitstream);
  std::vector<int> chunksToBase10(const std::vector<std::string> chunks);
}; // namespace b64cpp

} // namespace b64cpp
