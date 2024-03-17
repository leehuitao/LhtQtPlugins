#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LhtGui/TableView/table.h"

#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //高级线程测试
    m_lhtExamples.init();

    m_lhtExamples.recv(int(1), double(1), QString("1"));

    //数据库测试 如果需要请打开Pro文件中的      #DEFINES += BUILD_SQL  更换自己的lib dll 以及  include
    m_lhtExamples.initSql();

    //相机测试  如果需要请打开Pro文件中的       #DEFINES += BUILD_CAMERA  更换自己的lib dll 以及  include
    m_lhtExamples.initCamera();

    initProgress();

    initTableView();

    connect(ui->img_lab,&ShotLabel::signMouseRelease,this,&MainWindow::onMouseRelease);
    connect(ui->img_lab_2,&ShotPolygonLabel::signDrawPolygon,this,&MainWindow::slotDrawPolygon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTableView()
{
    Table * table = new Table(ui->widget);
    table->init();
    table->setFixedSize(QSize(350,350));
    table->show();
}

void MainWindow::initProgress()
{
    m_roundLabel = new SpinningRound(this);
    m_roundLabel->setImagePath("D:/3.png");
    m_roundLabel->resize(150,150);

    m_proressOfTheBarrel = new ProgressOfTheBarrel(this);
    m_proressOfTheBarrel->setImagePath("D:/3.png");
    m_proressOfTheBarrel->resize(150,150);
    m_proressOfTheBarrel->setGeometry(300,0,150,150);

    connect(&m_timer,&QTimer::timeout,[=]{
        m_progress += 3;
        if(m_progress == 360)
            m_progress = 0;
        m_roundLabel->setProgress(m_progress);
        m_proressOfTheBarrel->setProgress(m_progress);
    });
    m_timer.start(30);
}


void MainWindow::on_select_img_btn_clicked()
{
    //打开操作
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("open file"));
    if(!fileName.isEmpty()){
        ui->img_path->setText(fileName);
    }
    ui->img_lab->setImage(fileName);
    ui->img_lab_2->setImage(fileName);
    ui->img_merge_lab->setImagePath(fileName);
}

void MainWindow::onMouseRelease(QRect rect)
{
    ui->pos_text->append("X:"+QString::number(rect.x())+"Y:"+QString::number(rect.y())+"W:"+QString::number(rect.width())+"H:"+QString::number(rect.height()));
}

void MainWindow::slotDrawPolygon(QVector<QPointF> points)
{
    for(auto it : points){
        ui->pos_text->append("X:"+QString::number(it.x())+"Y:"+QString::number(it.y()));
    }
}

void MainWindow::on_rect_btn_clicked()
{
    ui->img_merge_lab->setDrawType(DrawRect);
}

void MainWindow::on_polygon_btn_clicked()
{
    ui->img_merge_lab->setDrawType(DrawPolygon);
}
