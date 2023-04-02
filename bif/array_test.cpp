#include "array.hpp"

#include "bee/copy.hpp"
#include "bee/format.hpp"
#include "bee/testing.hpp"
#include "bif/bifer.hpp"
#include "bif/debif.hpp"

using bee::print_line;
using std::make_shared;

namespace bif {
namespace {

TEST(basic)
{
  auto bifer = make_shared<Bifer>();
  auto [loc, array] = allocate_obj<Array<int>>(bifer);
  print_line(loc);
  print_line(array.size());

  array.allocate(20);

  print_line(array.size());

  array.set(0, 5);
  array[1] = 8;

  print_line(array[0]);
  print_line(array[1]);
}

TEST(decode)
{
  auto bifer = make_shared<Bifer>();
  {
    auto [loc, array] = allocate_obj<Array<int>>(bifer);
    array.allocate(20);
    for (int i = 0; i < 20; i++) { array[i] = i * i; }
  }

  auto bifer2 = make_shared<Bifer>(bee::copy(bifer->data()));
  {
    auto array = debif<Array<int>>(bifer2);
    for (int i = 0; i < array.size(); i++) { print_line(array[i]); }
  }
}

} // namespace
} // namespace bif
