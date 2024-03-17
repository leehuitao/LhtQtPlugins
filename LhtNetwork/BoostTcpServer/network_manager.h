#pragma once
#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include <queue>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <boost/logic/tribool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include "tcp_connection.h" 
#include "tcp_acceptor.h"
#include "io_manager.h"
#include "session_manager.h"
#include "io_manager.h"
typedef boost::unique_lock<boost::mutex> Lock;

class NetworkManager : private boost::noncopyable
{
public:
    static NetworkManager* Instance() {
        static boost::mutex mutex;
        if (!instance_) {
            Lock locker(mutex);
            if (!instance_) {
                instance_ = new NetworkManager();
            }
        }
        return instance_;
    }
    /** ����tcp */
    void tcpAcceptor(const unsigned short& port);
    /** ��ȡһ������ */
    TcpConnectionPtr connection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType) const;

    /** һ������ */
    void addConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn) const;

    /** ɾ��һ������ */
    void removeConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const std::string& connectionID) const;

    /** ����һ������ */
    void modifyConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn) const;
private:
    static NetworkManager* instance_;
    boost::shared_ptr<TcpAcceptor> _acceptor;    /**< ��������������� */
    boost::shared_ptr<UdpDispatch> _dispatch;
    int	 _connect_count;
};

