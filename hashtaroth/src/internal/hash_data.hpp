#ifndef HASHDATA_H
#define HASHDATA_H

#include <hashtaroth_types.h>

#include <openssl/evp.h>

#include <filesystem>

namespace hashtaroth
{
    class HashData
    {
    public:
        HashData();
        HashData(const hash_id_type&, const std::filesystem::path &, const hashtaroth_callback &);
        HashData &operator=(const HashData &);

        void reset_hash();

        unsigned char* get_hash();

        hash_id_type get_hash_id() const;
        void set_hash_id(const hash_id_type&);

        void set_callback(const hashtaroth_callback&);

        void set_state(const hashtaroth_hash_state&);

        std::filesystem::path get_file() const;
        void set_file(const std::filesystem::path&);

        void operator()(const hash_id_type&, const hashtaroth_hash_state&, unsigned char[EVP_MAX_MD_SIZE]);


    private:
        hash_id_type hash_id_;
        hashtaroth_hash_state state_;
        std::filesystem::path file_;
        unsigned char hash_[EVP_MAX_MD_SIZE];
        hashtaroth_callback callback_;
    };

} // namespace hashtaroth

#endif // HASHDATA_H