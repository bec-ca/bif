#include "bifer.hpp"

#include "data_range.hpp"

#include "bee/format.hpp"
#include "bee/testing.hpp"

#include <memory>

using bee::print_line;
using std::make_shared;

namespace bif {
namespace {

TEST(basic)
{
  auto bifer = make_shared<Bifer>();

  {
    auto loc = bifer->allocate(8);

    print_line(loc);

    DataRange r(bifer, loc, loc + 8);

    r.write_int32(1000000);
    r.write_int32(-1000);
  }

  print_line(bifer->size());

  {
    DataRange r(bifer, 0, 8);
    print_line(r.read_int32());
    print_line(r.read_int32());
  }
}

} // namespace
} // namespace bif
