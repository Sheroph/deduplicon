
#include <hash_extactor.hpp>

#include <openssl/sha.h>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>

using namespace std;
using namespace filesystem;

namespace hashtaroth
{

    hash_id_type Hashtaroth::current_hash_id_ = 0;

    std::unique_ptr<Hashtaroth> hashtaroth;

    Hashtaroth::Hashtaroth(const size_t nb_threads) : nb_threads_(nb_threads) {};


    hash_id_type Hashtaroth::hash_this(const path& file, const hashtaroth_callback& callback)
    {
        HashData hash_data{get_next_hash_id(), file, callback};
        hash_data.set_state(HASHTAROTH_INQUEUED);
        {
            unique_lock<mutex> lock(to_do_mut_);
            hashes_to_do_.push_back(hash_data);
        }
        return hash_data.get_hash_id();
    }

    hash_id_type Hashtaroth::get_next_hash_id()
    {
        return Hashtaroth::current_hash_id_++;
    }

    void Hashtaroth::get_next_job(HashData& hash_data)
    {
        unique_lock<mutex> lock(to_do_mut_);
        to_do_cond_.wait(lock, [&]() {return !hashes_to_do_.empty() || !running_;});
        if (!running_)
        {
            return;
        }
        hash_data = hashes_to_do_.front();
        hashes_to_do_.pop_front();
    }

    void Hashtaroth::hash_proc()
    {

        // OpenSSL context
        EVP_MD_CTX* openssl_ctx = EVP_MD_CTX_new();
        EVP_MD* msg_digest = EVP_MD_fetch(nullptr, "SHA256", nullptr);

        while(running_)
        {
            HashData hash_to_do;
            // Pop next job
            get_next_job(hash_to_do);

            const path& file = hash_to_do.get_file();
            if(!exists(file))
            {
                hash_to_do.set_state(HASHTAROTH_NOT_FOUND);
                hash_to_do(hash_to_do.get_hash_id(), HASHTAROTH_NOT_FOUND, hash_to_do.get_hash());
                continue;
            }
            hash_path(hash_to_do, openssl_ctx, msg_digest);
            hash_to_do(hash_to_do.get_hash_id(), HASHTAROTH_COMPUTED, hash_to_do.get_hash());
            EVP_MD_CTX_reset(openssl_ctx);
        }
        EVP_MD_CTX_free(openssl_ctx);
    }

    void Hashtaroth::hash_path(HashData& hash_data, EVP_MD_CTX* openssl_ctx, EVP_MD* msg_digest)
    {
        static constexpr size_t buffer_size{8192};
        static char buffer[buffer_size];

        std::ifstream file(hash_data.get_file().string(), std::ios::binary);
        if (!file)
        {
            hash_data.set_state(HASHTAROTH_NO_READ_ACCESS);
            return;
        }

        EVP_DigestInit_ex(openssl_ctx, msg_digest, nullptr);

        size_t bytes_read = 0;
        while (!file.eof())
        {
            bytes_read = file.readsome(buffer, buffer_size);
            if(bytes_read > 0)
            {
                EVP_DigestUpdate(openssl_ctx, buffer, bytes_read);
            }
        }
        EVP_DigestFinal_ex(openssl_ctx, hash_data.get_hash(), NULL);
    }
} // namespace hashtaroth



void initialize()
{
    hashtaroth::hashtaroth = make_unique<hashtaroth::Hashtaroth>();
}

void destroy()
{
    hashtaroth::hashtaroth.reset();
}

hash_id_type submit_file(const char* file_path, const hashtaroth_callback callback)
{
    const path file(file_path);
    return hashtaroth::hashtaroth->hash_this(file, callback);
}

// std::string sha256_file(const std::string& filename) {
//     unsigned char hash[EVP_MAX_MD_SIZE];
//     SHA256_CTX sha256;
//     SHA256_Init(&sha256);

//     std::ifstream file(filename, std::ios::binary);
//     if (!file) throw std::runtime_error("Unable to open file: " + filename);

//     char buffer[4096];
//     while (file.read(buffer, sizeof(buffer)))
//         SHA256_Update(&sha256, buffer, file.gcount());
//     if (file.gcount() > 0)
//         SHA256_Update(&sha256, buffer, file.gcount());

//     SHA256_Final(hash, &sha256);

//     std::ostringstream result;
//     for (int i = 0; i < EVP_MAX_MD_SIZE; ++i)
//         result << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//     return result.str();
// }

// int main() {
//     try {
//         std::string hash = sha256_file("fichier.txt");
//         std::cout << "SHA256: " << hash << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Erreur: " << e.what() << std::endl;
//     }
// }
