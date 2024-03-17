#ifndef SHOTMERGELABEL_H
#define SHOTMERGELABEL_H

#include <QMap>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#define  labelw 480
#define  labelh 320
struct DetectArea {
    QVector<QRect>        rect;
    QVector<QPolygonF>    polygon;
};
enum ShotType{
    DrawRect    = 1,
    DrawPolygon = 2,
    DrawRound   = 3
};
class ShotMergeLabel : public QLabel
{
    Q_OBJECT


public:
    ShotMergeLabel(QWidget *wid = nullptr);

    void setDrawType(ShotType t){
        m_drawType =t;
    }

    void setImagePath(QString path){
        this->m_img = QImage(path).scaled(480,320);
        update();
    }

    void setImage(QImage img){
        this->m_img = img.scaled(480,320);
        update();
    }

    void setStartBuild(bool build){
        m_startbuild = build;
    }

    void setDetectArea(DetectArea r){
        m_allExistingArea = r;
        update();
    }

    DetectArea getDetectArea(){
        return m_allExistingArea;
    }


Q_SIGNALS:
    void signMouseRelease(QRect);

    void signUpdateArea(DetectArea);
protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);//鼠标抬起
    void paintEvent(QPaintEvent *event);
    //判断点和初始点是否需要闭合
    bool checkPFPDistance(int x, int y);
    void drawPolygon();
    void drawLine();
private:

    //--------------------通用变量-----------------
    QImage              m_img;
    bool                m_startbuild=true;
    ShotType            m_drawType;
    DetectArea          m_allExistingArea;
    //--------------------矩形变量-----------------
    QRect               m_rect;//当前编辑的矩形
    bool                m_build=false;
    int                 m_x;//矩形初始位置
    int                 m_y;
    //-------------------多边形变量-----------------
    //点位是否闭合
    bool                m_closed=false;
    QVector<QPointF>    m_currentPoint;
    QVector<QPointF>    m_uiList;
    QVector<QPointF>    m_realList;


};
#endif // SHOTMERGELABEL_H
