#ifndef DLGCT_H
#define DLGCT_H

#include <QDialog>
#include <QStandardItemModel>
#include <atomic>
#include "filedealer.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class DlgCT;
}
QT_END_NAMESPACE

class DlgCT : public QDialog
{
	Q_OBJECT

public:
	DlgCT(QWidget *parent = nullptr);
	~DlgCT();
protected:
	void timerEvent(QTimerEvent * evt);
private slots:
	void on_toolButton_file_clicked();
	void on_pushButton_file_clicked();
	void on_pushButton_normal_clicked();

	void on_pushButton_thread_clicked();

	void on_pushButton_PNM_clicked();

	void on_pushButton_CNM_clicked();

public slots:
	void showMsg(QString);
protected:
	FileTask dealFile(QString filename);
private:
	int m_nTimerID = 0;
	std::atomic<int> m_nBusy;
	Ui::DlgCT *ui;
	QStandardItemModel * m_pMsgMod;
signals:
	void shootMsg(QString);

};
#endif // DLGCT_H
