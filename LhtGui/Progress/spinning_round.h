#ifndef SPINNINGROUND_H
#define SPINNINGROUND_H

#include <QLabel>
#include <QMutex>
#include <QObject>

class SpinningRound : public QLabel
{
    Q_OBJECT
public:
    explicit SpinningRound(QWidget *parent = nullptr);

    void setImagePath(QString path){
        m_image = QImage(path).copy();
    }

    void setProgress(int progress){
        m_progress = progress;
        update();
    }

    void paintEvent(QPaintEvent *);
signals:

public slots:

private:
    QString m_imagePath;
    int     m_progress;
    QImage  m_image;
    QMutex  m_mu;
};

#endif // SPINNINGROUND_H
