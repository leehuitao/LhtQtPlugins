#include "lht_examples.h"
#include "ui_lht_examples.h"
#ifdef BUILD_SQL
#include "LhtSql/LhtMysql/dbio_mysql.hpp"
#include "LhtSql/LhtHiredis/redis_manager.h"
#include "LhtSql/LhtMongo/mongodb_manager.h"
#endif
#ifdef BUILD_GRPC
#include "LhtGrpc/NetIO/server/server_interface.h"
#endif
#ifdef BUILD_BOOST
#include "LhtNetwork/BoostTcpServer/network_manager.h"
#include "LhtNetwork/BoostTcpServer/RegisterHandler.h"
#include "LhtNetwork/BoostTcpServer/TestMethod.h"
#endif
LhtExamples::LhtExamples(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LhtExamples)
{
    ui->setupUi(this);

    initQsLog(DebugLevel,QCoreApplication::applicationDirPath() + "/log.txt",1024 * 10 ,10);
}

LhtExamples::~LhtExamples()
{
    delete ui;
}
//------------------------------------------------QsLog测试--------------------------------------------------------//
void logFunction(const QString& message, QsLogging::Level level)
{

}

//void LhtExamples::qsLogFunc(const QString &message, Level level)
//{
//    //显示到界面上，或者其他功能
//}

void LhtExamples::initQsLog(QsLogging::Level level, const QString &logPath, long long maxSizeBytes, int maxOldLogCount)
{
    using namespace QsLogging;
    // 1. init the logging mechanism
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(level);
    const QString sLogPath(logPath);

    // 2. add two destinations
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                       sLogPath, EnableLogRotation, MaxSizeBytes(maxSizeBytes), MaxOldLogCount(maxOldLogCount)));
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));//日志执行后函数             两种添加方法 第一种外部函数
    //    DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(this,SLOT(qsLogFunc(const QString& , QsLogging::Level ))));//日志执行后函数       两种添加方法 第二种类函数,不能是线程类
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
    logger.addDestination(functorDestination);

    QLOG_INFO() << "Program started";
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();
    QLOG_TRACE() << "Here's a" << QString::fromUtf8("trace") << "message";
    QLOG_DEBUG() << "Here's a" << static_cast<int>(QsLogging::DebugLevel) << "message";
    QLOG_WARN()  << "Uh-oh!";
    qDebug() << "This message won't be picked up by the logger";
    QLOG_ERROR() << "An error has occurred";
    qWarning() << "Neither will this one";
    QLOG_FATAL() << "Fatal error!";

}
//------------------------------------------------数据库测试--------------------------------------------------------//
void LhtExamples::initSql()
{
#ifdef LhtSql
    //------------------------mysql------------------------------------------
    boost::shared_ptr<DBIO> pDBIO = NULL;

    pDBIO.reset(new DBIOMysql());

    bool ret = pDBIO->initConnectionPool("dbserver", "dbuser", "dbpassword", "strDBName", 20/*pool size*/, 7777/*port*/);
    //------------------------redis初始化------------------------------------------
    RedisManager::instance().InitPool("127.0.0.1", 6379, "", 60, 20, 100);
    //------------------------mongodb初始化------------------------------------------
    MongoDBManager::instance().mongodb_init("mongodb://localhost");
#endif
}


//------------------------------------------------相机测试--------------------------------------------------------//
void LhtExamples::initCamera()
{
#ifdef BUILD_CAMERA
    auto camera1 = new CameraOPT;
    camera1->setCameraIndex(1);
    camera1->setCallBack(this);
    camera1->Init();
    auto camera2 = new CameraHik;
    camera2->setCameraIndex(1);
    camera2->setCallBack(this);
    camera2->Init();
    auto camera3 = new DahuaCamera;
    camera3->setCameraIndex(1);
    camera3->setCallBack(this);
    camera3->Init();
    bool status = camera1->OpenCamera();
    bool status1 = camera2->OpenDevice();
    bool status2 = camera3->OpenDevice();
    if(status){
        camera1->StartGenImg();
    }
    if(status1){
        camera2->StartGenImg();
    }
    if(status2){
        camera3->StartGenImg();
    }
#endif
}
//------------------------------------------------BoostServer测试--------------------------------------------------------//
#ifdef BUILD_BOOST
class HandlerManager : private boost::noncopyable
{
public:
    static HandlerManager& Instance();


    template<class Handler>
    const bool InitHandler(const unsigned short cmd);
private:

    template<class Handler>
    void NotifyHandler(RequestBufferPtr msg);

private:
    bool registered_;

};

HandlerManager& HandlerManager::Instance()
{
    static HandlerManager g_instance;
    return g_instance;
}

template<class Handler>
void HandlerManager::NotifyHandler(RequestBufferPtr msg)
{
    Handler handler;
    handler.HandleMessage(msg);
}

template<class Handler>
const bool HandlerManager::InitHandler(const unsigned short cmd)
{
    RegisterHandler::Instance()->InitHandler(cmd, boost::bind(&HandlerManager::NotifyHandler<Handler>, this, _1));
    return 1;
}

void LhtExamples::initBoostTcpServer()
{
    //------------------------方法注册------------------------------------------
    HandlerManager::Instance().InitHandler<TestMethod>(1);
    //------------------------网络初始化------------------------------------------
    NetworkManager::Instance()->tcpAcceptor(11111);//监听  (登录后再将客户端连接加到连接池里)
    //------------------------启动------------------------------------------
    LhtBoostTcpServer::IOManager::instance().run();//启动服务work
}
#endif
//------------------------------------------------Grpc测试--------------------------------------------------------//
void LhtExamples::initGrpc(){
#ifdef BUILD_GRPC
    ServerInterface server;
    ServerInterface server1;
    server.initParameter("0.0.0.0:50051","localhost:50052");
    server.initRepository();
    server.setStart();

    server1.initParameter("0.0.0.0:50052","localhost:50051");
    server1.initRepository();
    server1.setStart();

    server.connectTo();
    server1.connectTo();
    server1.test();
#endif

}

void LhtExamples::initProgress()
{

}

void LhtExamples::initTableView()
{

}

//------------------------------------------------QDataPool测试--------------------------------------------------------//

void LhtExamples::handleData(std::tuple<int, double, QString> &args)
{
    int intValue = std::get<0>(args);
    double doubleValue = std::get<1>(args);
    QString stringValue = std::get<2>(args);

    qDebug() << "Received parameters: " << intValue << ", " << doubleValue << ", " << stringValue;
}
