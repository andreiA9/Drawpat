#ifndef IMAGE_CONTOLLER_H
#define IMAGE_CONTOLLER_H

//#include "DocumentContainer.h"
#include "RectangleSelectionOperator.h"
#include "ShapeOperator.h"
#include "ShapeSharing.h"

#include <QImage>
#include <QPainter>

class ImageController
{
public:
    ImageController() {}

    inline QImage& getCurrentImage() { return m_image; }

    void clearImage();

    void fillWithImage(const QImage& currentImage, const QSize& imageSize);

    void resizeImage(const QSize &newSize);

    // mouse events for the RectangleSelection class
    void rectSelectionMousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                      bool& resetToPreviousEvent);

    void rectSelectionMouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                                     QPoint& lastMovePoint);

    void copySelectedImage();

    // painting functions
    void paintImage(QPainter& painter, QRect& dirtyRectangle);

    void paintSelectionOverImage(QPainter& painter, QRect& dirtyRectangle);

    void paintMoveSelectionOverImage(QPainter& painter, QRect& dirtyRectangle);

    void paintText(QPainter& painter, QRect& dirtyRectangle,
                   QPoint& m_textPosition, QString& imageText);

private:
    QImage m_image;
    RectangleSelectionOperator m_rectangleSelectionOperator;
    ShapeOperator m_shapeOperator;
    ShapeSharing m_shapeSharing;
};

#endif // IMAGE_CONTOLLER_H
