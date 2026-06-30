#ifndef ISQL_API_HPP
#define ISQL_API_HPP

#include <string>

namespace beelzebase
{

  class MonitoredFSRecord;

  class ISQLApi
  {
  public:

    virtual ~ISQLApi() {};
    virtual bool init_db() = 0;
    virtual bool update_db() = 0;

    virtual bool add_monitored_entry(const MonitoredFSRecord&) = 0;
    virtual bool update_monitored_entry(const std::string&, const MonitoredFSRecord&) = 0;
    virtual bool delete_monitored_entry(const std::string&) = 0;
  };

} // namespace beelzebase

#endif // ISQL_API_HPP