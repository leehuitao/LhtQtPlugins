#include "lht_cuda_acceleerated_compute.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


void LhtComputeInit()
{

}

//向量排序  单精度浮点数Ascend  = true 升序   false  降序
bool LhtSortFloat(float* in1, int len, float* result, bool Ascend , bool needToCopyToTheDevice)
{
	float* temp;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp, sizeof(float) * len);
		cudaMemcpy(in1, temp, sizeof(float)*len, cudaMemcpyHostToDevice);
	}
	else {
		temp = in1;
	}


	return 1;
}

//向量点乘运算  单精度浮点数
bool LhtDotProductFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice)
{
	float* temp1;
	float* temp2;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp1, sizeof(float) * len);
		cudaMemcpy(in1, temp1, sizeof(float) * len, cudaMemcpyHostToDevice);
		cudaMalloc(&temp2, sizeof(float) * len);
		cudaMemcpy(in1, temp2, sizeof(float) * len, cudaMemcpyHostToDevice);
	}
	else {
		temp1 = in1;
		temp2 = in2;
	}


	return 1;
}

//向量对单个值逐元素乘法  单精度浮点数
bool LhtMulCFloat(float* in1, float in2, int len, float* result, bool needToCopyToTheDevice)
{
	float* temp;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp, sizeof(float) * len);
		cudaMemcpy(in1, temp, sizeof(float) * len, cudaMemcpyHostToDevice);
	}
	else {
		temp = in1;
	}


	return 1;
}
//复数乘法
bool LhtMulCFloat(LhtComplex* in1, LhtComplex* in2, int len, LhtComplex* result, bool needToCopyToTheDevice)
{

}
//向量加法  单精度浮点数
bool LhtAddFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice)
{
	float* temp;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp, sizeof(float) * len);
		cudaMemcpy(in1, temp, sizeof(float) * len, cudaMemcpyHostToDevice);
	}
	else {
		temp = in1;
	}


	return 1;
}
//向量减法  单精度浮点数
bool LhtSubFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice)
{
	float* temp;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp, sizeof(float) * len);
		cudaMemcpy(in1, temp, sizeof(float) * len, cudaMemcpyHostToDevice);
	}
	else {
		temp = in1;
	}


	return 1;
}
//向量和  
bool LhtSumFloat(float* in1, int len, float* result, bool needToCopyToTheDevice)
{
	float* temp;
	cudaMalloc(&result, sizeof(float) * len);
	if (needToCopyToTheDevice) {
		cudaMalloc(&temp, sizeof(float) * len);
		cudaMemcpy(in1, temp, sizeof(float) * len, cudaMemcpyHostToDevice);
	}
	else {
		temp = in1;
	}


	return 1;
}