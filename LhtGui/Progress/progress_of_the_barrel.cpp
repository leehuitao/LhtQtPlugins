#include "progress_of_the_barrel.h"

#include <QPainter>

#define OuterRoundSize 150
#define InsideRoundSize 32
#define ProgressSize    5

ProgressOfTheBarrel::ProgressOfTheBarrel(QWidget *parent) :QLabel(parent)
{

}

void ProgressOfTheBarrel::paintEvent(QPaintEvent *)
{
    if(m_progress<0)
    {
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//设置圆滑绘制风格（抗锯齿）
    //定义矩形绘制区域
    QRectF outRect(0,0, OuterRoundSize, OuterRoundSize);//设置外圆大小
    QRectF inRect(ProgressSize,ProgressSize, OuterRoundSize-(ProgressSize*2), OuterRoundSize-(ProgressSize*2));//设定遮罩大小
    //转换需要绘出的值
    QConicalGradient con (115,115,m_progress-180);
    con.setColorAt(0.5,palette().window().color());
    con.setColorAt(0.75,Qt::green);

    //    painter.rotate(90);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#4e4e4e"));//无色
    painter.drawPie(outRect,0*16,360*16);//设置外部边框

    //Value为当前进度显示文字
    QFont f = QFont("Microsoft YaHei", 10, QFont::Bold);
    painter.setFont(f);
    painter.setPen(QColor("#555555"));

    QRect source(0,0,InsideRoundSize,InsideRoundSize);


    //画内圆，遮罩颜色为窗口颜色
    QLinearGradient linearGradient(107,214,107,8);
    //从点（45，5）开始到点（45，90）结束，确定一条直线
    linearGradient.setColorAt(((float(m_progress)/360)),QColor("#208a5d"));
    linearGradient.setColorAt(1,QColor("#222222"));
    painter.setBrush(linearGradient);
    painter.drawEllipse(inRect);
    QString valueStr = QString("%1%").arg(QString::number(int(m_progress/3.6)));
    painter.drawText(inRect, Qt::AlignCenter, valueStr);
    //painter.drawImage(QPointF((OuterRoundSize-InsideRoundSize) / 2, (OuterRoundSize-InsideRoundSize) / 2), m_image, source);

}
