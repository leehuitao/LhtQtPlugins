#include "lht_basic_kernel.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"

//点加
__global__ void lhtAdd(float* in1, float* in2, float* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index < len)
		out[index] = in1[index] + in2[index];
}
//点减
__global__ void lhtSub(float* in1, float* in2, float* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index < len)
		out[index] = in1[index] - in2[index];
}
//点乘
__global__ void lhtMulc(float* in1, float* in2, float* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index < len)
		out[index] = in1[index] * in2[index];
}

//乘系数
__global__ void lhtMulc(float* in1, float int2, float* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index < len)
		out[index] = in1[index] * int2;
}

//复数乘
__global__ void lhtMulc(cufftComplex* in1, cufftComplex* in2, cufftComplex* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index < len) {
		//float a = in1[index].x; // 实部
		//float b = in1[index].y; // 虚部
		//float c = in2[index].x; // 实部
		//float d = in2[index].y; // 虚部
		out[index].x = in1[index].x * in2[index].x - in1[index].y * in2[index].y; // 结果的实部
		out[index].y = in1[index].x * in2[index].y + in1[index].y * in2[index].x; // 结果的虚部
	}
}

//排序
__global__ void lhtSort(float* in1, float* out, int len)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
}

//向量和  包含下面的均值都是规约求和
__global__ void lhtSum(float* in1, float* out, int len)
{
	unsigned int tid = threadIdx.x;
	//boundary check
	if (tid >= len) return;
	//convert global data pointer to the 
	float* idata = in1 + blockIdx.x * blockDim.x;
	//in-place reduction in global memory
	for (int stride = 1; stride < blockDim.x; stride *= 2)
	{
		if ((tid % (2 * stride)) == 0)
		{
			idata[tid] += idata[tid + stride];
		}
		//synchronize within block
		__syncthreads();
	}
	//write result for this block to global mem
	if (tid == 0)
		out[blockIdx.x] = idata[0];
}

//向量绝对值的和
__global__ void lhtAbsSum(float* in1, float* out, int len)
{
	unsigned int tid = threadIdx.x;
	//boundary check
	if (tid >= len) return;
	//convert global data pointer to the 
	float* idata = in1 + blockIdx.x * blockDim.x;
	//in-place reduction in global memory
	for (int stride = 1; stride < blockDim.x; stride *= 2)
	{
		if ((tid % (2 * stride)) == 0)
		{
			idata[tid] += (idata[tid + stride] > 0 ? idata[tid + stride] : -idata[tid + stride]);
		}
		//synchronize within block
		__syncthreads();
	}
	//write result for this block to global mem
	if (tid == 0)
		out[blockIdx.x] = idata[0];
}
//向量均值
__global__ void lhtMean(float* in1, float* out, int len)
{
	int blocksize = 1024;
	float gpu_sum = 0;
	dim3 block(blocksize, 1);
	dim3 grid((len - 1) / block.x + 1, 1);
	lhtSum(in1, out, len);
	for (int i = 0; i < grid.x; i++)
		gpu_sum += out[i];
	out[0] = gpu_sum / len;
}

//向量绝对值均值
__global__ void lhtAbsMean(float* in1, float* out, int len)
{
	int blocksize = 1024;
	float gpu_sum = 0;
	dim3 block(blocksize, 1);
	dim3 grid((len - 1) / block.x + 1, 1);
	lhtSum(in1, out, len);
	for (int i = 0; i < grid.x; i++)
		gpu_sum += out[i];
	out[0] = gpu_sum / len;
}

//向量最大值
__global__ void lhtMax(float* in1, float* out, int len)
{
	int tid = threadIdx.x;
	if (tid >= len)return;

	float* data = in1 + blockIdx.x * blockDim.x;
	for (int stride = 1; stride < blockDim.x; stride *= 2)
	{
		if ((tid % (2 * stride)) == 0)
		{
			if (data[tid] < data[tid + stride])
			{
				data[tid] = data[tid + stride];
			}
		}
		__syncthreads();
	}
	if (tid == 0)
	{
		out[blockIdx.x] = data[0];
	}
}

//向量最小值
__global__ void lhtMin(float* in1, float* out, int len)
{
	int tid = threadIdx.x;
	if (tid >= len)return;

	float* data = in1 + blockIdx.x * blockDim.x;
	for (int stride = 1; stride < blockDim.x; stride *= 2)
	{
		if ((tid % (2 * stride)) == 0)
		{
			if (data[tid] < data[tid + stride])
			{
				data[tid] = data[tid + stride];
			}
		}
		__syncthreads();
	}
	if (tid == 0)
	{
		out[blockIdx.x] = data[0];
	}
}



void LhtCopy2Host(float* in1, float* out, int len)
{
	cudaMemcpy(out, in1, sizeof(float)*len, cudaMemcpyDeviceToHost);
}