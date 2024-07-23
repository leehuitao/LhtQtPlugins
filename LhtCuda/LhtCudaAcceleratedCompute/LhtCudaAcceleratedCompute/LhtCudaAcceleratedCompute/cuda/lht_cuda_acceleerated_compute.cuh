
#ifndef LhtCudaAcceleeratedCompute
#define LhtCudaAcceleeratedCompute

/*
//              leehuitao cuda basic algorithm library
//              create:2024/7/23  
//              包含信号处理中的大部分基础算法
//
*/
struct LhtComplex
{
    float im;
    float re;
};

void LhtComputeInit();

//向量排序  单精度浮点数Ascend  = true 升序   false  降序
bool LhtSortFloat(float* in1, int len, float* result, bool Ascend = true, bool needToCopyToTheDevice = false);
//向量点乘运算  单精度浮点数
bool LhtDotProductFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice = false);
//向量对单个值逐元素乘法  单精度浮点数
bool LhtMulCFloat(float* in1, float in2, int len, float* result, bool needToCopyToTheDevice = false);
//复数乘法
bool LhtMulCFloat(LhtComplex* in1, LhtComplex* in2, int len, LhtComplex* result, bool needToCopyToTheDevice = false);
//向量加法  单精度浮点数
bool LhtAddFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice = false);
//向量减法  单精度浮点数
bool LhtSubFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice = false);
//向量和  
bool LhtSumFloat(float* in1, int len, float* result, bool needToCopyToTheDevice = false);
//无穷范数 单精度浮点数  绝对值的最大值
bool LhtNormInfFloat(float* in1, int len, float* result, bool needToCopyToTheDevice = false);
//向量最大值 单精度浮点数
bool LhtMaxFloat(float* in1, int len, float* result, bool needToCopyToTheDevice = false);
//向量最小值 单精度浮点数
bool LhtMinFloat(float* in1, int len, float* result, bool needToCopyToTheDevice = false);
//数组均值 单精度浮点数
bool LhtMeanFloat(float* in1, int len, float* result, bool needToCopyToTheDevice = false);
//fft  初始化  比较耗时
bool LhtFftInitFloat(int len);
//fft 析构
void LhtFftFreeFloat();
//fft计算
bool LhtFftFloat(float* in1, float* in2, int len, float* result, bool needToCopyToTheDevice = false);
//dft  初始化  比较耗时
bool LhtDftInitFloat(int len);
//dft 析构
void LhtDftFreeFloat();
//dft
bool LhtDftFloat(float* in1, float* in2, int len, float* result1, float* result2, bool needToCopyToTheDevice = false);
//V1 和  𝑉2的单个元素的平方和的平方根 单精度浮点数  ippsMagnitude_32fc
bool LhtCalculateRootOfSumOfSquaresFloat(const float* v1, const float* v2, int len, float* result, bool needToCopyToTheDevice = false);
//-------------------------------2024/7/19数字下变频-------------------------------------------
bool LhtdownOrthConversion(float* v1, float* v2, int len, int freq, int sampleRate, float* out1, float* out2, bool needToCopyToTheDevice = false);

bool LhtdownOrthConversion(LhtComplex* in, int len, int freq, int sampleRate, LhtComplex* out, bool needToCopyToTheDevice = false);
    /**
     * @brief LhtSampleUp整数倍上抽
     * @param src 原始数据
     * @param dst 结果数据
     * @param srcLen 原数据长度
     * @param factor 上采样因子
     * @result dst结果长度dstLen = (srcLen * factor);
    */
bool LhtSampleUp(const float* pSrc, int  srcLen, float* pDst, int* pDstLen, int factor, bool needToCopyToTheDevice = false);
/**
 * @brief LhtSampleDown整数倍下抽
 * @param src 原始数据
 * @param dst 结果数据
 * @param srcLen 原数据长度
 * @param factor 降采样因子
 * @result dst结果长度dstLen = (srcLen / factor);
*/
bool LhtSampleDown(const float* pSrc, int  srcLen, float* pDst, int* pDstLen, int factor, bool needToCopyToTheDevice = false);
//反转元素
bool LhtFlip(const float* src, float* dst, int len, bool needToCopyToTheDevice = false);


#endif // LhtCudaAcceleeratedCompute