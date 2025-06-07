#ifndef HASH_EXTRACTOR_HPP
#define HASH_EXTRACTOR_HPP

#include <hashtaroth.h>
#include <hash_data.hpp>

#include <list>
#include <map>
#include <thread>
#include <filesystem>
#include <condition_variable>
#include <mutex>

namespace hashtaroth
{
    class Hashtaroth
    {
    public:
        Hashtaroth(const size_t nb_threads = 0);
        hash_id_type hash_this(const std::filesystem::path& file, const hashtaroth_callback& callback);


    private:
        static hash_id_type get_next_hash_id();


    private:

        void get_next_job(HashData&);

        void hash_proc();

        void hash_path(HashData& hash_data, EVP_MD_CTX* openssl_ctx, EVP_MD* msg_digest);


        size_t nb_threads_;
        std::list<std::thread> threads_;

        std::list<HashData> hashes_to_do_;

        std::condition_variable to_do_cond_;
        std::mutex to_do_mut_;

        std::atomic_bool running_;

        static hash_id_type current_hash_id_;

    };
} // namespace hashtaroth

#endif HASH_EXTRACTOR_HPP
