#include "lht_qt_opencv_conversion.h"

LhtQtOpencvConversion::LhtQtOpencvConversion(QObject *parent) : QObject(parent)
{

}


Mat LhtQtOpencvConversion::QImageToMat(const QImage &image, bool cloneImageData)
{
    Mat mat;
    switch (image.format())
    {
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            break;

        case QImage::Format_RGB32:
            mat = Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cvtColor(mat, mat, COLOR_RGBA2BGRA);
            break;

        case QImage::Format_RGB888:
            mat = Mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cvtColor(mat, mat, COLOR_RGB2BGR);
            break;

        default:
            QLOG_ERROR() << "Unsupported image format";
            break;
    }

    if (cloneImageData)
        return mat.clone();
    else
        return mat;
}

QImage LhtQtOpencvConversion::MatToQImage(const Mat &mat)
{
    QImage::Format format;
    switch (mat.type())
    {
        case CV_8UC4:
            format = QImage::Format_ARGB32;
            break;

        case CV_8UC3:
            format = QImage::Format_RGB888;
            break;

        default:
            qWarning() << "Unsupported matrix type";
            return QImage();
    }

    QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), format);
    return image.copy();
}

IplImage *LhtQtOpencvConversion::QImageToIplImage(const QImage &image)
{
    IplImage *iplImg = cvCreateImage(cvSize(image.width(), image.height()), IPL_DEPTH_8U, 3);

    for (int y = 0; y < image.height(); ++y)
    {
        const uchar* qImageLine = image.constScanLine(y);
        uchar* iplImgLine = reinterpret_cast<uchar*>(iplImg->imageData + y * iplImg->widthStep);
        memcpy(iplImgLine, qImageLine, image.bytesPerLine());
    }

    return iplImg;
}

QImage LhtQtOpencvConversion::IplImageToQImage(const IplImage *iplImg)
{
    QImage::Format format;
    switch (iplImg->nChannels)
    {
        case 1:
            format = QImage::Format_Grayscale8;
            break;

        case 3:
            format = QImage::Format_RGB888;
            break;

        default:
            qWarning() << "Unsupported IplImage format";
            return QImage();
    }

    QImage image(iplImg->width, iplImg->height, format);
    for (int y = 0; y < iplImg->height; ++y)
    {
        const uchar* iplImgLine = reinterpret_cast<const uchar*>(iplImg->imageData + y * iplImg->widthStep);
        uchar* qImageLine = image.scanLine(y);
        memcpy(qImageLine, iplImgLine, iplImg->widthStep);
    }

    return image;
}
