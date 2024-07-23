#include "computing_interface.h"
#include <iostream>
#include <QDebug>
#include <QTime>
ComputingInterface::ComputingInterface(QObject *parent)
    : QObject{parent}
{
    init();
}

void ComputingInterface::init()
{
    IppStatus IPP_Init_status;
    IPP_Init_status=ippInit();
    qDebug()<<ippGetStatusString(IPP_Init_status);
    const IppLibraryVersion *lib;
    lib = ippsGetLibVersion();
    qDebug()<< lib->Name<< lib->Version;
    //ippSetNumThreads(1);
}

bool ComputingInterface::LhtSortFloat(float *in1, int len, float *result, bool Ascend, bool printResult)
{
    IppStatus ret;
    QTime t;
    t.start();
    memcpy(result,in1,len * sizeof(float));
    if(Ascend)
        ret = ippsSortAscend_32f_I(result,len);
    else
        ret = ippsSortDescend_32f_I(result,len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtSortFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__<<"use time = "<<t.elapsed()<<"ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtNormalizeFloat(float *in1, int len, float *result, float vSub, float vDiv, bool printResult)
{
    QTime t;
    t.start();
    // 对数组进行归一化处理
    auto status = ippsNormalize_32f(in1, result, len, vSub, vDiv);
    if(status != ippStsNoErr){
        qDebug()<<"Error LhtNormalizeFloat: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtDotProductFloat(float *in1, float *in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsDotProd_32f(in1,in2,len,result);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtDotProductFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtDotProductDouble(double *in1, double *in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsDotProd_64f(in1,in2,len,result);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtDotProductDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMulCFloat(float *in1, float in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsMulC_32f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtMulCFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtMulCDouble(double *in1, double in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsMulC_64f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtMulCDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtMulFloat(float *in1, float *in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsMul_32f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtMulFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtMutDouble(double *in1, double *in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsMul_64f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtMutDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtAddFloat(float *in1, float *in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算两个向量的对应元素之和
    auto ret = ippsAdd_32f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtAddFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtAddDouble(double *in1, double *in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算两个向量的对应元素之和
    auto ret = ippsAdd_64f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtAddDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtSubFloat(float *in1, float *in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算两个向量的对应元素之差
    auto ret = ippsSub_32f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtSubFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtSubDouble(double *in1, double *in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算两个向量的对应元素之和
    auto ret = ippsSub_64f(in1, in2, result, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtSubDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtSumFloat(float *in1, int len, float *result, IppHintAlgorithm hint, bool printResult)
{
    QTime t;
    t.start();
    // 计算量的元素之和
    auto ret = ippsSum_32f(in1, len, result,hint);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtSumFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtSumDouble(double *in1, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算量的元素之和
    auto ret = ippsSum_64f(in1, len, result);

    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtSumDouble: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtNormInfFloat(float *in1, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的无穷范数
    IppStatus status = ippsNorm_Inf_32f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtNormInfFloat: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtNormInfDouble(double *in1, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的无穷范数
    IppStatus status = ippsNorm_Inf_64f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtNormInfDouble: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMaxFloat(float *in1, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的最大值
    IppStatus status = ippsMax_32f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtMaxFloat: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMaxDouble(double *in1, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的最大值
    IppStatus status = ippsMax_64f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtMaxDouble: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMinFloat(float *in1, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的最小值
    IppStatus status = ippsMin_32f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtMinFloat: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMinDouble(double *in1, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的最小值
    IppStatus status = ippsMin_64f(in1, len, result);

    if(status != ippStsNoErr){
        qDebug()<<"Error LhtMinDouble: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtMeanFloat(float *in1, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    IppStatus status = ippsMean_32f(in1, len, result,ippAlgHintFast);
    if(status != ippStsNoErr){
        qDebug()<<"Error LhtMeanFloat: "<< status;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,1);
    }
    return true;
}

bool ComputingInterface::LhtFftInitFloat(int len)
{
    QTime t;
    t.start();
    int FFT_size = len;
    int FFTOrder = (log(FFT_size) / log(2));

    Ipp8u* pMemInit = 0;
    int sizeSpec = 0;
    int sizeInit = 0;

    int flag = IPP_FFT_NODIV_BY_ANY;
    sizeFft = (int)FFT_size;
    //add by zhuxue
    pDstR = (Ipp32f*)ippMalloc(sizeof(Ipp32f) * sizeFft);
    pDstI = (Ipp32f*)ippMalloc(sizeof(Ipp32f) * sizeFft);
    pDstTemp = (Ipp32f*)ippMalloc(sizeof(Ipp32f) * sizeFft);

    std::memset(pDstR, 0, sizeof(Ipp32f) * sizeFft);
    std::memset(pDstI, 0, sizeof(Ipp32f) * sizeFft);
    std::memset(pDstTemp, 0, sizeof(Ipp32f) * sizeFft);

    ippsFFTGetSize_C_32f(FFTOrder, flag, ippAlgHintNone, &sizeSpec, &sizeInit, &sizeBuffer);
    pMemSpec = (Ipp8u*)ippMalloc(sizeSpec);
    if (sizeInit > 0)
    {
        pMemInit = (Ipp8u*)ippMalloc(sizeInit);
    }
    if (sizeBuffer > 0)
    {
        pMemBuffer = (Ipp8u*)ippMalloc(sizeBuffer);
    }
    ippsFFTInit_C_32f(&pSpec, FFTOrder, flag, ippAlgHintNone, pMemSpec, pMemInit);
    if (sizeInit > 0)
    {
        ippFree(pMemInit);
    }

    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return 1;
}

void ComputingInterface::LhtFftFreeFloat()
{
    if(pMemSpec){
        ippFree(pMemSpec);
        ippFree(pDstR);
        ippFree(pDstI);
        ippFree(pMemBuffer);
        ippFree(pDstTemp);
    }
}

bool ComputingInterface::LhtFftFloat(float *in1, float *in2, int len, float *result, bool printResult)
{

    ippsFFTFwd_CToC_32f(in1,in2,pDstR,pDstI,pSpec, pMemBuffer);
    //计算向量的平方根
    ippsMagnitude_32f(pDstR,pDstI,pDstTemp,len);
    // LhtCalculateRootOfSumOfSquaresFloat(pDstR,pDstI,len,result);
    int halfLen = len / 2;
    ippsCopy_32f(pDstTemp+halfLen,result,halfLen);
    ippsCopy_32f(pDstTemp,result+halfLen,halfLen);

    if(printResult){
        printVector(result,len);
    }
    return 1;
}

bool ComputingInterface::LhtFftInitDouble(int len)
{
    QTime t;
    t.start();
    int FFT_size = len;
    int FFTOrder = (log(FFT_size) / log(2));

    Ipp8u* pMemInit = 0;
    int sizeSpec = 0;
    int sizeInit = 0;

    int flag = IPP_FFT_NODIV_BY_ANY;
    sizeFftD = (int)FFT_size;
    pDstRD = (Ipp64f*)ippMalloc(sizeof(Ipp64f) * sizeFftD);
    pDstID = (Ipp64f*)ippMalloc(sizeof(Ipp64f) * sizeFftD);
    std::memset(pDstRD, 0, sizeof(Ipp64f) * sizeFftD);
    std::memset(pDstID, 0, sizeof(Ipp64f) * sizeFftD);
    ippsFFTGetSize_C_64f(FFTOrder, flag, ippAlgHintNone, &sizeSpec, &sizeInit, &sizeBufferD);
    pMemSpecD = (Ipp8u*)ippMalloc(sizeSpec);
    if (sizeInit > 0)
    {
        pMemInit = (Ipp8u*)ippMalloc(sizeInit);
    }
    if (sizeBufferD > 0)
    {
        pMemBufferD = (Ipp8u*)ippMalloc(sizeBufferD);
    }
    ippsFFTInit_C_64f(&pSpecD, FFTOrder, flag, ippAlgHintNone, pMemSpecD, pMemInit);
    if (sizeInit > 0)
    {
        ippFree(pMemInit);
    }

    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return 1;
}

void ComputingInterface::LhtFftFreeDouble()
{
    if(pMemSpecD){
        ippFree(pMemSpecD);
        ippFree(pDstRD);
        ippFree(pDstID);
        ippFree(pMemBufferD);
    }
}

bool ComputingInterface::LhtFftDouble(double *in1, double *in2, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    ippsFFTFwd_CToC_64f(in1,in2,pDstRD,pDstID,pSpecD, pMemBufferD);
    //计算向量的平方根
    LhtCalculateRootOfSumOfSquaresDouble(pDstRD,pDstID,len,result);
    int halfLen = len / 2;
    // 使用 std::rotate 进行数组旋转
    std::rotate(result, result + halfLen, result + len);
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return 1;
}

bool ComputingInterface::LhtDftInitFloat(int len)
{
    QTime t;
    t.start();
    IppStatus status;
    int bufferSize;
    int specSize;
    int initSize;
    status = ippsDFTGetSize_C_32f(len, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, &specSize, &initSize, &bufferSize);
    if (status != ippStsNoErr) {
        qDebug() << "Error getting DFT size: " << status ;
        return false;
    }

    pDFTSpec = (IppsDFTSpec_C_32f*)ippsMalloc_8u(specSize);
    pDFTBuffer = ippsMalloc_8u(bufferSize);
    if (!pDFTSpec || !pDFTBuffer) {
        qDebug() << "Error allocating memory for DFT spec or buffer.";
        return false;
    }
    //IPP_FFT_FORWARD | IPP_ALG_DFT_RADIX2 | IPP_HINT_ALG_FASTEST
    status = ippsDFTInit_C_32f(len, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, pDFTSpec, pDFTBuffer);
    if (status != ippStsNoErr) {
        qDebug() << "Error initializing DFT: " << status ;
        return false;
    }

    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}

void ComputingInterface::LhtDftFreeFloat()
{
    if (pDFTSpec) {
        ippsFree(pDFTSpec);
    }
    if (pDFTBuffer) {
        ippsFree(pDFTBuffer);
    }
}

bool ComputingInterface::LhtDftFloat(float *in1, float *in2, int len, float *result1, float *result2, bool printResult)
{
    QTime t;
    t.start();
    if (!pDFTSpec || !pDFTBuffer) {
        qDebug() << "DFT not initialized.";
        return false;
    }
    auto ret = ippsDFTFwd_CToC_32f(in1,in2,result1,result2,pDFTSpec, pDFTBuffer);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtDftFloat: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result1,len);
        printVector(result2,len);
    }
    return true;
}

bool ComputingInterface::LhtCalculateRootOfSumOfSquaresFloat(const Ipp32f *v1, const Ipp32f *v2, int len, Ipp32f *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算 v1 的每个元素的平方
    auto ret =ippsSqr_32f_A24(v1, squaredV1, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresFloat1: "<< ret;
        return false;
    }
    // 计算 v2 的每个元素的平方
    ret =ippsSqr_32f_A24(v2, squaredV2, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresFloat2: "<< ret;
        return false;
    }
    // 计算每个元素的平方和
    ret =ippsAdd_32f(squaredV1, squaredV2, sumOfSquares, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresFloat3: "<< ret;
        return false;
    }
    // 计算平方和的平方根，并将结果存储在 result 中
    ret =ippsSqrt_32f_A24(sumOfSquares, result, len);

    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresFloat4: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtCalculateRootOfSumOfSquaresFloat2(const Ipp32fc *v1, int len, Ipp32f *result, bool printResult)
{
    QTime t;
    t.start();
    auto ret = ippsMagnitude_32fc(v1,result,len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresFloat2: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtCalculateRootOfSumOfSquaresDouble(const Ipp64f *v1, const Ipp64f *v2, int len, Ipp64f *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算 v1 的每个元素的平方
    auto ret =ippsSqr_64f_A53(v1, squaredV1D, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresDouble1: "<< ret;
        return false;
    }
    // 计算 v2 的每个元素的平方
    ret =ippsSqr_64f_A53(v2, squaredV2D, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresDouble2: "<< ret;
        return false;
    }
    // 计算每个元素的平方和
    ret =ippsAdd_64f(squaredV1D, squaredV2D, sumOfSquaresD, len);
    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresDouble3: "<< ret;
        return false;
    }
    // 计算平方和的平方根，并将结果存储在 result 中
    ret =ippsSqrt_64f_A53(sumOfSquaresD, result, len);

    if(ret != ippStsNoErr){
        qDebug()<<"Error LhtCalculateRootOfSumOfSquaresDouble4: "<< ret;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(result,len);
    }
    return true;
}

bool ComputingInterface::LhtNormL2Float(float *in1, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的L2范数
    IppStatus status = ippsNorm_L2_32f(in1, len, result);

    // 检查返回状态
    if (status == ippStsNoErr) {
        qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
        if(printResult)
            qDebug()<<"L2 norm: "<< *result;
        return true;
    } else {
        qDebug()<<"Error LhtNormL2Float: "<< status;
        return false;
    }

}

bool ComputingInterface::LhtPowerSpectrFloat(float *in1, float *in2, int len, float *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算功率谱
    IppStatus status = ippsPowerSpectr_32f(in1,in2, result,len);
    // 检查返回状态
    if (status == ippStsNoErr) {
        qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
        if(printResult){
            printVector(result,len);
        }
        return true;
    } else {
        qDebug()<<"Error LhtPowerSpectrFloat: "<< status;
        return false;
    }
}

bool ComputingInterface::LhtdownOrthConversion(Ipp32fc *v1, int len, int freq1, int sampleRate,  Ipp32fc *out1, bool printResult)
{
    // 生成复指数信号
    Ipp32f freq = (Ipp32f)freq1 / sampleRate; // 计算频率参数
    freq = freq < 0 ? freq + 1 : freq;
    Ipp32f phase = 0; // 初始相位
    if(mixedDataLen != len){
        if(complexExp != nullptr){
            delete complexExp;
            complexExp = nullptr;
        }
        complexExp = (Ipp32fc*)ippsMalloc_32fc(len);
        mixedDataLen = len;
    }
    ippsTone_32fc(complexExp, len, 1.0, freq, &phase, ippAlgHintAccurate);
    // 混频
    ippsMul_32fc(v1, complexExp, out1, len);

    return true;
}

bool ComputingInterface::LhtdownOrthConversion( Ipp32f *v1,  Ipp32f *v2, int len, int freq1, int sampleRate,  Ipp32f *out1,  Ipp32f *out2, bool printResult)
{
    // 生成复指数信号
    Ipp32f freq = (Ipp32f)freq1 / sampleRate; // 计算频率参数
    freq = freq < 0 ? freq + 1 : freq;
    Ipp32f phase = 0; // 初始相位
    if(mixedData == nullptr || mixedDataLen != len){
        if(mixedData != nullptr){
            delete mixedData;
            mixedData = nullptr;
            delete mixeiqdData;
            mixeiqdData = nullptr;
            delete complexExp;
            complexExp = nullptr;
        }
        complexExp = (Ipp32fc*)ippsMalloc_32fc(len);
        mixedData = (Ipp32fc*)ippsMalloc_32fc(len);
        mixeiqdData = (Ipp32fc*)ippsMalloc_32fc(len);
        mixedDataLen = len;
    }

    ippsTone_32fc(complexExp, len, 1.0, freq, &phase, ippAlgHintAccurate);

    LhtCopyRealAndimag2Complex(mixeiqdData,v1,v2,len);
    // 混频
    ippsMul_32fc(mixeiqdData, complexExp, mixedData, len);

    LhtCopyRealAndimag(mixedData,out1,out2,len);

    return true;
}

bool ComputingInterface::LhtNormL2Double(double *in1, int len, double *result, bool printResult)
{
    QTime t;
    t.start();
    // 计算向量的L2范数
    IppStatus status = ippsNorm_L2_64f(in1, len, result);

    // 检查返回状态
    if (status == ippStsNoErr) {
        qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
        if(printResult)
            qDebug()<<"L2 norm: "<< *result;
        return true;
    } else {
        qDebug()<<"Error: "<< status;
        return false;
    }
}

bool ComputingInterface::LhtFirInitFloat(const float *coeffs, int numCoeffs, IppAlgType type)
{
    QTime t;
    t.start();
    if (pFirSpec || pFirBuffer || pFirDlyLine) {
        qDebug() << "Filter already initialized.";
        return false;
    }
    int specSize = 0, bufSize = 0;
    IppStatus status = ippsFIRSRGetSize(numCoeffs, ipp32f, &specSize, &bufSize);
    if (status != ippStsNoErr) {
        qDebug() << "Error getting FIR size: " << status ;
        return false;
    }

    pFirSpec = (IppsFIRSpec_32f*)ippsMalloc_8u(specSize);
    pFirBuffer = ippsMalloc_8u(bufSize);
    //延迟线数据
    pFirDlyLine = ippsMalloc_32f(numCoeffs - 1);
    if (!pFirSpec || !pFirBuffer|| !pFirDlyLine) {
        qDebug()<< "Error allocating memory for FIR filter.";
        return false;
    }

    status = ippsFIRSRInit_32f(coeffs, numCoeffs,type , pFirSpec);
    if (status != ippStsNoErr) {
        qDebug() << "Error initializing FIR filter: " << status ;
        ippsFree(pFirSpec);
        ippsFree(pFirBuffer);
        ippsFree(pFirDlyLine);
        pFirSpec = nullptr;
        pFirBuffer = nullptr;
        pFirDlyLine = nullptr;
        return false;
    }
    ippsZero_32f(pFirDlyLine, numCoeffs - 1); // 初始化延迟线为零
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}

void ComputingInterface::LhtFirFreeFloat()
{
    if (pFirSpec) {
        ippsFree(pFirSpec);
    }
    if (pFirBuffer) {
        ippsFree(pFirBuffer);
    }
    if (pFirDlyLine) {
        ippsFree(pFirDlyLine);
    }
}

bool ComputingInterface::LhtFirFloat(const float *src, int len, float *dst, bool printResult)
{
    QTime t;
    t.start();
    if (!pFirSpec || !pFirBuffer|| !pFirDlyLine) {
        qDebug() << "Filter not initialized." ;
        return false;
    }
    //滤波
    IppStatus status = ippsFIRSR_32f(src, dst, len, pFirSpec, pFirDlyLine, pFirDlyLine, pFirBuffer);
    if (status != ippStsNoErr) {
        qDebug() << "Error applying FIR filter: " << status ;
        return false;
    }

    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}


bool ComputingInterface::LhtFirInitDouble(const double *coeffs, int numCoeffs, IppAlgType type)
{
    QTime t;
    t.start();
    if (pFirSpecD || pFirBufferD || pFirDlyLineD) {
        qDebug() << "Filter already initialized.";
        return false;
    }
    int specSize = 0, bufSize = 0;
    IppStatus status = ippsFIRSRGetSize(numCoeffs, ipp32f, &specSize, &bufSize);
    if (status != ippStsNoErr) {
        qDebug() << "Error getting FIR size: " << status ;
        return false;
    }

    pFirSpecD = (IppsFIRSpec_64f*)ippsMalloc_8u(specSize);
    pFirBufferD = ippsMalloc_8u(bufSize);
    //延迟线数据
    pFirDlyLineD = ippsMalloc_64f(numCoeffs - 1);
    if (!pFirSpecD || !pFirBufferD|| !pFirDlyLineD) {
        qDebug()<< "Error allocating memory for FIR filter.";
        return false;
    }

    status = ippsFIRSRInit_64f(coeffs, numCoeffs,type , pFirSpecD);
    if (status != ippStsNoErr) {
        qDebug() << "Error initializing FIR filter: " << status ;
        ippsFree(pFirSpecD);
        ippsFree(pFirBufferD);
        ippsFree(pFirDlyLineD);
        pFirSpecD = nullptr;
        pFirBufferD = nullptr;
        pFirDlyLineD = nullptr;
        return false;
    }
    ippsZero_64f(pFirDlyLineD, numCoeffs - 1); // 初始化延迟线为零
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}

void ComputingInterface::LhtFirFreeDouble()
{
    if (pFirSpecD) {
        ippsFree(pFirSpecD);
    }
    if (pFirBufferD) {
        ippsFree(pFirBufferD);
    }
    if (pFirDlyLineD) {
        ippsFree(pFirDlyLineD);
    }
}

bool ComputingInterface::LhtFirDouble(const double *src, int len, double *dst, bool printResult)
{
    QTime t;
    t.start();
    if (!pFirSpec || !pFirBuffer|| !pFirDlyLine) {
        qDebug() << "Filter not initialized." ;
        return false;
    }
    //滤波
    IppStatus status = ippsFIRSR_64f(src, dst, len, pFirSpecD, pFirDlyLineD, pFirDlyLineD, pFirBufferD);
    if (status != ippStsNoErr) {
        qDebug() << "Error applying FIR filter: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(dst,len);
    }
    return true;
}
#ifndef M_PI
#define M_PI 3.1415926
#endif
bool ComputingInterface::LhtFirInitFloatLp(float *coeffs, int numCoeffs)
{
    QTime t;
    t.start();
    if (pSpecLp || pBufLp ) {
        qDebug() << "Filter already initialized.";
        return false;
    }
    int specSize = 0, bufSize = 0;
    IppStatus status = ippsFIRSRGetSize(numCoeffs, ipp32f, &specSize, &bufSize);
    if (status != ippStsNoErr) {
        qDebug()  << "Error getting FIR size: " << status ;
        return false;
    }

    pSpecLp = (IppsFIRSpec_32f*)ippsMalloc_8u(specSize);
    pBufLp = ippsMalloc_8u(bufSize);
    if (!pSpecLp || !pBufLp ) {
        qDebug()  << "Error allocating memory for FIR filter." ;
        return false;
    }

    status = ippsFIRSRInit_32f(coeffs, numCoeffs, ippAlgAuto, pSpecLp);
    if (status != ippStsNoErr) {
        qDebug()  << "Error initializing FIR filter: " << status ;
        ippsFree(pSpecLp);
        ippsFree(pBufLp);
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}

void ComputingInterface::LhtFirFreeFloatLp()
{
    if (pSpecLp) {
        ippsFree(pSpecLp);
    }
    if (pBufLp) {
        ippsFree(pBufLp);
    }
}

bool ComputingInterface::LhtFirFloatLp(const float *src, float *dst, int len, bool printResult)
{
    QTime t;
    t.start();
    if (!pSpecLp || !pBufLp ) {
        qDebug()  << "Filter not initialized." ;
        return false;
    }

    IppStatus status = ippsFIRSR_32f(src, dst, len, pSpecLp, nullptr, nullptr, pBufLp);
    if (status != ippStsNoErr) {
        qDebug()  << "Error applying FIR filter: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(dst,len);
    }
    return true;
}

bool ComputingInterface::LhtFilterMedianFloat(const float *src, float *dst, int len, int makesize, bool printResult)
{
    QTime t;
    t.start();
    if(maskSize != makesize){
        maskSize = makesize;
        int bufferSize = 0;
        // 获取所需缓冲区大小
        IppStatus status = ippsFilterMedianGetBufferSize(maskSize, ipp32f, &bufferSize);
        if (status != ippStsNoErr) {
            printf("Error in getting buffer size: %d\n", status);
            return -1;
        }

        // 分配缓冲区
        pMedianBuffer = (Ipp8u *)ippsMalloc_8u(bufferSize);
        if (pMedianBuffer == NULL) {
            printf("Error in allocating buffer.\n");
            return -1;
        }

        // 分配延迟缓冲区
        pMedianDlySrc = (Ipp32f *)ippsMalloc_32f(maskSize-1);
        pMedianDlyDst = (Ipp32f *)ippsMalloc_32f(maskSize-1);
        if (pMedianDlySrc == NULL || pMedianDlyDst == NULL) {
            printf("Error in allocating delay buffers.\n");
            ippsFree(pMedianBuffer);
            return -1;
        }

        // 初始化延迟缓冲区
        ippsZero_32f(pMedianDlySrc, maskSize-1);
        ippsZero_32f(pMedianDlyDst, maskSize-1);
    }
    // 应用中值滤波
    IppStatus  status = ippsFilterMedian_32f(src, dst, len, maskSize, pMedianDlySrc, pMedianDlyDst, pMedianBuffer);
    if (status != ippStsNoErr) {
        qDebug()  << "Error LhtFilterMedianFloat: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(dst,len);
    }
    return true;
}

void ComputingInterface::LhtCopyRealAndimag(Ipp32fc *source, Ipp32f *real_dest, Ipp32f *imag_dest, int len)
{
    QTime t;
    t.start();
    ippsCplxToReal_32fc(source,real_dest,imag_dest,len);
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    // // 提取实部
    // ippsReal_32fc(source, real_dest,, len);

    // // 提取虚部
    // ippsImag_32fc(source, imag_dest, len);

}

void ComputingInterface::LhtCopyRealAndimag2Complex(Ipp32fc *dst, Ipp32f *real_dest, Ipp32f *imag_dest, int len)
{
    QTime t;
    t.start();
    ippsRealToCplx_32f(real_dest,imag_dest,dst,len);
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
}

bool ComputingInterface::LhtThreshold(const float *src, float *dst, int len, float level, float value, bool printResult)
{
    QTime t;
    t.start();
    IppStatus status = ippsThreshold_LTAbsVal_32f(src,dst,len,level,value);
    if (status != ippStsNoErr) {
        qDebug()  << "Error LhtThreshold: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(dst,len);
    }
    return true;
}

bool ComputingInterface::LhtCartToPolar(const float *in1, const float *in2, float *pDstMagn, float *pDstPhase, int len, bool printResult)
{
    QTime t;
    t.start();
    IppStatus status = ippsCartToPolar_32f(in1,in2,pDstMagn,pDstPhase,len);
    if (status != ippStsNoErr) {
        qDebug()  << "Error LhtCartToPolar: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(pDstMagn,len);
        printVector(pDstPhase,len);
    }
    return true;
}

bool ComputingInterface::LhtFlip(const float *src, float *dst, int len, bool printResult)
{
    QTime t;
    t.start();
    IppStatus status = ippsFlip_32f(src,dst,len);
    if (status != ippStsNoErr) {
        qDebug()  << "Error LhtFlip: " << status ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    if(printResult){
        printVector(dst,len);
    }
    return true;
}

void ComputingInterface::LhtResampleInit(int inRate, int outRate)
{
    QTime t;
    t.start();
    int history=128;
    int size,len,height;
    ippsResamplePolyphaseFixedGetSize_32f(inRate,outRate,2*(history-1),&size,&len,&height,ippAlgHintFast);
    pResampleState=(IppsResamplingPolyphaseFixed_32f*)ippsMalloc_8u(size);
    auto ret = ippsResamplePolyphaseFixedInit_32f(inRate,outRate,2*(history-1),0.95f,9.0f,pResampleState,ippAlgHintFast);
    if (ret != ippStsNoErr) {
        qDebug()  << "Error LhtResampleInit: " << ret ;
        return;
    }
    pInRate = inRate;
    pOutRate = outRate;
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";

}

bool ComputingInterface::LhtResample(const float* src, float* dst, int srcLen, int& retLen,float norm , bool printResult)
{
    if (!pResampleState) {
        qDebug() << "Resample not initialized.";
        return false;
    }

    if (!src || !dst) {
        qDebug() << "Invalid source or destination pointer.";
        return false;
    }
    int history=128;
    double time=history;
    QTime t;
    t.start();
    auto ret = ippsResamplePolyphaseFixed_32f(src,srcLen,dst,norm,&time,&retLen,pResampleState);
    if (ret != ippStsNoErr) {
        qDebug()  << "Error LhtSampleUp: " << ret ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";

    if (printResult) {
        printVector(dst, retLen);
    }

    return true;
}

bool ComputingInterface::LhtSampleUp(const float *pSrc, int srcLen, float *pDst, int *pDstLen, int factor)
{
    QTime t;
    t.start();
    int pPhase = 0;
    auto ret = ippsSampleUp_32f(pSrc,srcLen,pDst,pDstLen,factor,&pPhase);
    if (ret != ippStsNoErr) {
        qDebug()  << "Error LhtSampleUp: " << ret ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}

bool ComputingInterface::LhtSampleDown(const float *pSrc, int srcLen, float *pDst, int *pDstLen, int factor)
{
    QTime t;
    t.start();
    int pPhase = 0;
    auto ret = ippsSampleDown_32f(pSrc,srcLen,pDst,pDstLen,factor,&pPhase);
    if (ret != ippStsNoErr) {
        qDebug()  << "Error LhtSampleDown: " << ret ;
        return false;
    }
    qDebug() << __FUNCDNAME__ << "use time = " << t.elapsed() << "ms";
    return true;
}


void ComputingInterface::LhtResampleFree()
{
    ippFree(pResampleState);
}

template<typename T>
void ComputingInterface::printVector(const T &value, int len)
{
    for (int var = 0; var < len; ++var) {
        qDebug() <<"index:"<<var<<"="<< value[var] ;
    }

}

QString ComputingInterface::arrayToString(const float *  array, int size) {
    QString result;
    QTextStream stream(&result);

    for (int i = 0; i < size; ++i) {
        if (i != 0) {
            stream << ", "; // 在每个float之间添加逗号和空格
        }
        stream << array[i];
    }
    return result;
}
