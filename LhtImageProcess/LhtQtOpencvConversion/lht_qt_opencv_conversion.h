#ifndef LHTQTOPENCVCONVERSION_H
#define LHTQTOPENCVCONVERSION_H

#include <QObject>
#include <QImage>
#include "LhtLog/QsLog/QsLog.h"
#include "opencv2/opencv.hpp"
using namespace cv;

class LhtQtOpencvConversion : public QObject
{
    Q_OBJECT
public:
    explicit LhtQtOpencvConversion(QObject *parent = nullptr);

    Mat QImageToMat(const QImage &image, bool cloneImageData = true);
    QImage MatToQImage(const Mat &mat);
    IplImage *QImageToIplImage(const QImage &image);
    QImage IplImageToQImage(const IplImage *iplImg);
signals:

};

#endif // LHTQTOPENCVCONVERSION_H
