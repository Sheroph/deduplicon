#include <beelzebase.hpp>

#include <memory>

using namespace std;

namespace beelzebase
{
  Beelzebase::Beelzebase(unique_ptr<ISQLApi>& api) : sql_api_(std::move(api)) {
    sql_api_->init_db();
  }

  Beelzebase::~Beelzebase() {}

} // namespace beelzebase
