#pragma once
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace pac {

using std::vector;

class Packer {
 public:
  Packer() : buffer_(kDefaultBufferSize), length_(0), location_(2) {}
  ~Packer() {}

  void Reset() {
    buffer_.resize(kDefaultBufferSize);
    buffer_.shrink_to_fit();
    length_ = 0;
    location_ = 2;
  }

  void Swap(Packer& rhs) {
    rhs.buffer_.swap(buffer_);
    std::swap(rhs.length_, length_);
    std::swap(rhs.location_, location_);
  }

  Packer& Pack() {
    length_ = location_;
    location_ = 0;
    this->Push(length_);
    location_ = length_;
    return *this;
  }

  size_t Length() const { return length_; }

  std::string Body() const { return std::string(&buffer_[0] + 2, length_ - 2); }

  const char* Buffer() const { return &buffer_[0]; }

  void CheckSize(size_t byte_needed, uint16_t cur_size) {
    if (buffer_.size() - cur_size < byte_needed) {
      size_t new_size = buffer_.size() * 4;
      if (new_size - cur_size < byte_needed) {
        new_size = cur_size + byte_needed;
      }
      if (new_size > kMaxBufferSize) {
        throw std::overflow_error("Meet Packer Limit");
      }
      buffer_.resize(new_size);
    }
  }

  template<typename T>
  void Push(T&& num) {
    CheckeSize(sizeof(num), location_);
    memcpy(&buffer_[0] + location_, &num, sizeof(num));
    location_ += sizeof(num);
  }


  void Push(uint16_t num) {
    CheckSize(sizeof(num), location_);
    memcpy(&buffer_[0] + location_, &num, sizeof(num));
    location_ += sizeof(num);
  }

 private:
  static const size_t kDefaultBufferSize = 1024;
  static const size_t kMaxBufferSize = 8 * kDefaultBufferSize;
  vector<char> buffer_;
  uint16_t length_;
  uint16_t location_;
};

}  // namespace pac

