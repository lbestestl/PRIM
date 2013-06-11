#include "ImageEdit.h"

#include <QSize>
#include <QColor>
#include <QRgb>


ImageEdit::ImageEdit()
    : editing(false),
      isEdited(false)
{
    mImage = new QImage(QSize(540, 335), QImage::Format_ARGB32_Premultiplied);
}


ImageEdit::~ImageEdit()
{
    delete mImage;
}

void ImageEdit::openImage(QString filePath)
{
    mImage->load(filePath);
    *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
}


void ImageEdit::saveImage(QString filePath)
{
    mImage->save(filePath);
}


void ImageEdit::paint(QLabel& imageArea) {
    for (int i = startPoint.x(); i < endPoint.x(); i++) {
        for (int j = startPoint.y(); j < endPoint.y(); j++) {
            mImage->setPixel(i, j, qRgb(255, 255, 255));
        }
    }
    QPixmap preview;
    preview = preview.fromImage(*mImage);
    imageArea.setPixmap(preview);
    imageArea.update();
}



void ImageEdit::mousePressEvent(QMouseEvent *event, QLabel& imageArea)
{
    if(event->button() == Qt::LeftButton) {
        startPoint = endPoint = event->pos();
    }
    editing = true;
}


void ImageEdit::mouseMoveEvent(QMouseEvent *event, QLabel& imageArea)
{
    if(editing) {
        endPoint = event->pos();
    }
}


void ImageEdit::mouseReleaseEvent(QMouseEvent *event, QLabel& imageArea)
{
    if(editing) {
        if(event->button() == Qt::LeftButton) {
            paint(imageArea);
        }
        editing = false;
    }
}
