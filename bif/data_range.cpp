#include "data_range.hpp"

#include <cassert>
#include <cstddef>

namespace bif {

namespace {

void write_bytes(const uint8_t* data, int size, DataRange& range)
{
  for (int i = 0; i < size; i++) { range.write_uint8(data[i]); }
}

void read_bytes(uint8_t* data, int size, DataRange& range)
{
  for (int i = 0; i < size; i++) { data[i] = range.read_uint8(); }
}

} // namespace

////////////////////////////////////////////////////////////////////////////////
// DataRange
//

DataRange::DataRange(const Bifer::ptr& bifer, int64_t begin, int64_t end)
    : _bifer(bifer), _begin(begin), _end(end)
{
  assert(_begin >= 0 && _end >= _begin && _end <= _bifer->size());
}

void DataRange::write_uint8(uint8_t v)
{
  assert(_begin < _end);
  _bifer->set(_begin, std::byte(v));
  ++_begin;
}

uint8_t DataRange::read_uint8()
{
  assert(_begin < _end);
  auto ret = _bifer->get(_begin);
  _begin++;
  return std::to_integer<uint8_t>(ret);
}

void DataRange::write_int8(int8_t v) { write_uint8(v); }
int8_t DataRange::read_int8() { return read_uint8(); }

void DataRange::write_uint16(uint16_t v)
{
  write_uint8(v & 0xff);
  write_uint8((v >> 8));
}

uint16_t DataRange::read_uint16()
{
  uint16_t l = read_uint8();
  uint16_t h = read_uint8();
  return l | (h << 8);
}

void DataRange::write_int16(int16_t v) { write_uint16(v); }
int16_t DataRange::read_int16() { return read_uint16(); }

void DataRange::write_uint32(uint32_t v)
{
  write_uint16(v & 0xffff);
  write_uint16((v >> 16));
}

uint32_t DataRange::read_uint32()
{
  uint32_t l = read_uint16();
  uint32_t h = read_uint16();
  return l | (h << 16);
}

void DataRange::write_int32(int32_t v) { write_uint32(v); }
int32_t DataRange::read_int32() { return read_uint32(); }

void DataRange::write_uint64(uint64_t v)
{
  write_uint32(v & 0xffffffff);
  write_uint32((v >> 32));
}

uint64_t DataRange::read_uint64()
{
  uint64_t l = read_uint32();
  uint64_t h = read_uint32();
  return l | (h << 32);
}

void DataRange::write_int64(int64_t v) { write_uint64(v); }
int64_t DataRange::read_int64() { return read_uint64(); }

void DataRange::write_float(float v)
{
  write_bytes((const uint8_t*)&v, 4, *this);
}

float DataRange::read_float()
{
  float output;
  read_bytes((uint8_t*)&output, 4, *this);
  return output;
}

void DataRange::write_double(double v)
{
  write_bytes((const uint8_t*)&v, 8, *this);
}

double DataRange::read_double()
{
  double output;
  read_bytes((uint8_t*)&output, 8, *this);
  return output;
}

DataRange DataRange::slice(int64_t begin) const
{
  return DataRange(_bifer, _begin + begin, _end);
}

DataRange DataRange::slice(int64_t begin, int64_t end) const
{
  return DataRange(_bifer, _begin + begin, _begin + end);
}

} // namespace bif
