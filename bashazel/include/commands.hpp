#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <vector>
#include <filesystem>

namespace bashazel
{
  std::string usage();

  void start();
  void stop();

  bool add_monitored_item(const std::filesystem::path&);
  bool remove_monitored_item(const std::filesystem::path&);

  std::vector<std::string> list_monitored_items();

  void report();
  void status();

} // namespace bashazel


#endif // COMMANDS_HPP