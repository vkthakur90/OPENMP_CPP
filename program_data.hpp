#pragma once

#include <memory>

#define SIMD_SIZE 512

template <size_t N>
struct ProgramData {
    size_t size{N};
    struct {
        alignas(SIMD_SIZE/alignof(float)) float num1[N]{};
        alignas(SIMD_SIZE/alignof(float)) float num2[N]{};
    } inputs;
    struct {
        alignas(SIMD_SIZE/alignof(float)) float sum[N]{};
        alignas(SIMD_SIZE/alignof(float)) float diff[N]{};
        alignas(SIMD_SIZE/alignof(float)) float prod[N]{};
        alignas(SIMD_SIZE/alignof(float)) float ratio[N]{};
    } outputs;
};


