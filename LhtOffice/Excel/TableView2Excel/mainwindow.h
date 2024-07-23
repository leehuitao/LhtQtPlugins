#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "Excel/export_excel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTestTable();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //---------Excel线程--------
    ExportExcel m_deviceExportExcel;

    QStandardItemModel *m_device1Model;
};
#endif // MAINWINDOW_H
