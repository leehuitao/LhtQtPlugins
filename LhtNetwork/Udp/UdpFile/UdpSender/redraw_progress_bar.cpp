#include "redraw_progress_bar.h"
#include "qboxlayout.h"
#include <QPainter>
#include <QPixmap>
RedrawProgressBar::RedrawProgressBar(QWidget*parent):QLabel(parent)
{
    init();
}

void RedrawProgressBar::init()
{
    QVBoxLayout *vbox = new QVBoxLayout;
    m_txt = new QLabel(this);
    m_txt->setAlignment(Qt::AlignCenter);
    m_txt->setText("当前进度:0%");
    m_progressBar = new QLabel(this);

    vbox->addWidget(m_txt);
    vbox->addWidget(m_progressBar);

    this->setLayout(vbox);
}

void RedrawProgressBar::setValue(float ratio)
{
    m_ratio = ratio;
    m_txt->setText(QString("当前进度:%1%").arg(ratio*100));
}

void RedrawProgressBar::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap(m_progressBar->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.drawRect(0,0,m_progressBar->width()*m_ratio,m_progressBar->height());
    m_progressBar->setPixmap(pixmap);

    //Pen 用于定义边框属性 Brush 用于定义填充属性时
}
