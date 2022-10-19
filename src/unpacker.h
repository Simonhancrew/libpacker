#pragma once


#include <cinttypes>

namespace pac {

class Unpacker {
 public:
 private:
  char* buffer_;
  uint16_t length_;
  uint16_t location_;
};

}  // namespace pac
