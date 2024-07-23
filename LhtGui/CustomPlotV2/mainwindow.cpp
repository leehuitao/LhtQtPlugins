#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

const int dataLen = 16384;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initCustomPlot();

    timer = new QTimer;
    timer->setInterval(100);

    connect(timer,&QTimer::timeout,this,&MainWindow::slotTimeout);

    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCustomPlot()
{
    m_data = new xyData[dataLen];
    // 获取全局随机数生成器实例
    QRandomGenerator *generator = QRandomGenerator::global();
    for(int i = 0 ; i < dataLen ;i++){
        m_data[i].x = i;
        m_data[i].y = generator->bounded(1000);
    }
    QVBoxLayout *tu=new QVBoxLayout(ui->widget);
    m_plot = new QCustomPlot;
    tu->addWidget(m_plot);
    m_plot->setOpenGl(true);
    m_plot->addGraph();
    qDebug() << "opengl status:" << m_plot->openGl();

    m_plot->xAxis->setRange(0, 16384);
    m_plot->yAxis->setRange(0, 1000);
    // 刻度显示
    m_plot->xAxis->setTicks(true);
    m_plot->yAxis->setTicks(true);
    // 刻度值显示
    m_plot->xAxis->setTickLabels(true);
    m_plot->yAxis->setTickLabels(true);
    // 网格显示
    m_plot->xAxis->grid()->setVisible(true);
    m_plot->yAxis->grid()->setVisible(true);
    // 子网格显示
    m_plot->xAxis->grid()->setSubGridVisible(true);
    m_plot->yAxis->grid()->setSubGridVisible(true);
    // 右和上坐标轴、刻度值显示
    m_plot->xAxis->setVisible(true);
    m_plot->yAxis->setVisible(true);
    m_plot->xAxis->setTicks(true);
    m_plot->yAxis->setTicks(true);

    m_plot->xAxis->setBasePen(QPen(Qt::white));
    m_plot->xAxis->setTickPen(QPen(Qt::black));
    m_plot->xAxis->setTickLabelColor(Qt::black);

    m_plot->yAxis->setBasePen(QPen(Qt::white));
    m_plot->yAxis->setTickPen(QPen(Qt::black));
    m_plot->yAxis->setTickLabelColor(Qt::black);
    m_plot->graph(0)->setSmooth(true); //启用曲线平滑

    m_coreData = m_plot->graph(0)->data()->coreData();
    // 可能需要预分配容器内存，预分配内存仅需一次
    m_coreData->reserve(dataLen);

    m_coreData->resize(dataLen);
    m_plot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical); // 允许在X轴和Y轴上缩放
    m_plot->axisRect()->setRangeZoomAxes(m_plot->xAxis, m_plot->yAxis); // 设置可缩放的轴
    m_plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |QCP::iSelectLegend | QCP::iSelectPlottables);
    //只允许XY轴缩放
    m_plot->setOnlyAllowsXYZoom(1);

}

void MainWindow::slotTimeout()
{
    //逐点更新
    // for(int i = 0 ; i < dataLen ;i++){
    //     // 逐点更新 xi = 5.0;
    //     (*m_coreData)[i].key = i;

    //     // 逐点更新 yi = sin(5.0);
    //     (*m_coreData)[i].value = m_data[i].y;
    // }
    //一次更新  或者直接对m_coreData的y值进行修改可以更快一些
    memcpy((char*)m_coreData->data(), (char*)m_data, sizeof(double)*dataLen*2);
    m_plot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    m_plot->rescaleAxes();
    m_plot->replot();
}

