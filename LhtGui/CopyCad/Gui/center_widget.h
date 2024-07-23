#ifndef CENTER_WIDGET_H
#define CENTER_WIDGET_H

#include <QWidget>
#include "Gui/shot_merge_label.h"
namespace Ui {
class CenterWidget;
}

class CenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = nullptr);
    ~CenterWidget();
    void setDrawType(ShotType t);

    void setImagePath(QString path);

    void setImage(QImage img);

    void setStartBuild(bool build);

    void setDetectArea(DetectArea r);

    DetectArea getDetectArea();
signals:
    void addLine(int,int);
private slots:
    void on_draw_line_btn_clicked();

    void on_draw_polygon_btn_clicked();

    void on_draw_round_btn_clicked();

    void on_draw_arc_line_btn_clicked();

    void on_add_parallel_line_btn_clicked();

    void on_draw_rect_btn_clicked();

    void on_start_btn_clicked();

private:
    Ui::CenterWidget *ui;
};

#endif // CENTER_WIDGET_H
