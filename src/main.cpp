#include <hashtaroth.hpp>
#include <daemonarch.hpp>
#include <beelzebase.hpp>

#include <sqlite/sqlite_api.hpp>

#include <memory>
#include <filesystem>
#include <cstdlib>

using namespace hashtaroth;
using namespace daemonarch;
using namespace beelzebase;

using namespace std;
using namespace std::filesystem;

int main(int argc, char **argv)
{
  int main_return_code{EXIT_SUCCESS};
  // Create deduplicon modules
  Hashtaroth hashtaroth;
  DaemonArch daemonarch;

  const path database_path{"/tmp/beelzebase/beelzebase.db"};
  unique_ptr<ISQLApi> sql_backend{make_unique<SqliteAPI>(database_path)};

  Beelzebase beelzebase(std::move(sql_backend));

  hashtaroth.start();
  daemonarch.start();

  return main_return_code;
}