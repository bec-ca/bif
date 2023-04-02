#include "bifer.hpp"

#include <cassert>
#include <cstdint>

namespace bif {

////////////////////////////////////////////////////////////////////////////////
// Bifer
//

Bifer::Bifer() {}
Bifer::Bifer(std::vector<std::byte>&& data) : _data(std::move(data)) {}
Bifer::~Bifer() {}

int64_t Bifer::allocate(int64_t size)
{
  int64_t loc = _data.size();
  _data.resize(_data.size() + size, std::byte(0));
  return loc;
}

const std::vector<std::byte>& Bifer::data() { return _data; }

int64_t Bifer::size() const { return _data.size(); }

void Bifer::set(int64_t idx, std::byte v) { _data.at(idx) = v; }
std::byte Bifer::get(int64_t idx) { return _data.at(idx); }

} // namespace bif
