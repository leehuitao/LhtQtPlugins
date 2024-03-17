
# windows 安装gprc
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat

cd vcpkg
vcpkg install grpc:x64-windows
vcpkg install protobuf protobuf:x64-windows

# 注意：服务端需要继承ServiceNetIO::UserServiceInterface::Service   {ServiceNetIO 包名 UserServiceInterface服务名 } 重载NewNotify


# 1.服务已经封装完成初始化流程如下：
server.initParameter("0.0.0.0:50051","localhost:50052");//设置监听及目标地址
server.initRepository();//初始化方法仓库
server.setStart();//启动

# 2.方法注册函数
HandlerManager::Instance().InitHandler<TestMethod>(1);//TestMethod类名，1为指令号

# 3.接收数据后，数据包存入处理线程
m_handleInterface.recvData(request,m_stream);

# 4.处理线程为包含等待条件的线程接收数据后会自动调用
HandleInterface::handleData(std::pair<RequestBufferPtr , QString>data)

# 5.随后取出方法仓库中的指令对应的类进行方法调用
RequestHandler handler = MsgHandlerRepository<RequestHandler>::instance().handler(data.first.order_id());
handler(data.first,data.second);

6.方法函数处理结束后  发送一个新的数据包到对放rpc