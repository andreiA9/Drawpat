#ifndef PAINTING_MANAGER_H
#define PAINTING_MANAGER_H

// local project headers
// ----------------------
#include "ImageController.h"
#include "ImageText.h"

// standard C/C++ headers
// ----------------------

class PaintingManager
{
public:
    PaintingManager() {}

    inline QImage& getCurrentImage() { return m_imageController.getCurrentImage(); }

    void clearImage();

    void fillWithImage(const QImage& currentImage, const QSize& imageSize);

    void resizeImage(const QSize &newSize);

    // mouse events for the ImageController class
    void rectSelectionMousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                      bool& resetToPreviousEvent);

    void rectSelectionMouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                                     QPoint& lastMovePoint);

    void rectSelectionMouseReleaseEvent(QMouseEvent *event, PaintEvent paintEvent);

    void copySelectedImage();

    // painting functions
    void paintImage(QPainter& painter, QRect& dirtyRectangle);

    void paintSelectionOverImage(QPainter& painter, QRect& dirtyRectangle);

    void paintMoveSelectionOverImage(QPainter& painter, QRect& dirtyRectangle);

    void paintText(QPainter& painter, QRect& dirtyRectangle,
                   QPoint& m_textPosition, QString& imageText);

private:
    ImageController m_imageController;
    ImageText m_imageText;
};

#endif // PAINTING_MANAGER_H
