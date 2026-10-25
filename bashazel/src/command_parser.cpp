#include <command_parser.hpp>

#include <string>
#include <map>
#include <functional>

using namespace std;

namespace bashazel
{

  using command_map_t = map<string, command_type_t>;
  using parser_t = function<void(const string&, command_t&)>;
  using command_parser_map_t = map<command_type_t, parser_t>;

  static const command_map_t string2command {
    {"start", START},
    {"stop", STOP},
    {"add_monitored_item", ADD_MONITORED_ITEM},
    {"quit", QUIT}
  };

  const parser_t command_forward{[](const string&, command_t&) {}};

  const void parse_single_param_command(const string& command_line, command_t& command) {

    const size_t parameter_idx = command_line.find(' ');
    if(parameter_idx != string::npos){
      command.parameters.push_back(command_line.substr(parameter_idx + 1));
    }
    else {
      command.type = UNKNOWN;
      command.parameters.clear();
    }

  }

  static const command_parser_map_t parsers{
    {START, command_forward},
    {STOP, command_forward},
    {ADD_MONITORED_ITEM, parse_single_param_command},
    {QUIT, command_forward}
  };

  command_t parse_command(const string& command_line) {

    bool command_found{false};
    command_t output;
    output.type = command_type_t::UNKNOWN;

    command_map_t::const_iterator command_name{string2command.cbegin()};
    command_map_t::const_iterator end{string2command.cend()};
    while(!command_found && command_name != end) {

      const size_t count{command_name->first.size()};

      if(!command_line.compare(0, count, command_name->first)) {
        command_found = true;
        output.type = command_name->second;
        parsers.at(output.type)(command_line, output);
        continue;
      }
      ++command_name;
    }
    return output;
  }

} // namespace bashazel
