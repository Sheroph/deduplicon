
#include <hash_data.hpp>

using namespace std;
using namespace std::filesystem;

namespace hashtaroth
{

    HashData::HashData()
    {
        hash_id_ = -1;
        state_ = hashtaroth_hash_state::HASHTAROTH_CREATED;
        memset(hash_, 0, EVP_MAX_MD_SIZE);
        callback_ = [](const hash_id_type, const hashtaroth_hash_state, const unsigned char[EVP_MAX_MD_SIZE]) {throw exception("HashData: Callback not set !");};
    }

    HashData::HashData(const hash_id_type& id, const path &file_to_hash, const hashtaroth_callback &input_callback) : hash_id_{id}, file_{file_to_hash}, callback_{input_callback}
    {
        state_ = hashtaroth_hash_state::HASHTAROTH_CREATED;
        memset(hash_, 0, EVP_MAX_MD_SIZE);
    }

    HashData &HashData::operator=(const HashData &hashdata)
    {
        hash_id_ = hashdata.hash_id_;
        state_ = hashdata.state_;
        callback_ = hashdata.callback_;
        memcpy(hash_, hashdata.hash_, EVP_MAX_MD_SIZE);
        file_ = hashdata.file_;
        return *this;
    }

    hash_id_type HashData::get_hash_id() const
    {
        return hash_id_;
    }

    void HashData::set_hash_id(const hash_id_type& hash_id)
    {
        hash_id_ = hash_id;
    }

    void HashData::set_callback(const hashtaroth_callback& callback)
    {
        callback_ = callback;
    }

    void HashData::reset_hash()
    {
        memset(hash_, 0, EVP_MAX_MD_SIZE);
    }

    void HashData::set_state(const hashtaroth_hash_state& state)
    {
        state_ = state;
    }

    path HashData::get_file() const
    {
        return file_;
    }

    void HashData::set_file(const path& file)
    {
        file_ = file;
    }

    void HashData::operator()(const hash_id_type& hash_id, const hashtaroth_hash_state& state, unsigned char hash[EVP_MAX_MD_SIZE])
    {
        callback_(hash_id, state, hash);
    }

    unsigned char* HashData::get_hash()
    {
        return hash_;
    }

} // namespace hashtaroth
