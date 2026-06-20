#ifndef SQLITE_API_HPP
#define SQLITE_API_HPP

namespace beelzebase
{
  class SqliteAPI
  {
  public:
    SqliteAPI();
    ~SqliteAPI();

    bool init_db();

  protected:
    bool update_db();
  };

} // namespace beelzebase
#endif // SQLITE_API_HPP