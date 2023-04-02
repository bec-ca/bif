#pragma once

#include "array.hpp"

namespace bif {

struct String : public Array<char> {
 public:
  String(Array<char>&& ar) : Array<char>(std::move(ar)) {}

  String& operator=(const std::string&);
  String& operator=(const char*);

  operator std::string() const;

  std::string to_string() const;

  static String debif(const Bifer::ptr& bifer, DataRange header);

 private:
};

} // namespace bif
