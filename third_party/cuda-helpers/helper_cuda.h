#pragma once

#include <cuda_runtime.h>

// Minimal helper_cuda.h providing '_ConvertSMVer2Cores' for deviceQuery fallback builds.
inline int _ConvertSMVer2Cores(int major, int minor) {
    struct SmsPerArch {
        int sm;  // Encoded as (major << 4) + minor to mirror CUDA helper utility.
        int cores;
    };
    static constexpr SmsPerArch table[] = {
        {0x30, 192}, {0x32, 192}, {0x35, 192}, {0x37, 192},
        {0x50, 128}, {0x52, 128}, {0x53, 128},
        {0x60, 64},  {0x61, 128}, {0x62, 128},
        {0x70, 64},  {0x72, 64},  {0x75, 64},
        {0x80, 64},  {0x86, 128}, {0x87, 128},
        {0x89, 128}, {0x90, 128},
        {-1, 64},    // Fallback for unknown architectures.
    };

    const int search_key = (major << 4) + minor;
    for (const auto &entry : table) {
        if (entry.sm == search_key) {
            return entry.cores;
        }
        if (entry.sm == -1) {
            break;
        }
    }
    return table[sizeof(table) / sizeof(table[0]) - 1].cores;
}
