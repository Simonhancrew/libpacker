#pragma once

// A macro to disallow the move constructor, same as above
#define DISALLOW_MOVE_AND_ASSIGN(ClassName)         \
  ClassName(const ClassName&&)            = delete; \
  ClassName& operator=(const ClassName&&) = delete

namespace pac {

class NonCopyable {
 public:
  NonCopyable(const NonCopyable&)    = delete;
  void operator=(const NonCopyable&) = delete;
};

}  // namespace pac
