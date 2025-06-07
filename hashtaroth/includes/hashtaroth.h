#ifndef HASHTAROTH_H
#define HASHTAROTH_H

#include <openssl/evp.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    enum hashtaroth_hash_state {
        HASHTAROTH_NO_READ_ACCESS,
        HASHTAROTH_NOT_FOUND,
        HASHTAROTH_INQUEUED,
        HASHTAROTH_COMPUTING,
        HASHTAROTH_COMPUTED,
        HASHTAROTH_CREATED
    };

    typedef int32_t hash_id_type;
    typedef void (*hashtaroth_callback)(const hash_id_type, const hashtaroth_hash_state, const unsigned char[EVP_MAX_MD_SIZE]);

    // Initialize library
    void initialize();
    void destroy();

    // submit file to hashing library
    hash_id_type submit_file(const char* file_path, const hashtaroth_callback callback);

#ifdef __cplusplus
};
#endif // __cplusplus


#endif // HASHTAROTH_H