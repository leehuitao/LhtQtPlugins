/**

 */


#include "tcp_connection.h"
#include "io_manager.h"

#define MAX_PACKET_LENGTH	(1024 * 1024 *10)

/**
 * @brief 初始化TcpConnection对象
 * @param service 运行所需io
 * @param id 连接id
 */
TcpConnection::TcpConnection(boost::asio::io_service& service,const std::string& id):
        _id(id),
        _sock(service),
        _outStandingBufferSize(0),
		_headSize(4),
        _lastRecvTime(std::time(0)),
        _netIOService(service),
        _netTimer(service),
	_strandRead(service), 
    _strandWrite(LhtBoostTcpServer::IOManager::instance().GetAsyncIoService()),
		login_request_time(0),
	_request(new ParseRequestData)
{
	//AntUtils::mmonitor::instance().increase("TcpConnection");
}

/**
 * @brief 析构TcpConnection对象
 */
TcpConnection::~TcpConnection()
{
	//AntUtils::mmonitor::instance().reduce("TcpConnection");
	response_queue_ = std::queue<ResponseBufferPtr>();
}

/**
 * @brief 设置连接的属性
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 */
void TcpConnection::setConnectionProps(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType,
		const std::string& server_name)
{
    _userID = userID;
    _sessionType = sessionType;
    _connectionType = connectionType;
    server_name_ = server_name;
}

void TcpConnection::setAsynExcuteEventMod(bool asyn_excute_event) {_asyn_excute_event_mod = asyn_excute_event; }

const std::string& TcpConnection::id() const { return _id; }
const std::string& TcpConnection::userID() const { return _userID;}
const std::string& TcpConnection::ServerName() const { return server_name_; }
const std::string& TcpConnection::sessionType() const { return _sessionType;}
const std::string& TcpConnection::connectionType() const { return _connectionType;}
const std::size_t& TcpConnection::outStandingBufferSize() const { return _outStandingBufferSize;}
TcpConnection::tcp::socket& TcpConnection::socket(){ return _sock; }
boost::asio::io_service::strand& TcpConnection::strand(){ return _strandRead;}

void TcpConnection::close(){
    boost::system::error_code ec;
    _sock.close(ec);
}

bool TcpConnection::isIpv4() const{
    boost::system::error_code ec;
    return _sock.remote_endpoint(ec).address().is_v4();
}

bool TcpConnection::isIpv6() const{
    boost::system::error_code ec;
    return _sock.remote_endpoint(ec).address().is_v6();
}

bool TcpConnection::isMulticast() const{
    boost::system::error_code ec;
    return _sock.remote_endpoint(ec).address().is_multicast();
}

std::string TcpConnection::ip() const{
    boost::system::error_code ec;
    return _sock.remote_endpoint(ec).address().to_string(ec);
}

unsigned short TcpConnection::port() const{
    boost::system::error_code ec;
    return _sock.remote_endpoint(ec).port();
}
void TcpConnection::setExceptionCallBack(fException func) { _operationException = func; }
void TcpConnection::setRecvAfterCallBack(fRecvCallback func) { _operationRecvAfter = func; }
void TcpConnection::setSendAfterCallBack(fSendCallback func) { _operationSendAfter = func; }
// 接收收据的过程:
/*
 * 1. 由外部调用startReceive()创建异步读任务。
 * 2. 当有数据的时候，调用handleReceive
 * 3. handleReceive调用handleData，一次接收的数据拼接到一个大的缓冲区中进行分析。
 * 4. 得到完整的数据包，调用parseData
 * 5. parseData做两个事：
 *    a. 分析协议头，参数行，属性表，并根据参数调用适合的解密函数进行解密操作。
 *    b. 从handler管理器中查找注册的handler并调用具体的协议包处理过程。
 */
