#ifndef LHTQTIMAGEFUNC_H
#define LHTQTIMAGEFUNC_H

#include <QImage>
#include <QObject>

class LhtQtImageFunc : public QObject
{
    Q_OBJECT
public:
    explicit LhtQtImageFunc(QObject *parent = nullptr);

    //水平翻转
    QImage horFilp(QImage image)
    {
        return image.mirrored(true, false);
    }
    //垂直翻转
    QImage verFilp(QImage image)
    {
        return  image.mirrored(false, true);
    }
    //顺时针旋转
    QImage clockwise(QImage image)
    {
        QMatrix matrix;
        matrix.rotate(90.0);
        return  image.transformed(matrix,Qt::FastTransformation);
    }
    //逆时针旋转
    QImage anticlockwise(QImage image)
    {
        QMatrix matrix;
        matrix.rotate(-90.0);
        return  image.transformed(matrix,Qt::FastTransformation);
    }

signals:

};

#endif // LHTQTIMAGEFUNC_H
