/*
 * Sebastian Barry 2025
 *
 * We take in character data and convert that to ASCII numbers.
 * Convert the ASCII into a binary stream.
 * Take the binary stream and split it up by 6 bits at a time.
 * Convert the 6 bit sequences from base-2 to base-10 decimal values
 *    (starting from the right -> left).
 * Convert those 6 bit base-10 values back to ASCII using the conversion table.
 *
 */

#include "b64cpp/b64cpp.hpp"
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

struct TranslationMap {
  std::unordered_map<int, char> valueToChar;
  TranslationMap() {
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz"
                        "0123456789+/";
    for (int i = 0; i < chars.size(); i++) {
      valueToChar[i] = chars[i];
    }
  }
};

namespace b64cpp {

B64CPP::B64CPP() {}

void B64CPP::encode(const char *data) {
  int lengthOfString = this->findSizeOfData(data);
  if (lengthOfString > 0) {
    // find the binary ecoding of this data.
    std::vector<int> ascii = this->catoAscii(data, lengthOfString);
    std::string bs = this->asciiToBitStream(ascii);
    // std::cout << bs << std::endl;
    std::vector<std::string> chunks = this->chunkBSTo6Bits(bs);
    std::vector<int> basetenchunks = this->chunksToBase10(chunks);

    TranslationMap m;
    for (int v : basetenchunks) {
      printf("%c", m.valueToChar[v]);
    }
    printf("\n");
  }
}

/*
 * Takes a vector of chunks
 * and converts them to a base 10 number
 * starting from the right and moving to the left, we square the 6 - n'th index
 * and add that to the sum if the bit we are squaring is a 1.
 * IOW, the power we are squaring by increases as we move from the right to the
 * left.
 *
 */
std::vector<int> B64CPP::chunksToBase10(const std::vector<std::string> chunks) {
  std::vector<int> base10Chunks;
  for (int i = 0; i < chunks.size(); ++i) {
    // find the length of the chunk (always 6)
    int right = chunks[i].size() - 1;
    int l = right;
    std::string chunk = chunks[i];
    int total = 0;
    while (right >= 0) {
      if (chunk[right] == '1') {
        double squaredValue = pow(2.0, l - right);
        total += static_cast<int>(squaredValue);
      }
      --right;
    }
    base10Chunks.push_back(total);
  }
  return base10Chunks;
}

/*
 * chunk the 8 bit bit stream to a bit stream of 6 bits
 */
std::vector<std::string> B64CPP::chunkBSTo6Bits(const std::string &bitstream) {
  std::vector<std::string> chunks;
  for (size_t i = 0; i < bitstream.size(); i += 6) {
    std::string chunk = bitstream.substr(i, 6);
    if (chunk.size() < 6) {
      chunk.append(6 - chunk.size(),
                   '0'); // pad the difference b/w the last chunk and 6 with 0s
    }
    chunks.push_back(chunk);
  }
  return chunks;
}

/*
 * convert a ascii vector to a bitstream of 8 bits
 */
std::string B64CPP::asciiToBitStream(std::vector<int> ascii) {
  std::string bitStream;
  for (int val : ascii) {
    std::bitset<8> bits(static_cast<unsigned char>(val));
    bitStream += bits.to_string();
  }
  return bitStream;
}

/*
 * convert a char array to an ascii vector
 */
std::vector<int> B64CPP::catoAscii(const char *data, size_t size) {
  std::vector<int> asciivalues;
  if (!data)
    return asciivalues;
  for (size_t i = 0; i < size; i++) {
    asciivalues.push_back(static_cast<unsigned char>(data[i]));
  }
  return asciivalues;
}

int B64CPP::findSizeOfData(const char *data) {
  size_t length = strlen(data);
  printf("length of value %zu\n", length);
  return length;
}

B64CPP::~B64CPP() {}

} // namespace b64cpp
