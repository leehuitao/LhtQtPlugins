#ifndef REDRAWPROGRESSBAR_H
#define REDRAWPROGRESSBAR_H
#include <QLabel>
#include <QWidget>

class RedrawProgressBar:public QLabel
{
public:
    RedrawProgressBar(QWidget*parent = nullptr);
public:
    void init();
    void setValue(float);
protected:
    void paintEvent(QPaintEvent*event)override;
private:
    float m_ratio = 0;
    QLabel * m_txt;
    QLabel * m_progressBar;
};

#endif // REDRAWPROGRESSBAR_H
