#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Interface/computing_interface.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_dot_product_btn_clicked();

    void on_add_btn_clicked();

    void on_sub_btn_clicked();

    void on_mul_btn_clicked();

    void on_max_btn_clicked();

    void on_min_btn_clicked();

    void on_mean_btn_clicked();

    void on_sort_btn_clicked();

    void on_filp_btn_clicked();

    void on_fft_btn_clicked();

    void on_dft_btn_clicked();

    void on_normalize_btn_clicked();

    void on_init_btn_clicked();

    void on_vec_mul_btn_clicked();

    void on_max2_btn_clicked();

    void on_fft_init_btn_clicked();

    void on_dft_init_btn_clicked();

    void on_power_btn_clicked();

    void on_resample_btn_clicked();

    void on_filter_lp_btn_clicked();

    void on_filter_lp_init_btn_clicked();

    void on_resample_init_btn_clicked();

private:
    Ui::MainWindow *ui;
    ComputingInterface *interface;
    float testVec1[11]{1,2,-3,4,6,9,80,-500,-7777,15,-9999};
    float testVec2[11]{777,2,-555,4,9,-8974,80,-500,245777,-878000,-337789};
    float testVecResult[11]{0};

};
#endif // MAINWINDOW_H
