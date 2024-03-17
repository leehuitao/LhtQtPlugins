#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LhtExamples/lht_examples.h"
#include "LhtGui/DrawLine/shot_polygon_label.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTableView();

    void initProgress();
private slots:
    void on_select_img_btn_clicked();

    void onMouseRelease(QRect);

    void slotDrawPolygon(QVector<QPointF>);

    void on_rect_btn_clicked();

    void on_polygon_btn_clicked();
private:
    Ui::MainWindow *ui;

    LhtExamples m_lhtExamples;


    int                         m_progress = 0;

    QTimer                      m_timer;

    SpinningRound   *           m_roundLabel;

    ProgressOfTheBarrel *       m_proressOfTheBarrel;
};
#endif // MAINWINDOW_H
