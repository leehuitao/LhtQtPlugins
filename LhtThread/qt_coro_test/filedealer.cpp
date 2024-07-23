#include "filedealer.h"
#include <QThread>
#include <QFile>

std::atomic<int> atdbg(0);

fileDealer::fileDealer(QObject *parent)
	: QObject{parent}
{}
void fileDealer::dealFile(QString filename)
{
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}

	m_pThread = new std::thread([filename,this]()->void{
		DBG;
		QFile fp(filename);
		char buf[1024];
		unsigned long long hashfile = 0;
		DBG;
		if (fp.open(QIODevice::ReadOnly))
		{
			long long sz = fp.size();
			long long tot = 0;
			int lastP = 0;
			int rlen = fp.read(buf,1024);
			while (rlen>0)
			{
				for (int i=0;i<rlen;++i)
				{
					unsigned char c = hashfile>>56;
					hashfile <<=8;
					hashfile ^= (buf[i] ^ c );
				}
				tot += rlen;

				int P = tot * 10 / sz;
				if (P>lastP)
				{
					lastP = P;
					emit sig_progress(QString("Dealed %1 %").arg(P*10));
					DBG;
				}
				//故意弄点延迟
				//QThread::msleep(10);
				rlen = fp.read(buf,1024);
			}
		}
		result = QString("Hash = %1, file=%2").arg(hashfile,0,16).arg(filename).toUtf8();
		DBG;
		emit sig_done();
		DBG;
	});
}
