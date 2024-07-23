#include "center_widget.h"
#include "ui_center_widget.h"
#include "Gui/add_line_dialog.h"
CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterWidget)
{
    ui->setupUi(this);
}

CenterWidget::~CenterWidget()
{
    delete ui;
}

void CenterWidget::setDrawType(ShotType t)
{
    ui->label->setDrawType(t);
}

void CenterWidget::setImagePath(QString path)
{
    ui->label->setImagePath(path);
}

void CenterWidget::setImage(QImage img)
{
    ui->label->setImage(img);
}

void CenterWidget::setStartBuild(bool build)
{
    ui->label->setStartBuild(build);
}

void CenterWidget::setDetectArea(DetectArea r)
{
    ui->label->setDetectArea(r);
}

DetectArea CenterWidget::getDetectArea()
{
    return ui->label->getDetectArea();
}

void CenterWidget::on_draw_line_btn_clicked()
{
    ui->label->setDrawType(DrawLine);
}

void CenterWidget::on_draw_polygon_btn_clicked()
{
    ui->label->setDrawType(DrawPolygon);
}

void CenterWidget::on_draw_round_btn_clicked()
{
    ui->label->setDrawType(DrawRound);
}

void CenterWidget::on_draw_arc_line_btn_clicked()
{
    ui->label->setDrawType(DrawArcLine);
}

void CenterWidget::on_add_parallel_line_btn_clicked()
{
    AddLineDialog dis;
    if(dis.exec() == QDialog::Accepted){
        auto distance = dis.getDidtance();
        auto size = dis.getSize();
        ui->label->adddLine1(distance,size);
    }
//    ui->label->setDrawType(DrawRect);
}

void CenterWidget::on_draw_rect_btn_clicked()
{
    ui->label->setDrawType(DrawRect);
}

void CenterWidget::on_start_btn_clicked()
{
     ui->label->setStartBuild(1);
}
