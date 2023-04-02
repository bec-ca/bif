#pragma once

#include "bifer.hpp"

#include <cstdint>
#include <vector>

namespace bif {

struct DataRange {
 public:
  DataRange(const Bifer::ptr& biffer, int64_t begin, int64_t end);

  DataRange(const DataRange& other) = default;

  void write_uint8(uint8_t);
  uint8_t read_uint8();

  void write_int8(int8_t);
  int8_t read_int8();

  void write_uint16(uint16_t);
  uint16_t read_uint16();

  void write_int16(int16_t);
  int16_t read_int16();

  void write_uint32(uint32_t);
  uint32_t read_uint32();

  void write_int32(int32_t);
  int32_t read_int32();

  void write_uint64(uint64_t);
  uint64_t read_uint64();

  void write_int64(int64_t);
  int64_t read_int64();

  void write_float(float);
  float read_float();

  void write_double(double);
  double read_double();

  DataRange slice(int64_t begin) const;
  DataRange slice(int64_t begin, int64_t end) const;

 private:
  Bifer::ptr _bifer;

  int64_t _begin;
  int64_t _end;
};

} // namespace bif
