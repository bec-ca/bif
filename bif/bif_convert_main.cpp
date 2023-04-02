#include "array.hpp"

#include "bif/debif.hpp"
#include "bif/string.hpp"

#include "bee/file_reader.hpp"
#include "bee/file_writer.hpp"
#include "command/command_builder.hpp"
#include "command/group_builder.hpp"

#include <memory>

using bee::print_line;
using command::Cmd;
using command::CommandBuilder;
using command::GroupBuilder;
using std::make_shared;
using std::string;
using std::vector;

namespace bif {
namespace {

bee::OrError<vector<string>> load_lines(const string& filename)
{
  bail(positions, bee::FileReader::open(bee::FilePath::of_string(filename)));
  return positions->read_all_lines();
}

bee::OrError<bee::Unit> lines_to_bif_main(
  const string& input_file, const string& output_file)
{
  print_line("Reading file '$'...", input_file);
  bail(lines, load_lines(input_file));

  print_line("Converting data...");
  auto bifer = make_shared<bif::Bifer>();
  auto [_, ar] = bif::allocate_obj<bif::Array<bif::String>>(bifer);

  ar.allocate(lines.size());
  for (const auto& s : lines) { ar.add() = s; }

  print_line("Writing file '$'...", output_file);
  bail_unit(bee::FileWriter::save_file(
    bee::FilePath::of_string(output_file), bifer->data()));

  return bee::ok();
}

Cmd lines_to_bif_cmd()
{
  using namespace command::flags;
  auto builder = CommandBuilder("Analyse positions");
  auto input_file = builder.required("--input-file", string_flag);
  auto output_file = builder.required("--output-file", string_flag);
  return builder.run(
    [=]() { return lines_to_bif_main(*input_file, *output_file); });
}

} // namespace
} // namespace bif

int main(int argc, char* argv[])
{
  return GroupBuilder("Bif converter")
    .cmd("lines-to-bif", bif::lines_to_bif_cmd())
    .build()
    .main(argc, argv);
}
