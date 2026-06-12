#include <file_modifier.hpp>
#include <fstream>

using namespace std;
using namespace std::filesystem;

namespace daemonarch::test::tools
{
  FileModifier::FileModifier(const path &file) : file_(file) {}

  void FileModifier::write_bytes(const char *bytes, const size_t size, const ios::openmode mode) {
    ofstream stream(file_, mode);
    stream.write(bytes, size);
    stream.close();
  }

  void FileModifier::open_close(const ios::openmode mode) {
    ofstream stream(file_, mode);
    stream.close();
  }



} // namespace daemonarch::test::tools