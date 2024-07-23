#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "define.h"
#include "redraw_progress_bar.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QByteArray a;
//    a.append('1');
//    a.append('2');
//    a.append('3');
//    a.resize(3);
//    FileInfo info(FILE_CMD_START,3,1,1,"123",a);

//    FileInfo info1(info.toByteArray());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectFile_clicked()
{
    filePath = QFileDialog::getOpenFileName(nullptr, "Select File");
      if (!filePath.isEmpty()) {
          ui->filePath->setText(filePath);
      }

}


void MainWindow::on_sendFile_clicked()
{
    ui->sendFile->setEnabled(0);
    ui->selectFile->setEnabled(0);
    ui->sendFile->setText(QStringLiteral("发送中"));
    filePath = ui->filePath->text();
    if (m_udpThread == nullptr) {
        m_udpThread = new UdpThread;
        
        connect(m_udpThread, &UdpThread::signNewProgress, this, [=](float ratio) {
            if (ratio == 1)
            {
                ui->sendFile->setEnabled(1);
                ui->selectFile->setEnabled(1);
                ui->sendFile->setText(QStringLiteral("发送"));
            }
            ui->label->setValue(ratio);
            });
    }
    m_udpThread->setFilePath(filePath);
    m_udpThread->init("127.0.0.1",80801,"127.0.0.1",80802);
    m_udpThread->start();
}

