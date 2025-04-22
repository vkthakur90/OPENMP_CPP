#pragma once 

#include "program_data.hpp"
#include <cstdio>

template <size_t N>
void ProgramData_init(std::unique_ptr<ProgramData<N>> & data_ptr){
    #pragma parallel omp for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        data_ptr->inputs.num1[idx] = static_cast<float>(3 * (idx + 1));
        data_ptr->inputs.num2[idx] = static_cast<float>(1 * (idx + 1));
    }
}

template <size_t N>
void ProgramData_compute(std::unique_ptr<ProgramData<N>> & data_ptr){
    float a, b;
    
    #pragma parallel omp for simd schedule(static)
    for(size_t idx = 0; idx < data_ptr->size; ++idx){
        a = data_ptr->inputs.num1[idx];
        b = data_ptr->inputs.num2[idx];
        
        data_ptr->outputs.sum[idx] = a + b;
        data_ptr->outputs.diff[idx] = a - b;
        data_ptr->outputs.prod[idx] = a * b;
        data_ptr->outputs.ratio[idx] = (b != 0) ? a/b : 0;
    }
}

template <size_t N>
void ProgramData_display(std::unique_ptr<ProgramData<N>> & data_ptr){
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
void ProgramData_exec(std::unique_ptr<ProgramData<N>> & data_ptr){
    ProgramData_init(data_ptr);
    ProgramData_compute(data_ptr);
    ProgramData_display(data_ptr);
}