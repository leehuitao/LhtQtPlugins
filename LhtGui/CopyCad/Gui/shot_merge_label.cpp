#include "shot_merge_label.h"
#include <math.h>
#include <Windows.h>
#include <cmath>  // For math functions
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ShotMergeLabel::ShotMergeLabel(QWidget *wid)
{

}

//鼠标按下
void ShotMergeLabel::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton){
        if(m_drawType == DrawRect){
            m_x = event->x();
            m_y = event->y();
            m_build = true;
        }else if(m_drawType == DrawPolygon){
            //先检测是否闭合
            m_closed = checkPFPDistance(event->x(),event->y());

        }else if(m_drawType == DrawLine){
            m_x = event->x();
            m_y = event->y();
            m_uiList.append(QPointF(m_x,m_y));
        }else if(m_drawType == DrawArcLine){
            m_build = true;
            if (m_isArcBeingDrawn) {
                // 第二次点击，设置结束点并固定弧线
                m_arcEndPoint = event->pos();
                m_isArcBeingDrawn = false;
                // 将弧线添加到某个存储结构中
                // 例如：
                //                m_allExistingArea.arcLine.append(...);
            } else {
                // 第一次点击，设置起点
                m_arcStartPoint = event->pos();
                m_arcEndPoint = event->pos(); // 初始化结束点
                m_isArcBeingDrawn = true;
            }
            update();
        }else if(m_drawType == CopyNewLine){

        }else if(m_drawType == DrawRound){
            m_build = true;
            m_center = event->pos();
            m_radius = 0;
        }
    }else{
        int _x = event->x();
        int _y = event->y();
        m_closed = 0;
        m_uiList.clear();
        m_currentPoints.clear();
        for(int i = 0 ; i <  m_allExistingArea.rect.size() ; i++){
            if(m_allExistingArea.rect.at(i).contains(_x,_y)){
                m_rect = QRect();
                qDebug()<<"1 size = "<<m_allExistingArea.rect.size();
                m_allExistingArea.rect.remove(i);
                qDebug()<<"2 size = "<<m_allExistingArea.rect.size();
                signUpdateArea(m_allExistingArea);
                qDebug()<<__LINE__;
                break;
            }
        }
        for(int i = 0 ; i <  m_allExistingArea.polygon.size() ; i++){
            QPointF p(_x,_y);
            qDebug()<<__LINE__;
            if(m_allExistingArea.polygon.at(i).containsPoint(p,Qt::OddEvenFill)){
                m_rect = QRect();
                m_allExistingArea.polygon.remove(i);
                signUpdateArea(m_allExistingArea);
                qDebug()<<__LINE__;
                break;
            }
        }

    }
    update();
}

void ShotMergeLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(m_drawType == DrawRect && m_build){
        QRect r(m_x,m_y,e->x()-m_x,e->y()-m_y);
        m_rect = r;
        update();
    }else if (m_drawType == DrawRound && m_build) {
        QPointF currentPos = e->pos();
        m_radius = QLineF(m_center, currentPos).length();
        update();
    }else if(m_drawType == DrawArcLine && m_build){
        // 更新结束点
        m_arcEndPoint = e->pos();
        // 动态更新弧线的矩形边界
        m_arcRect.setTopLeft(m_arcStartPoint);
        m_arcRect.setWidth(m_arcEndPoint.x() - m_arcStartPoint.x());
        m_arcRect.setHeight(m_arcEndPoint.y() - m_arcStartPoint.y());
        m_arcRect = m_arcRect.normalized();
        update();
    }
}

void ShotMergeLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && m_drawType == DrawRect){
        m_allExistingArea.rect.append(m_rect);
        signUpdateArea(m_allExistingArea);
        m_build = false;
    }
    if(e->button() == Qt::LeftButton && m_drawType == DrawRound){
        m_allExistingArea.round.append(LhtRounds{m_center,m_radius});
        m_build = false;
    }
    //    if(e->button() == Qt::LeftButton && m_drawType == DrawArcLine){
    //        QPainterPath path;
    //        path.moveTo(m_arcStart);
    //        // 假设这里的弧线半径和角度都是预定义的
    //        QRectF rectangle(m_arcStart.x() - 100, m_arcStart.y() - 100, 200, 200);
    //        double startAngle = 0; // 起始角度
    //        double spanAngle = 180; // 跨度角度
    //        path.arcTo(rectangle, startAngle, spanAngle);
    //        m_allExistingArea.arcLine.append(path);
    //        m_build = false;
    //    }
}

void ShotMergeLabel::paintEvent(QPaintEvent *event)
{
    if(m_startbuild){
        QPainter painter(this);  //QPainter对象
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
        QPen pen; //画笔
        pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush); //添加画刷
        painter.drawImage(0,0,m_img);
        //绘制已经有的轮廓
        for(auto it : m_allExistingArea.rect){
            painter.drawRect(it);
        }
        for(auto it : m_allExistingArea.polygon){
            painter.drawPolygon(it); //绘制多边形
        }
        for(auto it : m_allExistingArea.line){
            painter.drawLine(it);
        }
        for(auto it : m_allExistingArea.round){
            painter.drawEllipse(it.center,it.radius,it.radius);
        }
        for(auto it : m_allExistingArea.arcLine){
            painter.drawPath(it);
        }
        if(m_drawType == DrawRect){
            painter.drawRect(m_rect.x(),m_rect.y(),m_rect.width(),m_rect.height()); //绘制矩形
        }else if(m_drawType == DrawPolygon){
            drawLine();
        }else if(m_drawType == DrawRound){
            painter.drawEllipse(m_center, m_radius, m_radius);
        }else if(m_drawType == DrawLine){
            drawLine1();
        }else if (m_drawType == DrawArcLine) {
            drawLine2();
        }else if(m_drawType == CopyNewLine){
            //            drawLine();
        }
    }


}

