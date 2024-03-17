#include "shot_polygon_label.h"

#include <QPainter>

ShotPolygonLabel::ShotPolygonLabel(QWidget *parent) : QLabel(parent)
{

}

void ShotPolygonLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        //先检测是否闭合
        closed = checkPFPDistance(event->x(),event->y());
    }else{
        closed = 0;
        rlist.clear();
        finalPoints.clear();
        currentPoint.clear();
    }
    update();
}


void ShotPolygonLabel::mouseMoveEvent(QMouseEvent *e)
{

}

void ShotPolygonLabel::mouseReleaseEvent(QMouseEvent *e)
{

}

void ShotPolygonLabel::paintEvent(QPaintEvent *event)
{
    if(startbuild){
        QPainter painter(this);  //QPainter对象
        QPen pen; //画笔
        pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush); //添加画刷
        painter.drawImage(0,0,img);
        // if(closed){
        //    drawPolygon();
        //}else{
        drawLine();
        // }
    }
}

void ShotPolygonLabel::drawLine()
{
    QPainter painter(this);  //QPainter对象
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    painter.drawPoints(currentPoint);
    pen.setWidth(1);
    painter.setPen(pen);
    if(!closed){
        for (int i = 0;i < rlist.size()-1; i++) {
            QLineF line(rlist.at(i),rlist.at(i+1));
            painter.drawLine(line);
        }
    }else {
        for (int i = 0;i < rlist.size(); i++) {
            if(i != rlist.size()-1){
                QLineF line(rlist.at(i),rlist.at(i+1));
                painter.drawLine(line);
            }else{
                QLineF line(rlist.at(i),rlist.at(0));
                painter.drawLine(line);
                QPolygonF ploygon(rlist);
            }

        }
    }

}

bool ShotPolygonLabel::checkPFPDistance(int x, int y)
{
    //至少有三个点的时候允许闭合
    if(rlist.size()>=3){
        auto point = rlist.first();
        auto powx = pow(x-point.x(),2);
        auto powy = pow(y-point.y(),2);
        //两点间的距离小于3则闭合
        if(sqrt(powx+powy)<10){
            signDrawPolygon(rlist);
            for(auto it : rlist){
                realList.append(QPointF(it.x()/scalew,it.y()/scaleh));
            }
            finalPoints = QPolygonF(realList);
            return 1;
        } else{
            QPointF p(x,y);
            rlist.append(p);
            currentPoint.append(p);
            return 0;
        }
    }else{
        QPointF p(x,y);
        rlist.append(p);
        currentPoint.append(p);
        return 0;
    }
}

void ShotPolygonLabel::drawPolygon()
{
    QPainter painter(this);  //QPainter对象
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    painter.drawPolygon(finalPoints,Qt::OddEvenFill);

}
