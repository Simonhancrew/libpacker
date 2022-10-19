#pragma once

#include <cinttypes>
#include <cstring>
#include <stdexcept>

namespace pac {

class Unpacker {
 public:
  Unpacker(const char* data, size_t len, bool copy)
      : buffer_(nullptr), length_(len) {
    buffer_ = const_cast<char*>(data);
  }

  ~Unpacker();

  Unpacker& Rewind() {
    location_ = 2;
    return *this;
  }

  void Reset() { location_ = 0; }

  void CheckSize(size_t byte, uint16_t location) {
    if (static_cast<size_t>(length_ - location) < byte) {
      throw std::overflow_error("Upacker size beyond limit");
    }
  }

  uint16_t PopUint16() {
    uint16_t res = 0;
    CheckSize(sizeof res, location_);
    memcpy(&res, buffer_ + location_, sizeof res);
    location_ += sizeof res;
    return res;
  }

 private:
  char* buffer_;
  uint16_t length_;
  uint16_t location_ = 0;
};

}  // namespace pac
