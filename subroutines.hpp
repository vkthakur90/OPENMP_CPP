#pragma once 

#include "program_data.hpp"
#include <cstdio>

template <size_t N>
void ProgramData_init(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        data_ptr->inputs.num1[idx] = static_cast<float>(3 * (idx + 1));
        data_ptr->inputs.num2[idx] = static_cast<float>(1 * (idx + 1));
    }
}

template <size_t N> 
void ProgramData_computeSum(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & a = data_ptr->inputs.num1[idx];
        auto & b = data_ptr->inputs.num2[idx];
        
        data_ptr->outputs.sum[idx] = a + b;
    }
}

template <size_t N> 
void ProgramData_computeDifference(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & a = data_ptr->inputs.num1[idx];
        auto & b = data_ptr->inputs.num2[idx];
        
        data_ptr->outputs.diff[idx] = a - b;
    }
}

template <size_t N> 
void ProgramData_computeProduct(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & a = data_ptr->inputs.num1[idx];
        auto & b = data_ptr->inputs.num2[idx];
        
        data_ptr->outputs.prod[idx] = a * b;
    }
}

template <size_t N> 
void ProgramData_computeRatio(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    #pragma omp parallel for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        auto & a = data_ptr->inputs.num1[idx];
        auto & b = data_ptr->inputs.num2[idx];
        
        data_ptr->outputs.ratio[idx] = (b != 0.0f) ? a/b : 0;
    }
}

template <size_t N>
void ProgramData_compute(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    ProgramData_computeSum(data_ptr);
    ProgramData_computeDifference(data_ptr);
    ProgramData_computeProduct(data_ptr);
    ProgramData_computeRatio(data_ptr);
}

template <size_t N>
void ProgramData_display(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    size_t size = (data_ptr->size > 50) ? 50 : data_ptr->size;
    for(size_t idx = 0; idx < size; ++idx){
        std::printf(
            "%0.2f\t%0.2f\t\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n",
            data_ptr->inputs.num1[idx], 
            data_ptr->inputs.num2[idx], 
            data_ptr->outputs.sum[idx], 
            data_ptr->outputs.diff[idx], 
            data_ptr->outputs.prod[idx], 
            data_ptr->outputs.ratio[idx]
        );
    }    
}

template <size_t N>
void ProgramData_exec(std::unique_ptr<ProgramData<N>> & data_ptr) noexcept {
    if(data_ptr == nullptr) {
        return;    
    }
    
    ProgramData_init(data_ptr);
    ProgramData_compute(data_ptr);
    ProgramData_display(data_ptr);
}