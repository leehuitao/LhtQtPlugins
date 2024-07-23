#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./network/udp_thread.h"
#include <QProgressBar>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(m_udpThread,&UdpThread::signNewProgress,ui->progressBar,&QProgressBar::setValue);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectFile_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory); // 设置只选择目录
    dialog.setOption(QFileDialog::ShowDirsOnly); // 设置只显示目录
    dialog.exec();

    QStringList selectedDirs = dialog.selectedFiles();
     if (!selectedDirs.isEmpty()) {
         QString selectedDir = selectedDirs.first();
         qDebug() << "Selected directory:" << selectedDir;
         ui->filePath->setText(selectedDir);
     }

}


void MainWindow::on_send_clicked()
{
    ui->send->setDisabled(1);
    if(m_udpThread == nullptr){
        m_udpThread = new UdpThread;
        connect(m_udpThread,&UdpThread::signNewProgress,this,[=](float ratio){
            ui->progressBar->setValue(ratio*100);

        });
    }

    m_udpThread->init("127.0.0.1",80802,"127.0.0.1",80801);
    m_udpThread->setFilePath(ui->filePath->text());
    m_udpThread->start();
}


void MainWindow::on_stopListen_clicked()
{
    ui->send->setEnabled(1);
    m_udpThread->setStop();
}