void TcpConnection::startReceive()
{
    _lastRecvTime = std::time(0);
	_ipaddress = ip();
    MessageBufferPtr msg(new MessageBuffer);

    boost::asio::async_read(
		_sock,
		boost::asio::buffer(msg->_data, kBufferInfoSize),
		boost::asio::transfer_at_least(1),//接收到的最小数据大小
		_strandRead.wrap(boost::bind(
			&TcpConnection::handleReceive, shared_from_this(), 
			boost::asio::placeholders::error, 
			boost::asio::placeholders::bytes_transferred, 
			msg)));
}

/**
 * @brief 发送数据
 * @param msg 指定数据
 */
std::size_t TcpConnection::sendMessage(std::string msg)
{
    _lastRecvTime = std::time(0);

	boost::shared_ptr<std::string> msgBuffer(new std::string(msg));
    _outStandingBufferSize += msg.length();

    boost::asio::async_write(
		_sock,
		boost::asio::buffer(*msgBuffer),
		_strandWrite.wrap(boost::bind(
			&TcpConnection::handleSend, shared_from_this(),
			msgBuffer,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)));

    return msg.length();
}

void TcpConnection::sendResponse(ResponseBufferPtr data)
{
    BundleResponseData response;

	response_queue_.push(data);
	if (1 == response_queue_.size()) {
		//测试
		this->sendMessage(data->body_);
		//正确的
		//this->sendMessage(response.bundleAllData(data));
	}
}

/**
 * @brief 发送打包好的应答数据
 * @param data 应答数据的指针
 */
void TcpConnection::sendBundleMessage(const ResponseBufferPtr data)
{
	ResponseBufferPtr data_copy(new ResponseBuffer(*data));
	_strandWrite.dispatch(boost::bind(&TcpConnection::sendResponse, shared_from_this(), data_copy));
}

#define MAX_TIME_OUT 2 * 60

bool TcpConnection::IsOverTime()
{
	std::time_t now = std::time(0);
	std::time_t interval = now - _lastRecvTime;
	if (interval >= MAX_TIME_OUT){
		return true;
	}

	return false;
}

/**
 * @brief 连接超时检查
 */
void TcpConnection::handleTimeout()
{
    if (!_sock.is_open())
        return ;

    if (IsOverTime()) {
        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin, ec);
		response_queue_ = std::queue<ResponseBufferPtr>();

        return ;
    }

    _netTimer.expires_from_now(boost::posix_time::seconds((long)MAX_TIME_OUT));
    _netTimer.async_wait(_strandWrite.wrap(boost::bind(&TcpConnection::handleTimeout, shared_from_this())));
}

/**
 * @brief 处理发送
 * @param error 错误代码
 */
void TcpConnection::handleSend(boost::shared_ptr<std::string> msgBuffer, const boost::system::error_code& error,
		const std::size_t& bytes)
{
    if (error) {
        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin);


    } else {
        _outStandingBufferSize -= bytes;
		response_queue_.pop();

    	if (!response_queue_.empty())
    	{
    	    BundleResponseData response;
    		sendMessage(response.bundleAllData(response_queue_.front()));
    	}
    }
}

/**
 * @brief 处理接受
 * @param error 错误代码
 * @param bytes 接受到的数据大小
 * @param msg 接受到的数据
 */
void TcpConnection::handleReceive(const boost::system::error_code& error,
        const std::size_t& bytes,
        MessageBufferPtr msg)
{
    if (!error) {
		handleData(msg, bytes);

        if (!_sock.is_open())
            return ;

        msg.reset(new MessageBuffer);
        boost::asio::async_read(
                _sock,
                boost::asio::buffer(msg->_data, kBufferInfoSize),
                boost::asio::transfer_at_least(1),
                _strandRead.wrap(boost::bind(&TcpConnection::handleReceive, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred,
                        msg)));


    } else {

        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin);


    }
}

/**
 * @brief 处理接受到的数据
 * @param msg 需处理的数据
 * @param bytes 数据大小
 */
