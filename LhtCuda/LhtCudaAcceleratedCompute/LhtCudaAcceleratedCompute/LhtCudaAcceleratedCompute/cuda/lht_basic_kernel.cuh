#pragma once
/*
//              leehuitao cuda basic algorithm library
//              create:2024/7/23
//              基础函数库；错误检查 、结果比较等
//
*/
#include <cuda_runtime.h>
#include <cufft.h>
#include <iostream>

//错误检查
#define CUDA_CHECK(call)                                                   \
  {                                                                        \
    const cudaError_t error = call;                                        \
    if (error != cudaSuccess) {                                            \
      printf("Error: %s:%d, ", __FILE__, __LINE__);                        \
      printf("code: %d, reasone: %s\n", error, cudaGetErrorString(error)); \
      return false;                                                        \
    }                                                                      \
  }

//将GPU数据拷贝到Cpu   
void LhtCopy2Host(float* in1, float* out, int len);

//点加
__global__ void lhtAdd(float* in1 , float* int2, float* out,int len);

//点减
__global__ void lhtSub(float* in1, float* int2, float* out, int len);

//点乘
__global__ void lhtMulc(float* in1, float* int2, float* out, int len);

//乘系数
__global__ void lhtMulc(float* in1, float int2, float* out, int len);

//复数乘
__global__ void lhtMulc(cufftComplex* in1, cufftComplex* int2, cufftComplex* out, int len);

//排序
__global__ void lhtSort(float* in1,  float* out, int len);

//向量和
__global__ void lhtSum(float* in1, float* out, int len);
//向量绝对值的和
__global__ void lhtAbsSum(float* in1, float* out, int len);

//向量均值
__global__ void lhtMean(float* in1, float* out, int len);

//向量绝对值均值
__global__ void lhtAbsMean(float* in1, float* out, int len);

//向量最大值
__global__ void lhtMax(float* in1, float* out, int len);

//向量最小值
__global__ void lhtMin(float* in1, float* out, int len);

//运行时间打印 示例
//{
//float time;
//cudaEvent_t start, stop;
//
//...
//
////创建Event
//cudaEventCreate(&start);
//cudaEventCreate(&stop);
////记录当前时间
//cudaEventRecord(start, 0);
//
//...//需要计时的那一部分
//
////记录当前时间
//cudaEventRecord(stop, 0);
//cudaEventSynchronize(start);    //等待事件完成。
//cudaEventSynchronize(stop);    //等待事件完成。记录之前的任务
//cudaEventElapsedTime(&time, start, stop);    //计算时间差
//printf("The time by event:\t%f(ms)\n", time);
//cudaEventDestroy(start);    //消除Event
//cudaEventDestroy(stop);
//}
