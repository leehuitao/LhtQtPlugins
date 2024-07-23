#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_deviceExportExcel.start();
    connect(&m_deviceExportExcel,&ExportExcel::signExcelExportState,[=](int state){
        if(!state)
            ui->state_lab->setText(QString::fromLocal8Bit("文档导出进行中..."));
        else
            ui->state_lab->clear();
    });
    createTestTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTestTable()
{
    QStandardItemModel* model = new QStandardItemModel(this);

    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal, "姓名");
    model->setHeaderData(1,Qt::Horizontal, "年龄");
    model->setHeaderData(2,Qt::Horizontal, "性别");

    model->setRowCount(100);
    /*设置行字段名*/
    model->setRowCount(3);
    model->setHeaderData(0,Qt::Vertical, "记录");
    model->setHeaderData(1,Qt::Vertical, "记录");
    model->setHeaderData(2,Qt::Vertical, "记录");
    for(int i = 0 ; i < 3 ; i ++){
        model->setItem(i, 0, new QStandardItem(QString::number(qrand()%321)));
        model->setItem(i, 1, new QStandardItem(QString::number(qrand()%321)));
        model->setItem(i, 2, new QStandardItem(QString::number(qrand()%321)));
    }

    ui->tableView->setModel(model);
}


void MainWindow::on_pushButton_clicked()
{
    m_deviceExportExcel.Table2ExcelByHtml(ui->tableView,"Device");
}
