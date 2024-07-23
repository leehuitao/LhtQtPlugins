#ifndef FILEDEALER_H
#define FILEDEALER_H

#include <QObject>
#include <thread>
#include <QThread>
#include <coroutine>
#include <functional>
#include <QDebug>
#include <atomic>

extern std::atomic<int> atdbg;
#define DBG {qDebug()<<++atdbg<<"Thread"<<QThread::currentThreadId()<<__FUNCTION__<<"@"<<__FILE__<<":"<<__LINE__;}

/*!
 * \brief The fileDealer class 这个类实现了计算文件哈希的演示功能。
 */
class fileDealer : public QObject
{
	Q_OBJECT
public:
	explicit fileDealer(QObject *parent = nullptr);
	~fileDealer()
	{
		DBG;
		if (m_pThread)
		{
			DBG;
			m_pThread->join();
			delete m_pThread;
			m_pThread = nullptr;

		}
	}
	//dealFile 计算哈希，存储在 result 里
	void dealFile(QString filename);
public:
	QByteArray result;
private:
	std::thread * m_pThread = nullptr;
signals:
	void sig_done();
	void sig_progress(QString p);
};

/*!
 * \brief The FileTask class	协程结构体
 */
struct FileTask
{
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;
	FileTask(handle_type h)
	{DBG;}
	FileTask(FileTask&& s)
	{DBG;}

	struct promise_type {
		promise_type() = default;
		~promise_type() = default;
		auto get_return_object() noexcept {
			DBG;
			return FileTask{handle_type::from_promise(*this)};
		}
		auto initial_suspend() noexcept {
			//一创建立刻执行
			DBG;
			return std::suspend_never{};
		}
		auto final_suspend() noexcept {
			DBG;
			return std::suspend_always{};
		}
		void unhandled_exception() {
			DBG;
			exit(1);
		}
		void return_void()
		{DBG;}
	};

};
/*!
 * \brief The awDealFile class	协程 await 对象
 */
class awDealFile : public QObject
{
	Q_OBJECT
public:
	awDealFile(QString filename,std::function<void (QString)> func_prog = nullptr,QObject *parent = nullptr)
		:QObject(parent)
		,m_fn(filename)
		,m_pDealer(new fileDealer)
	{
		DBG;
		if (func_prog)
			connect (m_pDealer,&fileDealer::sig_progress,func_prog);
		//处理完毕的信号，会在处理线程里发出，所以用QueuedConnection确保协程返回时，保持线程不变。
		QObject::connect(m_pDealer,&fileDealer::sig_done,this, &awDealFile::slot_done,Qt::QueuedConnection);

	}
	~awDealFile()
	{
		DBG;
		if (m_pDealer)
			m_pDealer->deleteLater();
		m_pDealer = nullptr;
	}
	bool await_ready() {
		DBG;
		return false;
	}
	/*!
	 * \brief await_resume	这个函数的返回值决定了 await 关键词可以返回什么类型的东西
	 * \return 哈希结果
	 */
	QByteArray await_resume() {
		DBG;
		return m_pDealer->result;
	}

	/*!
	 * \brief await_suspend	co_await 时，会调用这个函数。此时，启动处理，并在处理完毕后resume
	 * \param h
	 */
	void await_suspend(FileTask::handle_type h) {
		hd = h;
		//处理
		DBG;
		m_pDealer->dealFile(m_fn);
		DBG;
	}
private slots:
	void slot_done()
	{
		DBG;
		if (hd)
			hd.resume();
	}
private:
	QString m_fn;
	fileDealer * m_pDealer = nullptr;
	FileTask::handle_type hd;
};


#endif // FILEDEALER_H
