#pragma once

#include <memory>

template <size_t N>
struct ProgramData {
    size_t size{N};
    struct {
        float num1[N]{};
        float num2[N]{};
    } inputs;
    struct {
        float sum[N]{};
        float diff[N]{};
        float prod[N]{};
        float ratio[N]{};
    } outputs;
};


