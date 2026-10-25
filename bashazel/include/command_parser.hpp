#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <vector>
#include <string>

namespace bashazel
{

  enum command_type_t {
    START,
    STOP,
    QUIT,
    ADD_MONITORED_ITEM,
    UNKNOWN
  };

  struct command_t {
    command_type_t type;
    std::vector<std::string> parameters;
  };

  command_t parse_command(const std::string&);

} // namespace bashazel


#endif // COMMAND_PARSER_HPP