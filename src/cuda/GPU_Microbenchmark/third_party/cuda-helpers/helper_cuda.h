#ifndef HELPER_CUDA_H
#define HELPER_CUDA_H
// Minimal helper_cuda replacement. Extend as needed.
#include <cstdio>
#include <cstdlib>

#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

inline void check_cuda(cudaError_t result, const char *func, const char *file, int line)
{
    if (result != cudaSuccess)
    {
        fprintf(stderr, "CUDA error at %s:%d code=%d(%s) \"%s\"\n",
                file, line, int(result), cudaGetErrorName(result), func);
        std::fflush(stderr);
        std::exit(EXIT_FAILURE);
    }
}

#endif // HELPER_CUDA_H
