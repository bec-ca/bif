#pragma once

#include <concepts>

namespace bif {

template <class T>
concept SizeOfConcept = requires {
                          {
                            T::size_of()
                            } -> std::same_as<int>;
                        };

template <class T> struct size_of;

template <SizeOfConcept T> struct size_of<T> {
  constexpr static int value() { return T::size_of(); }
};

template <std::integral T> struct size_of<T> {
  constexpr static int value() { return sizeof(T); }
};

template <class T> constexpr int size_of_v = size_of<T>::value();

} // namespace bif
