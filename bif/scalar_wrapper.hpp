#pragma once

#include "data_range.hpp"

#include "bee/format.hpp"

namespace bif {

template <class T> struct scalar_codec;

template <> struct scalar_codec<char> {
  static char read(DataRange r) { return r.read_int8(); }
  static void write(DataRange r, char v) { r.write_int8(v); }
};

template <> struct scalar_codec<uint8_t> {
  static uint8_t read(DataRange r) { return r.read_uint8(); }
  static void write(DataRange r, uint8_t v) { r.write_uint8(v); }
};

template <> struct scalar_codec<int8_t> {
  static int8_t read(DataRange r) { return r.read_int8(); }
  static void write(DataRange r, int8_t v) { r.write_int8(v); }
};

template <> struct scalar_codec<uint16_t> {
  static uint16_t read(DataRange r) { return r.read_uint16(); }
  static void write(DataRange r, uint16_t v) { r.write_uint16(v); }
};

template <> struct scalar_codec<int16_t> {
  static int16_t read(DataRange r) { return r.read_int16(); }
  static void write(DataRange r, int16_t v) { r.write_int16(v); }
};

template <> struct scalar_codec<uint32_t> {
  static uint32_t read(DataRange r) { return r.read_uint32(); }
  static void write(DataRange r, uint32_t v) { r.write_uint32(v); }
};

template <> struct scalar_codec<int32_t> {
  static int32_t read(DataRange r) { return r.read_int32(); }
  static void write(DataRange r, int32_t v) { r.write_int32(v); }
};

template <> struct scalar_codec<uint64_t> {
  static uint64_t read(DataRange r) { return r.read_uint64(); }
  static void write(DataRange r, uint64_t v) { r.write_uint64(v); }
};

template <> struct scalar_codec<int64_t> {
  static int64_t read(DataRange r) { return r.read_int64(); }
  static void write(DataRange r, int64_t v) { r.write_int64(v); }
};

template <> struct scalar_codec<float> {
  static float read(DataRange r) { return r.read_float(); }
  static void write(DataRange r, float v) { r.write_float(v); }
};

template <> struct scalar_codec<double> {
  static double read(DataRange r) { return r.read_double(); }
  static void write(DataRange r, double v) { r.write_double(v); }
};

template <class T> struct ScalarWrapper {
 public:
  ScalarWrapper(DataRange data) : _data(data) {}

  T get() const { return scalar_codec<T>::read(_data); }
  void set(T v) { return scalar_codec<T>::write(_data, v); }

  ScalarWrapper& operator=(T v)
  {
    set(v);
    return *this;
  }

  T operator*() { return get(); }

  std::string to_string() const { return bee::format(get()); }

 private:
  DataRange _data;
};

} // namespace bif
