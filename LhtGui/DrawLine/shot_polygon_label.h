#ifndef SHOT_POLYGON_LABEL_H
#define SHOT_POLYGON_LABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#define  labelw 480
#define  labelh 320

class ShotPolygonLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ShotPolygonLabel(QWidget *parent = nullptr);
    void setImage(QString imgpath){
        imagrpath = imgpath;
        QImage  m = QImage(imgpath);//.scaled(300, 1200);
        img = m.scaled(labelw, labelh,Qt::KeepAspectRatio);
        sourcew = m.width();
        sourceh = m.height();
        scalew  = double(sourcew)/double(labelw);
        scaleh  = double(sourceh)/double(labelh);
        this->setMaximumSize(img.width(),img.height());
        update();
    }

    void setImage(QImage img){
        QImage  m = img;//.scaled(300, 1200);
        sourcew = m.width();
        sourceh = m.height();
        img = m.scaled(labelw, labelh,Qt::KeepAspectRatio);
        scalew  = double(sourcew)/double(labelw);
        scaleh  = double(sourceh)/double(labelh);
    }

signals:
    void signDrawPolygon(QVector<QPointF>);
public slots:

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);//鼠标抬起
    void paintEvent(QPaintEvent *event);

private:
    void drawLine();
    //判断点和初始点是否需要闭合
    bool checkPFPDistance(int x, int y);

    void drawPolygon();
private:
    int x;
    int y;
    int selectNumber = 1;
    QString imagrpath;
    QSize size;
    bool startbuild=true;
    //点位是否闭合
    bool closed=false;
    QPointF pointf;
    QVector<QPointF>    currentPoint;
    QVector<QPointF>    rlist;
    QVector<QPointF>    realList;
    QPolygonF           finalPoints;
    QImage img;
    int     sourcew;
    int     sourceh;
    double  scalew;
    double  scaleh;
};

#endif // SHOT_POLYGON_LABEL_H
