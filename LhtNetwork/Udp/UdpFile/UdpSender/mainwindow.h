#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./network/udp_thread.h"
#include "redraw_progress_bar.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFile_clicked();

    void on_sendFile_clicked();

private:
    Ui::MainWindow *ui;
    UdpThread * m_udpThread = nullptr;
    QString filePath;
};
#endif // MAINWINDOW_H
