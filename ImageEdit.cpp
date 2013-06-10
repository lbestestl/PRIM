#include "ImageEdit.h"

#include <QSize>


ImageEdit::ImageEdit()
{
    mImage = new QImage(QSize(540, 335), QImage::Format_ARGB32_Premultiplied);
}


void ImageEdit::openImage(QString filePath)
{
    mImage->load(filePath);
    *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
}
