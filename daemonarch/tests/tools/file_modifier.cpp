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

  bool FileModifier::remove() {
    const bool remove_status{filesystem::remove(file_)};
    if(remove_status)
    {
      file_ = "";
    }
    return remove_status;
  }

  void FileModifier::rename(const string& new_name) {
    const path root{file_.parent_path()};
    const path new_path{root / new_name};
    filesystem::rename(file_, new_path);
    file_ = new_path;
  }


} // namespace daemonarch::test::tools