inline void TcpConnection::handleData(MessageBufferPtr msg, const std::size_t& bytes)
{
	if (bytes <= 0) {
		return;
	}
	else 
	{

		_lastRecvTime = std::time(0);
        char* byte = new char[bytes];
        memcpy(byte, msg->_data, bytes);
        std::string str(byte, bytes);
		boost::shared_ptr<std::string> msgBuffer(new std::string(str));
		//测试
		RequestHandler handler = MsgHandlerRepository<RequestHandler>::instance().handler(1);

		if (handler.empty()) {
			handler = MsgHandlerRepository<RequestHandler>::instance().handler(kUnknownCmder);

		}
		else {
			_request->_requestBuffer.reset(new RequestBuffer);
			_request->_requestBuffer->body_ = "ceshiceshiceshiceshiceshiceshiceshiceshiceshiceshi";
			_request->_requestBuffer->conn_ = shared_from_this();

			_strandRead.post(boost::bind(handler, _request->_requestBuffer));
			//AntUtils::IOManager::instance().GetAsyncIoService().post(boost::bind(handler, _request->_requestBuffer));


		}
		/*boost::asio::async_write(
			_sock,
			boost::asio::buffer(*msgBuffer),
			_strand.wrap(boost::bind(
				&TcpConnection::handleSend, shared_from_this(),
				msgBuffer,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)));*/
		//std::cout << "receive data " << str;
        delete[]byte;
		return;
		msg->_data[bytes] = '\0';
		std::size_t curDataLen = _inputBuffer.size();
		_inputBuffer.resize(curDataLen + bytes);
		std::copy(msg->_data, msg->_data + bytes, _inputBuffer.begin() + curDataLen);
		for (;;) {
			curDataLen = _inputBuffer.size();
			if (curDataLen >= _headSize) // HEADER_LENGTH == 4
			{
				int nTem;
				::memcpy(&nTem, _inputBuffer.data(), sizeof nTem);
				const int len = be32toh(nTem);

				if (len <= 0 || len > MAX_PACKET_LENGTH)
				{
					close();
					return;
				}
				else if (curDataLen >= len)
				{
					this->parseData(_inputBuffer.data(), len);
					std::size_t leaveSize = curDataLen - len;
					if (leaveSize > 0)
					{
						std::copy(_inputBuffer.begin() + len,
							_inputBuffer.end(),
							_inputBuffer.begin());
					}
					else
					{
						leaveSize = 0;
					}

					_inputBuffer.resize(leaveSize);
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}

boost::mutex consoleLock;

void TcpConnection::parseData(const char* pBuffer, const std::size_t& bytes)
{
	_request->parseAllData(pBuffer, bytes);

	if (_request->_requestBuffer->req_status_ != kRequestStateDone)
	{
		_request->_requestBuffer->req_status_ = kRequestStateError;
	}
#if defined(DEBUG)
	std::string user = _userID;
	std::string userName = user.substr(0, user.find("@"));
	int command = _request->_requestBuffer->method_;

	if (command != 0x0071) { // 打印心跳之外的消息
		consoleLock.lock();

		if (!userName.empty()) {
			std::cout << user << std::endl;
			std::cout << "[U:" << userName << "]" << std::endl;
		}
		else {
			ActiveTcpConnection* edgeConn = dynamic_cast<ActiveTcpConnection*>(this);
			if (edgeConn) {
				std::cout << "[Edge:" << getTypeName(edgeConn->GetServerType()) << "]" << std::endl;
			}
			else {
				std::cout << "[U:Un-Login User ]" << std::endl;
			}
		}

		std::cout << "[R] thread_ID:  0x" << boost::this_thread::get_id();

		_request->_requestBuffer->printObject();

		consoleLock.unlock();
	}
#endif

	RequestHandler handler = MsgHandlerRepository<RequestHandler>::instance().handler(_request->_requestBuffer->method_);

	if (handler.empty()) {
		handler = MsgHandlerRepository<RequestHandler>::instance().handler(kUnknownCmder);

	}
	else {
		_request->_requestBuffer->conn_ = shared_from_this();

		_strandWrite.post(boost::bind(handler, _request->_requestBuffer));
			//AntUtils::IOManager::instance().GetAsyncIoService().post(boost::bind(handler, _request->_requestBuffer));


	}

	_request.reset(new ParseRequestData);
}
