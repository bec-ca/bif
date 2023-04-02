#pragma once

#include "bifer.hpp"
#include "data_range.hpp"
#include "scalar_wrapper.hpp"
#include "size_of.hpp"

#include <cstdint>

namespace bif {

template <class T>
concept DebifableConcept = requires(const Bifer::ptr& bifer, DataRange range) {
                             {
                               T::debif(bifer, range)
                               } -> std::same_as<T>;
                           };

template <class T> struct debif_t;

template <DebifableConcept T> struct debif_t<T> {
  static T call(const Bifer::ptr& bifer, DataRange range)
  {
    return T::debif(bifer, range);
  }
};

template <std::integral T> struct debif_t<T> {
  using value_type = T;
  static auto call(const auto&, DataRange r)
  {
    return ScalarWrapper<value_type>(r);
  }
};

template <class T> auto debif(const Bifer::ptr& bifer, DataRange range)
{
  return debif_t<T>::call(bifer, range);
}

template <class T> auto debif(const Bifer::ptr& bifer)
{
  return debif_t<T>::call(bifer, DataRange(bifer, 0, size_of_v<T>));
}

template <class T> std::pair<int64_t, T> allocate_obj(const Bifer::ptr& bifer)
{
  auto loc = bifer->allocate(size_of_v<T>);
  return std::make_pair(
    loc, debif<T>(bifer, DataRange(bifer, loc, loc + size_of_v<T>)));
}

} // namespace bif
