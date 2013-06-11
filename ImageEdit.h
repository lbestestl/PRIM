#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H


#include <QImage>
#include <QMouseEvent>
#include <QLabel>


class ImageEdit
{
public:
    ImageEdit();
    ~ImageEdit();
    
    void openImage(QString);
    void saveImage(QString);
    void mosaicImage();
    void paint(QLabel&);
    void mousePressEvent(QMouseEvent *event, QLabel&);
    void mouseMoveEvent(QMouseEvent *event, QLabel&);
    void mouseReleaseEvent(QMouseEvent *event, QLabel&);
    
private:
    bool editing;
    bool isEdited;
    QPoint startPoint, endPoint;
    QImage *mImage,  /**< Main image. */
           mImageCopy; /**< Copy of main image, need for events. */
};

#endif // IMAGEEDIT_H
