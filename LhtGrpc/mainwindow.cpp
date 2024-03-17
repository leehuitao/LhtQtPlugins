
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_pushButton_2_clicked();
    on_pushButton_3_clicked();
    on_pushButton_4_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    server1.test();
}


void MainWindow::on_pushButton_2_clicked()
{
    server.initParameter("0.0.0.0:50051","localhost:50052");
    server.initRepository();
    server.setStart();
}


void MainWindow::on_pushButton_3_clicked()
{
    server1.initParameter("0.0.0.0:50052","localhost:50051");
    server1.initRepository();
    server1.setStart();
}


void MainWindow::on_pushButton_4_clicked()
{
    server.connectTo();
    server1.connectTo();

}

