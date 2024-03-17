#include "shot_merge_label.h"

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

        }
    }else{
        int _x = event->x();
        int _y = event->y();
        m_closed = 0;
        m_uiList.clear();
        m_currentPoint.clear();
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
    }
}

void ShotMergeLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && m_drawType == DrawRect){
        m_allExistingArea.rect.append(m_rect);
        signUpdateArea(m_allExistingArea);
        m_build = false;
    }

}

void ShotMergeLabel::paintEvent(QPaintEvent *event)
{
    if(m_startbuild){
        QPainter painter(this);  //QPainter对象
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

        if(m_drawType == DrawRect){
            painter.drawRect(m_rect.x(),m_rect.y(),m_rect.width(),m_rect.height()); //绘制矩形
        }else if(m_drawType == DrawPolygon){
            drawLine();
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
            m_currentPoint.append(p);
            return 0;
        }
    }else{
        QPointF p(x,y);
        m_uiList.append(p);
        m_currentPoint.append(p);
        return 0;
    }
}


void ShotMergeLabel::drawPolygon()
{
    QPainter painter(this);  //QPainter对象
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
}

void ShotMergeLabel::drawLine()
{
    QPainter painter(this);  //QPainter对象
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));  //设置画笔颜色
    pen.setWidth(5);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //添加画刷
    painter.drawPoints(m_currentPoint);
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
