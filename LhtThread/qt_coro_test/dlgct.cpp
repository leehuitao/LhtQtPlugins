#include "dlgct.h"
#include "ui_dlgct.h"
#include <QDateTime>
#include <QFileInfo>
#include <QSettings>
#include <QFileDialog>
#include "nmcalc.h"
DlgCT::DlgCT(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgCT)
	, m_pMsgMod(new QStandardItemModel(this))
{
	ui->setupUi(this);
	//显示消息的模型
	ui->listView_msg->setModel(m_pMsgMod);
	//最大化按钮
	setWindowFlag(Qt::WindowMinMaxButtonsHint);
	//界面元素记忆
	QSettings settings(QCoreApplication::applicationFilePath()+".ini",QSettings::IniFormat);
	ui->lineEdit_file->setText(settings.value("ui/lineEdit_file","").toString());
	ui->spinBox_N->setValue(settings.value("ui/spinBox_N",10).toInt());
	ui->spinBox_M->setValue(settings.value("ui/spinBox_M",5).toInt());
	//演示非阻塞调用时，定时器依旧活跃
	m_nTimerID = startTimer(500);
	//跨线程显示界面用到的队列槽
	connect(this,&DlgCT::shootMsg,this,&DlgCT::showMsg,Qt::QueuedConnection);
	showMsg("Program started.");
}

DlgCT::~DlgCT()
{
	delete ui;
}

void DlgCT::on_toolButton_file_clicked()
{
	QSettings settings(QCoreApplication::applicationFilePath()+".ini",QSettings::IniFormat);
	QString lastDir = settings.value("history/lastDir","./").toString();
	QString fm  = QFileDialog::getOpenFileName(this,tr("Open File"),lastDir,"Files(*.*)");
	QFileInfo info(fm);
	if (info.exists())
	{
		settings.setValue("history/lastDir",info.absolutePath());
		ui->lineEdit_file->setText(info.absoluteFilePath());
	}
}
void DlgCT::on_pushButton_file_clicked()
{
	DBG;
	QSettings settings(QCoreApplication::applicationFilePath()+".ini",QSettings::IniFormat);
	settings.setValue("ui/lineEdit_file",ui->lineEdit_file->text());
	DBG;
	dealFile(ui->lineEdit_file->text());
}
FileTask DlgCT::dealFile(QString filename)
{
	using std::placeholders::_1;
	using std::bind;
	DBG;
	++m_nBusy;
	//传入的进度回调，注意可能在另一个线程执行，所以采用的是信号而非槽。
	QByteArray res = co_await awDealFile(filename,bind(&DlgCT::shootMsg,this,_1));
	DBG;
	--m_nBusy;
	//如果在协程对象里不使用Queued槽，则此处已经发生了协程切换。
	showMsg(res);

}
void DlgCT::showMsg(QString msg)
{
	//DBG;
	QString strDtm = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + " > ";
	m_pMsgMod->appendRow(new QStandardItem(strDtm + msg));
	if (m_pMsgMod->rowCount()>256)
	{
		m_pMsgMod->removeRows(0,m_pMsgMod->rowCount()-256);
	}
	ui->listView_msg->scrollToBottom();
}

void DlgCT::timerEvent(QTimerEvent * evt)
{
	if (evt->timerId()==m_nTimerID && m_nBusy>0)
	{
		DBG;
		showMsg("Running...");
	}
}

void DlgCT::on_pushButton_normal_clicked()
{
	DBG;
	++m_nBusy;
	QFile fp(ui->lineEdit_file->text());
	char buf[1024];
	unsigned long long hashfile = 0;
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
				DBG;
				lastP = P;
				showMsg(QString("Dealed %1 %").arg(P*10));
			}
			rlen = fp.read(buf,1024);
			//假多线程，也可以看做是Qt的有栈协程，人为释放资源
			QCoreApplication::processEvents();
		}
	}
	DBG;
	showMsg(QString("Hash = %1, file=%2").arg(hashfile,0,16).arg(ui->lineEdit_file->text()));
	--m_nBusy;
}


void DlgCT::on_pushButton_thread_clicked()
{
	fileDealer * dealer = new fileDealer(this);
	connect(dealer,&fileDealer::sig_done,[dealer,this]()->void{
		DBG;
		emit shootMsg(dealer->result);
		dealer->deleteLater();
		--m_nBusy;
	});
	connect(dealer,&fileDealer::sig_progress,this,&DlgCT::shootMsg);
	DBG;
	++m_nBusy;
	dealer->dealFile(ui->lineEdit_file->text());
	DBG;
}


void DlgCT::on_pushButton_PNM_clicked()
{
	QSettings settings(QCoreApplication::applicationFilePath()+".ini",QSettings::IniFormat);
	settings.setValue("ui/spinBox_N",ui->spinBox_N->value());
	settings.setValue("ui/spinBox_M",ui->spinBox_M->value());
	const int n = ui->spinBox_N->value();
	const int m = ui->spinBox_M->value() > n? n:ui->spinBox_M->value();
	nmCalc pnm = pnm_calc(n,m);
	long long count = 0;
	while (pnm.next() && isVisible())
	{
		const int * res = pnm.currResult();
		//象征性输出一些
		if (count % 1000==0)
		{
			QString msg = QString("P(%1,%2).%3=").arg(n).arg(m).arg(count);
			for (int i=0;i<m;++i)
			{
				if (i) msg += ",";
				msg += QString("%1").arg(res[i]);
			}
			showMsg(msg);
			QCoreApplication::processEvents();
		}
		++count;
	}

}


void DlgCT::on_pushButton_CNM_clicked()
{
	QSettings settings(QCoreApplication::applicationFilePath()+".ini",QSettings::IniFormat);
	settings.setValue("ui/spinBox_N",ui->spinBox_N->value());
	settings.setValue("ui/spinBox_M",ui->spinBox_M->value());
	const int n = ui->spinBox_N->value();
	const int m = ui->spinBox_M->value() > n? n:ui->spinBox_M->value();
	nmCalc cnm = cnm_calc(n,m);
	long long count = 0;
	while (cnm.next() && isVisible())
	{
		const int * res = cnm.currResult();
		//象征性输出一些
		if (count % 10==0)
		{
			QString msg = QString("C(%1,%2).%3=").arg(n).arg(m).arg(count);
			for (int i=0;i<m;++i)
			{
				if (i) msg += ",";
				msg += QString("%1").arg(res[i]);
			}
			showMsg(msg);
			QCoreApplication::processEvents();
		}
		++count;
	}
}

