#pragma once

#include "size_of.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace bif {

struct Bifer {
 public:
  using ptr = std::shared_ptr<Bifer>;

  Bifer();
  Bifer(std::vector<std::byte>&& data);
  ~Bifer();

  int64_t allocate(int64_t size);

  const std::vector<std::byte>& data();

  int64_t size() const;

  void set(int64_t idx, std::byte);
  std::byte get(int64_t idx);

 private:
  std::vector<std::byte> _data;
};

} // namespace bif
