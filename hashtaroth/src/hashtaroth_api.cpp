#include <hashtaroth_api.h>
#include <hashtaroth.hpp>

#include <memory>

using namespace std;
using namespace filesystem;

static unique_ptr<hashtaroth::Hashtaroth> hashtaroth_;

void initialize()
{
    hashtaroth_ = make_unique<hashtaroth::Hashtaroth>();
}

void destroy()
{
    hashtaroth_.reset();
}

hash_id_type submit_file(const char* file_path, const hashtaroth_callback callback)
{
    const path file(file_path);
    return hashtaroth_->hash_this(file, callback);
}
