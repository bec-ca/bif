#include "string.hpp"

#include "bee/testing.hpp"

using bee::print_line;
using std::make_shared;

namespace bif {
namespace {

TEST(basic)
{
  auto bifer = make_shared<Bifer>();
  auto [_, str] = allocate_obj<String>(bifer);

  str = "hello";
  print_line(str);
  print_line("bifer size: $", bifer->size());
}

TEST(array_string)
{
  auto bifer = make_shared<Bifer>();
  auto [_, ar] = allocate_obj<Array<String>>(bifer);

  ar.allocate(2);
  ar[0] = "foobar";
  ar[1] = "yo";

  for (int i = 0; i < 2; i++) { print_line(ar[i]); }

  print_line("bifer size: $", bifer->size());
}

} // namespace
} // namespace bif