bool ShotMergeLabel::checkPFPDistance(int x, int y)
{
    //至少有三个点的时候允许闭合
    if(m_uiList.size()>=3){
        auto point = m_uiList.first();
        auto powx = pow(x-point.x(),2);
        auto powy = pow(y-point.y(),2);
        //两点间的距离小于10则闭合
        if(sqrt(powx+powy)<20){
            m_allExistingArea.polygon.append(QPolygonF(m_uiList));
            signUpdateArea(m_allExistingArea);
            m_uiList.clear();
            return 1;
        } else{
            QPointF p(x,y);
            m_uiList.append(p);
            m_currentPoints.append(p);
            return 0;
        }
    }else{
        QPointF p(x,y);
        m_uiList.append(p);
        m_currentPoints.append(p);
        return 0;
    }
}


void ShotMergeLabel::drawPolygon()
{
    QPainter painter(this);  //QPainter对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
}

void ShotMergeLabel::drawLine()
{
    QPainter painter(this);  //QPainter对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    painter.drawPoints(m_currentPoints);
    pen.setWidth(3);
    painter.setPen(pen);
    if(!m_closed){
        for (int i = 0;i < m_uiList.size()-1; i++) {
            QLineF line(m_uiList.at(i),m_uiList.at(i+1));
            painter.drawLine(line);
        }
    }else {
        for (int i = 0;i < m_uiList.size(); i++) {
            if(i != m_uiList.size()-1){
                QLineF line(m_uiList.at(i),m_uiList.at(i+1));
                painter.drawLine(line);
            }else{
                QLineF line(m_uiList.at(i),m_uiList.at(0));
                painter.drawLine(line);
                QPolygonF ploygon(m_uiList);
            }

        }
    }

}

void ShotMergeLabel::drawLine1()
{
    QPainter painter(this);  //QPainter对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    painter.drawPoints(m_currentPoints);
    pen.setWidth(3);
    painter.setPen(pen);
    if (m_uiList.size()==2) {
        QLineF line(m_uiList.at(0),m_uiList.at(1));
        painter.drawLine(line);
        m_currentLine = line;
        m_allExistingArea.line.append(line);
        m_uiList.clear();
    }
}

void ShotMergeLabel::adddLine1(int len, int size)
{
    QPainter painter(this);  //QPainter对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    pen.setWidth(3);
    painter.setPen(pen);
    for(int i = 0 ; i < size ; i++){
        QLineF line(m_currentLine.x1(),m_currentLine.y1() + len*(i+1),m_currentLine.x2(),m_currentLine.y2() + len*(i+1));
        m_allExistingArea.line.append(line);
    }
    update();
}
//计算两个点之间的角度
double calculateAngle(const QPointF& p1, const QPointF& p2) {
    // 计算两点之间的向量差
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    // 计算弧度
    double radians = atan2(dy, dx);

    // 转换为度
    double degrees = radians * 180.0 / M_PI;

    // 返回角度值
    return degrees;
}
void ShotMergeLabel::drawLine2()
{
    QPainter painter(this);  //QPainter对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //抗锯齿和使用平滑转换算法
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    // 假设圆心位置，这个应该通过计算得到
    QPointF centerPoint((m_arcStartPoint.x() + m_arcEndPoint.x())/2, (m_arcStartPoint.y() + m_arcEndPoint.y())/2);

    // 计算半径
    double radius = sqrt(pow(m_arcStartPoint.x() - centerPoint.x(), 2) + pow(m_arcStartPoint.y() - centerPoint.y(), 2));
    //计算矩形的角度
    auto ang = calculateAngle(m_arcStartPoint,m_arcEndPoint);
    // 计算矩形
    QRectF rect(centerPoint.x() - radius, centerPoint.y() - radius  , radius * 2, radius * 2 );
    // 应用旋转变换
    QTransform transform;
    transform.translate(rect.center().x(), rect.center().y());
    transform.rotate(ang);
    transform.translate(-rect.center().x(), -rect.center().y());
    painter.setTransform(transform);

    // 计算角度
    double startAngle = 0;//atan2(m_arcStartPoint.y() - centerPoint.y(), m_arcStartPoint.x() - centerPoint.x()) * 180 / M_PI;
    double endAngle = 180;//atan2(m_arcEndPoint.y() - centerPoint.y(), m_arcEndPoint.x() - centerPoint.x()) * 180 / M_PI;

    // 转换为Qt的角度单位
    int startAngle16 = static_cast<int>(startAngle * 16);
    int spanAngle16 = static_cast<int>((endAngle - startAngle) * 16);
    // 绘制矩形和弧线
//    painter.drawRect(rect);
    // 绘制弧线
    painter.drawArc(rect, startAngle16, spanAngle16);
}
