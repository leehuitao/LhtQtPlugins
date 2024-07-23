#ifndef COMPUTING_INTERFACE_H
#define COMPUTING_INTERFACE_H

#include <QObject>
#include "ipp.h"
#include "ipps.h"
#include "ippcore.h"
class ComputingInterface : public QObject
{
    Q_OBJECT
public:
    explicit ComputingInterface(QObject *parent = nullptr);

    void init();
    //向量排序  单精度浮点数Ascend  = true 升序   false  降序
    bool LhtSortFloat(float * in1 ,int len,float * result ,bool Ascend = true,bool printResult = false);
    //向量排序  单精度浮点数Ascend  = true 升序   false  降序
    __declspec(deprecated("需要提前找到最大值来做一个除法  才可以将他归一化到0-1."))
    bool LhtNormalizeFloat(float * in1 ,int len,float * result,float  vSub, float vDiv,bool printResult = false);
    //向量点乘运算  单精度浮点数
    bool LhtDotProductFloat(float * in1 , float * in2 ,int len,float * result,bool printResult = false);
    //向量对单个值逐元素乘法  单精度浮点数
    bool LhtMulCFloat(float * in1 , float in2 ,int len,float * result,bool printResult = false);
    //向量逐元素乘法  单精度浮点数
    bool LhtMulFloat(float * in1 , float* in2 ,int len,float * result,bool printResult = false);
    //向量加法  单精度浮点数
    bool LhtAddFloat(float * in1 , float * in2 ,int len,float * result,bool printResult = false);
    //向量减法  单精度浮点数
    bool LhtSubFloat(float * in1 , float * in2 ,int len,float * result,bool printResult = false);
    //向量和  单精度浮点数 ippAlgHintFast 最快    ippAlgHintAccurate  最准确
    bool LhtSumFloat(float * in1 ,int len,float * result, IppHintAlgorithm hint = ippAlgHintFast,bool printResult = false);
    //无穷范数 单精度浮点数  绝对值的最大值
    bool LhtNormInfFloat(float * in1 ,int len,float * result,bool printResult = false);
    //向量最大值 单精度浮点数
    bool LhtMaxFloat(float * in1 ,int len,float * result,bool printResult = false);
    //向量最小值 单精度浮点数
    bool LhtMinFloat(float * in1 ,int len,float * result,bool printResult = false);
    //数组均值 单精度浮点数
    bool LhtMeanFloat(float * in1 ,int len,float * result,bool printResult = false);
    //fft  初始化  比较耗时
    bool LhtFftInitFloat(int len);
    //fft 析构
    void LhtFftFreeFloat();
    //fft计算
    bool LhtFftFloat(float * in1 , float * in2 ,int len,float * result,bool printResult = false);
    //dft  初始化  比较耗时
    bool LhtDftInitFloat(int len);
    //dft 析构
    void LhtDftFreeFloat();
    //dft
    bool LhtDftFloat(float * in1 , float * in2 ,int len,float * result1,float * result2,bool printResult = false);
    //V1 和  𝑉2的单个元素的平方和的平方根 单精度浮点数  ippsMagnitude_32fc
    bool LhtCalculateRootOfSumOfSquaresFloat(const Ipp32f* v1, const Ipp32f* v2, int len, Ipp32f* result,bool printResult = false);
    //复数元素的平方和的平方根 单精度浮点数
    bool LhtCalculateRootOfSumOfSquaresFloat2(const Ipp32fc* v1,int len, Ipp32f* result,bool printResult = false);
    //数组平方和的平方根 单精度浮点数
    bool LhtNormL2Float(float * in1 ,int len,float * result,bool printResult = false);
    //计算功率谱ippsPowerSpectr_32f
    bool LhtPowerSpectrFloat(float * in1 ,float * in2 ,int len,float * result,bool printResult = false);

    //-------------------------------2024/7/19数字下变频-------------------------------------------
    bool LhtdownOrthConversion( Ipp32f* v1,  Ipp32f* v2, int len, int freq ,int sampleRate, Ipp32f* out1,  Ipp32f* out2 ,bool printResult = false );

    bool LhtdownOrthConversion( Ipp32fc* v1, int len, int freq ,int sampleRate, Ipp32fc* out1,bool printResult = false );
    //------------------------------------滤波器---------------------------------------------------

