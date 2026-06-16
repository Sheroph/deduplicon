#ifndef FILE_MODIFIER_HPP
#define FILE_MODIFIER_HPP

#include <future>
#include <filesystem>

namespace daemonarch::test::tools
{
  class FileModifier
  {
    public:
    FileModifier(const std::filesystem::path&);


    void write_bytes(const char* bytes, const size_t size, const std::ios::openmode mode = std::ios::trunc);
    void open_close(const std::ios::openmode mode = std::ios::app);
    void rename(const std::string&);
    bool remove();

    private:
      std::filesystem::path file_;
  };

} // namespace daemonarch::test::tools
#endif // FILE_MODIFIER_HPP