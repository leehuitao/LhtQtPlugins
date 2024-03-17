#pragma once
#include <map>

/**
 * @brief 消息处理器仓库类
 * @tparam Handler 具体的操作
 */
template<typename Handler>
class GrpcMsgHandlerRepository
{
public:

    static GrpcMsgHandlerRepository& instance( );

    bool registerHandler(const unsigned short code, Handler handler);

    void removeHandler(const unsigned short code);

    Handler handler(const unsigned short  code) const;

private:
    GrpcMsgHandlerRepository();
    GrpcMsgHandlerRepository(const GrpcMsgHandlerRepository& other);
    GrpcMsgHandlerRepository& operator=(const GrpcMsgHandlerRepository& other);

private:
    typedef std::map<unsigned short, Handler> HandlerMap;

    HandlerMap handlers;    /**< 存放处理的容器 */

};

/**
 * @brief 创建MsgHandlerRepository的单例对象
 * @tparam Handler 具体的处理器
 * @return 返回MsgHandlerRepository对象
 */
template<typename Handler>
GrpcMsgHandlerRepository<Handler>& GrpcMsgHandlerRepository<Handler>::instance()
{
    static GrpcMsgHandlerRepository<Handler> _gInstance;
    return _gInstance;
}

/**
 * @brief 注册处理器至仓库
 * @tparam Handler 具体的处理器类型
 * @param code 处理器的标示
 * @param handler 具体的处理器
 * @return 返回是否注册成功
 */
template<typename Handler>
bool GrpcMsgHandlerRepository<Handler>::registerHandler(const unsigned short code,
    Handler handler) {
    return this->handlers.insert(std::make_pair(code, handler)).second;
}

/**
 * @brief 删除仓库里的处理器
 * @tparam Handler 具体的处理器类型
 * @param code 处理的标示
 */
template<typename Handler>
void GrpcMsgHandlerRepository<Handler>::removeHandler(const unsigned short code)
{
    this->handlers.erase(code);
}

/**
 * @brief 获取仓库里的处理器
 * @tparam Handler 具体的处理器类型
 * @param code 处理器的标示
 * @return 返回处理器
 */
template<typename Handler>
Handler GrpcMsgHandlerRepository<Handler>::handler(const unsigned short code) const
{
    typename HandlerMap::const_iterator i = this->handlers.find(code);
    return i != this->handlers.end() ? i->second : Handler();
}

/**
 * @brief 初始化MsgHandlerRepository对象
 * @tparam Handler
 */
template<typename Handler>
GrpcMsgHandlerRepository<Handler>::GrpcMsgHandlerRepository()
{
}

/**
 * @brief 初始化MsgHandlerRepository对象
 * @tparam Handler 具体的处理器类型
 * @param other 具体的处理器类型
 */
template<typename Handler>
GrpcMsgHandlerRepository<Handler>::GrpcMsgHandlerRepository(
    const GrpcMsgHandlerRepository<Handler>& other)
{
}

/**
 * @brief 重载=
 * @tparam Handler 具体的处理器类型
 * @param other 具体的处理器
 * @return =
 */
template<typename Handler>
GrpcMsgHandlerRepository<Handler>& GrpcMsgHandlerRepository<Handler>::operator=(
    const GrpcMsgHandlerRepository<Handler>& other)
{
    return *this;
}