    //FIR  初始化  比较耗时
    bool LhtFirInitFloat(const float* coeffs, int numCoeffs,IppAlgType type = ippAlgFFT);
    //FIR 析构
    void LhtFirFreeFloat();
    //FIR
    bool LhtFirFloat(const float* src,  int len,float* dst,bool printResult = false);


    //低通滤波
    //初始化  比较耗时
    bool LhtFirInitFloatLp(float * coeffs,int numCoeffs);
    // 析构
    void LhtFirFreeFloatLp();
    //
    bool LhtFirFloatLp(const float* src, float* dst, int len,bool printResult = false);

    //应用中位数滤波
    bool LhtFilterMedianFloat(const float* src, float* dst, int len,int masksize,bool printResult = false);

    //将低于阈值的值设定为某个值
    bool LhtThreshold(const float* src, float* dst, int len,float level,float value,bool printResult = false);

    //快速提取复数中的实部和虚部
    void LhtCopyRealAndimag(Ipp32fc *source, Ipp32f *real_dest, Ipp32f *imag_dest, int len) ;
    //快速将实部和虚部放到数组中
    void LhtCopyRealAndimag2Complex(Ipp32fc *dst, Ipp32f *real_dest, Ipp32f *imag_dest, int len) ;

    //这个函数将二维空间中点的 (x, y) 坐标转换为极坐标 (r, θ)，其中 r 是径向距离（幅度），θ 是角度（相位）。
    bool LhtCartToPolar(const float* in1, const float* in2, float* pDstMagn, float* pDstPhase, int len,bool printResult = false);
    //反转元素
    bool LhtFlip(const float* src, float* dst, int len,bool printResult = false);

    //-------------------------------重采样-----------------------------------
    /**
     * @brief LhtResampleInit非整数倍重采样初始化
     * @param inRate 输入采样率
     * @param outRate 输出采样率
    */
    void LhtResampleInit(int inRate,int outRate );
    /**
     * @brief LhtResample非整数倍重采样函数（必要LhtResampleInit）
     * @param src 原始数据
     * @param dst 结果数据
     * @param srcLen 原数据长度
     * @param norm 归一化因子1.0为不变  0.5为减半
     * @result dst结果长度dstLen = (srcLen * pUpFactor) / pDownFactor;
    */
    bool LhtResample(const float* src, float* dst, int srcLen,int & retLen,float norm = 1.0f,bool printResult = false);
    //IPPAPI(IppStatus, ippsSampleUp_32f,  (const Ipp32f*  pSrc, int  srcLen, Ipp32f*  pDst, int* pDstLen, int factor, int* pPhase))
    /**
     * @brief LhtSampleUp整数倍上抽
     * @param src 原始数据
     * @param dst 结果数据
     * @param srcLen 原数据长度
     * @param factor 上采样因子
     * @result dst结果长度dstLen = (srcLen * factor);
    */
    bool LhtSampleUp(const float*  pSrc, int  srcLen, float*  pDst, int* pDstLen, int factor);
    /**
     * @brief LhtSampleDown整数倍下抽
     * @param src 原始数据
     * @param dst 结果数据
     * @param srcLen 原数据长度
     * @param factor 降采样因子
     * @result dst结果长度dstLen = (srcLen / factor);
    */
    bool LhtSampleDown(const float*  pSrc, int  srcLen, float*  pDst, int* pDstLen, int factor);

    void LhtResampleFree();
    //--------------------------------------------double类型-------------------------------------------------

