#ifndef HASHTAROTH_H
#define HASHTAROTH_H

#include <hashtaroth_types.h>

#ifdef _WIN32
  #ifdef HASHTAROTH_EXPORT
    #define HASHTAROTH_API __declspec(dllexport)
  #else
    #define HASHTAROTH_API __declspec(dllimport)
  #endif
#else
  #define HASHTAROTH_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    // Initialize library
    HASHTAROTH_API void initialize();
    HASHTAROTH_API void destroy();

    // submit file to hashing library
    HASHTAROTH_API hash_id_type submit_file(const char* file_path, const hashtaroth_callback callback);

#ifdef __cplusplus
};
#endif // __cplusplus


#endif // HASHTAROTH_H