#ifndef BEELZEBASE_HPP
#define BEELZEBASE_HPP

#include <isql_api.hpp>

#include <memory>

namespace beelzebase
{
  class Beelzebase
  {
    public:
      Beelzebase(std::unique_ptr<ISQLApi>&);
      ~Beelzebase();

    private:
      std::unique_ptr<ISQLApi> sql_api_;
  };

} // namespace beelzebase
#endif // BEELZEBASE_HPP