    //向量点乘运算  双精度浮点数
    bool LhtDotProductDouble(double * in1 , double * in2 ,int len,double * result,bool printResult = false);
    //向量逐元素乘法  双精度浮点数
    bool LhtMulCDouble(double * in1 , double in2 ,int len,double * result,bool printResult = false);
    //向量乘法  双精度浮点数
    bool LhtMutDouble(double * in1 , double* in2 ,int len,double * result,bool printResult = false);
    //向量加法  双精度浮点数
    bool LhtAddDouble(double * in1 , double * in2 ,int len,double * result,bool printResult = false);
    //向量减法  双精度浮点数
    bool LhtSubDouble(double * in1 , double * in2 ,int len,double * result,bool printResult = false);
    //向量和  双精度浮点数
    bool LhtSumDouble(double * in1 ,int len,double * result,bool printResult = false);
    //无穷范数 双精度浮点数绝对值的最大值
    bool LhtNormInfDouble(double * in1 ,int len,double * result,bool printResult = false);
    //向量最大值 双精度浮点数
    bool LhtMaxDouble(double * in1 ,int len,double * result,bool printResult = false);
    //向量最小值 双精度浮点数
    bool LhtMinDouble(double * in1 ,int len,double * result,bool printResult = false);
    //fft  初始化  比较耗时
    bool LhtFftInitDouble(int len);
    //fft 析构
    void LhtFftFreeDouble();
    //fft计算
    bool LhtFftDouble(double * in1 , double * in2 ,int len,double * result,bool printResult = false);
    //V1 和  𝑉2的单个元素的平方和的平方根 双精度浮点数
    bool LhtCalculateRootOfSumOfSquaresDouble(const Ipp64f* v1, const Ipp64f* v2, int len, Ipp64f* result,bool printResult = false);
    //数组平方和的平方根 双精度浮点数
    bool LhtNormL2Double(double * in1 ,int len,double * result,bool printResult = false);
    //FIR  初始化  比较耗时
    bool LhtFirInitDouble(const double* coeffs, int numCoeffs,IppAlgType type = ippAlgFFT);
    //FIR 析构
    void LhtFirFreeDouble();
    //FIR
    bool LhtFirDouble(const double* src,  int len,double* dst,bool printResult = false);

    QString arrayToString(const float * array, int size);
signals:

private:
    template<typename T>
    void printVector(const T& value , int len);
    // 定义存储中间结果的向量   求平方根时使用
    Ipp32f squaredV1[16384 * 16];
    Ipp32f squaredV2[16384 * 16];
    Ipp32f sumOfSquares[16384 * 16];

    // 定义存储中间结果的向量   求平方根时使用
    Ipp64f squaredV1D[16384 * 16];
    Ipp64f squaredV2D[16384 * 16];
    Ipp64f sumOfSquaresD[16384 * 16];
    //float 类型 fft
    int sizeFft;
    int sizeBuffer;
    Ipp32f * pDstR= nullptr;
    Ipp32f * pDstI= nullptr;
    Ipp32f * pDstTemp= nullptr;
    Ipp8u* pMemSpec= nullptr;
    Ipp8u* pMemBuffer= nullptr;
    IppsFFTSpec_C_32f * pSpec= nullptr;

    //double 类型 fft
    int sizeFftD;
    int sizeBufferD;
    Ipp64f * pDstRD= nullptr;
    Ipp64f * pDstID= nullptr;
    Ipp8u* pMemSpecD= nullptr;
    Ipp8u* pMemBufferD= nullptr;
    IppsFFTSpec_C_64f * pSpecD= nullptr;

    //Dft
    IppsDFTSpec_C_32f* pDFTSpec= nullptr;
    Ipp8u* pDFTBuffer= nullptr;
    Ipp32f * pDstDftR= nullptr;
    Ipp32f * pDstDftI= nullptr;
    //fir
    IppsFIRSpec_32f* pFirSpec= nullptr;
    Ipp8u* pFirBuffer= nullptr;
    Ipp32f* pFirDlyLine= nullptr;

    //fir double
    IppsFIRSpec_64f* pFirSpecD= nullptr;
    Ipp8u* pFirBufferD= nullptr;
    Ipp64f* pFirDlyLineD= nullptr;

    //低通滤波
    IppsFIRSpec_32f* pSpecLp = nullptr;
    Ipp8u* pBufLp= nullptr;

    //重采样
    int             pInRate;
    int             pOutRate;
    int             pFilterLen;
    // 归一化因子
    Ipp32f          pResampleNorm = 1.0;
    // 重采样起始时间
    Ipp64f          pResampleTime = 0.0;
    IppsResamplingPolyphaseFixed_32f *pResampleState;
    //中位数滤波
    int maskSize = -1;//中位数滤波
    Ipp8u * pMedianBuffer= nullptr;
    Ipp32f *pMedianDlySrc = nullptr;
    Ipp32f *pMedianDlyDst = nullptr;
    //下变频
    Ipp32fc* mixedData = nullptr;
    Ipp32fc* mixeiqdData = nullptr;
    int mixedDataLen=0;
    Ipp32fc * complexExp = nullptr;
};

#endif // COMPUTING_INTERFACE_H
