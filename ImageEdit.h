#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H


#include <QImage>


class ImageEdit
{
public:
    ImageEdit();
    
    void openImage(QString);
    void saveImage();
    void mosaicImage();
    
private:
    bool isEdited;
    QImage *mImage,  /**< Main image. */
           mImageCopy; /**< Copy of main image, need for events. */
};

#endif // IMAGEEDIT_H
