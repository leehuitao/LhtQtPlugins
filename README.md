# 欢迎 代码库转移到Github
https://github.com/leehuitao
# 一些相关模块或者库的编译方式
https://gitee.com/shijingying/GoTestServer
# 📚简介
本项目为本人在工作中遇到过的，或者平时学习到的一些觉得好用的方法/基类/功能等

# 📦软件架构
- Qt 5.14.2 + msvc 2017
- Windows

# 🛠️主要技术


| 模块                |     介绍        |        Activity     |
| -------------------|----------------- |----------------- |
| LhtIPPS |     ipps加速算法/openblas加速/fftw   | 测试用例：向量加减乘除加速，低通滤波等加速，dft,fft加速，复数的快速转换，排序，数组反转，数字下变频，快速相位提取，功率谱计算，非整数倍重采样  |
| LhtLocalization |     国产化   | Windows下虚拟国产话设备的方法，Qt安装，编译   |
| LhtCuda    |     CUDA相关代码   | cuda11.8版本，信号处理中常用的处理算法，排序，复数乘法，点积，最大值，最小值，均值，fft，dft，下变频，重采样，多流多线程，耗时，信息获取，多流FFT，nsight system的使用 |
| LhtCamera    |     一些相机的SDK的调用          | 海康/大华/OPT |
| LhtEncode                |     编码和解码             | OPUS/AAC/MD5/SHA/OpenSsl/H264 |
| LhtExamples             |     测试程序                | 包含各个模块的测试使用|
| LhtFile |     简单的文件处理         | QFile/QDataStream/QTextStream/Qt文件映射写入 |
| LhtGrpc |     GRPC的测试案例          | QT GRPC 调用测试 |
| LhtGui |     一些与UI相关的代码         | 自己做的一些QT的UI小组件，QCustomPlotV2 升级版本，启用gpu，曲线平滑，一次性拷贝，只允许XY轴缩放等 |
| LhtImage|     图像处理，转换等       | Halcon图像算法/图像转换 灰度图/YUV/RGB/MONO8/QT图像与cv::Mat转换 |
| LhtLog|     日志系统           | QsLog/GLog |
| LhtModel|     Epoll等         | Epoll/select/iocp |
| LhtNetwork|     绝大部分网络的使用相关     | 一些网络框架  C++ Boost Tcp服务框架/Qt Tcp服务客户端框架/Qt  tcp udp serial http 客户端框架|
| LhtSql|    多种数据库的并发使用        | Mysql线程池/redis线程池/Mongo线程池 |
| LhtThread|  好用的线程基类，异步处理      | 无锁线程/事件驱动线程/普通线程/重载Run/C++线程 |
| LhtOffice|  word/excel等的导出      | 用Concurrent不卡线程 |


# 🧡Star

