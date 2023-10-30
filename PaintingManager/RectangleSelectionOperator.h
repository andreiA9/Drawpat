#ifndef RECTANGLE_SELECTION_H
#define RECTANGLE_SELECTION_H

#include "CommonTypes.h"

#include <QImage>
#include <QRect>
#include <QMouseEvent>

class RectangleSelectionOperator
{
public:
    RectangleSelectionOperator() {}

    inline const QRect& getTransformedRect() { return m_transformedRect; }

    inline const QRect& getSelectionRect() { return m_selectionRectangle; }

    inline const QImage& getSelectedImage() { return m_selectedImage; }

    void copySelectedImage(const QImage& sourceImage);

    void translate(int xDelta, int yDelta);

    void mousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                      bool& resetToPreviousEvent);

    void mouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                        QPoint& lastMovePoint);

private:
    QImage m_selectedImage;
    QRect m_selectionRectangle;
    QRect m_transformedRect;
};

#endif // RECTANGLE_SELECTION_H
