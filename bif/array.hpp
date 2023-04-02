#pragma once

#include "bif/data_range.hpp"
#include "bifer.hpp"
#include "debif.hpp"
#include "size_of.hpp"

#include "bee/copy.hpp"
#include "bee/ref.hpp"

#include <cassert>
#include <memory>

namespace bif {

template <class T> struct Array {
 public:
  struct iterator {
   public:
    iterator(Array& array, int64_t idx) : _array(array), _idx(idx) {}

    iterator& operator++() { _idx++; }

    T operator*() const { return _array->get(_idx); }

    auto operator<=>(const iterator& other) const
    {
      return _idx <=> other._idx;
    }

   private:
    bee::ref<Array> _array;
    int64_t _idx;
  };

  static constexpr int element_size = size_of_v<T>;

  static constexpr int size_of() { return 8 * 2; }

  auto get(int64_t idx) const
  {
    assert(_data.has_value() && idx >= 0 && idx < _size);
    int64_t pos = idx * element_size;
    auto range = _data->slice(pos, pos + element_size);
    return bif::debif<T>(_bifer, range);
  }

  auto at(int64_t idx) const { return get(idx); }

  auto operator[](int64_t idx) { return get(idx); }

  auto add()
  {
    assert(_used < _size);
    auto ret = get(_used);
    _used++;
    return ret;
  }

  template <class U> void set(int64_t idx, U value)
  {
    auto t = get(idx);
    t = value;
  }

  static Array debif(const Bifer::ptr& bifer, DataRange header)
  {
    auto h = bee::copy(header);
    auto loc = h.read_int64();
    auto size = h.read_int64();
    std::optional<DataRange> data;
    if (size > 0) { data.emplace(bifer, loc, loc + element_size * size); }
    return Array(bifer, header, data, size);
  }

  void allocate(int64_t size)
  {
    assert(!_data.has_value() && _size == 0 && size > 0);
    auto loc = _bifer->allocate(size * size_of_v<T>);
    _data.emplace(_bifer, loc, loc + size);
    _size = size;
    {
      auto h = bee::copy(_header);
      h.write_int64(loc);
      h.write_int64(size);
    }
  }

  iterator begin() { return iterator(*this, 0); }
  iterator end() { return iterator(*this, _used); }

  int64_t size() const { return _size; }

 private:
  Array(
    const Bifer::ptr& bifer,
    DataRange header,
    std::optional<DataRange> data,
    int64_t size)
      : _bifer(bifer), _header(header), _data(data), _size(size), _used(size)
  {}

  Bifer::ptr _bifer;

  DataRange _header;
  std::optional<DataRange> _data;

  int64_t _size;

  int64_t _used;
};

} // namespace bif
