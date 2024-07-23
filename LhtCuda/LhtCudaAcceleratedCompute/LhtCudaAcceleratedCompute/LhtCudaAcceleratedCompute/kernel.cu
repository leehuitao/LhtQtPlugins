
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>


//结果检查
void checkResult(float* hostRef, float* gpuRef, double epsilon, const int N)  // 检查结果 epsilon 允许误差范围
{
    bool match = 1;  // 定义匹配标志
    for (int i = 0; i < N; i++)  // 比较每个元素
    {
        if (abs(hostRef[i] - gpuRef[i]) > epsilon)  // 如果误差超过范围
        {
            match = 0;  // 匹配标志置0
            printf("Arrays do not match!\n");  // 打印提示信息
            printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i], gpuRef[i], i);  // 打印不匹配的元素
            break;
        }
    }
    if (match) printf("Arrays match.\n\n");  // 如果匹配，打印提示信息
}


int main()
{
    const int arraySize = 5;
    const int a[arraySize] = { 1, 2, 3, 4, 5 };
    const int b[arraySize] = { 10, 20, 30, 40, 50 };
    int c[arraySize] = { 0 };

    // Add vectors in parallel.
    cudaError_t cudaStatus; //= addWithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4]);

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}

