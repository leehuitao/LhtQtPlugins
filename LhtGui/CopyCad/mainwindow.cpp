#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_centerWidget = new CenterWidget;
    this->setCentralWidget(m_centerWidget);
    m_centerWidget->setDrawType(DrawPolygon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

