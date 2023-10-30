// local project headers
// ----------------------
#include "PaintingManager.h"

// standard C/C++ headers
// ----------------------

void PaintingManager::clearImage()
{
    m_imageController.clearImage();
}

void PaintingManager::fillWithImage(const QImage& currentImage, const QSize& imageSize)
{
    m_imageController.fillWithImage(currentImage, imageSize);
}

void PaintingManager::resizeImage(const QSize &newSize)
{
    m_imageController.resizeImage(newSize);
}

void PaintingManager::rectSelectionMousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                                   bool& resetToPreviousEvent)
{
    m_imageController.rectSelectionMousePressEvent(event, paintEvent, resetToPreviousEvent);
}

void PaintingManager::rectSelectionMouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                                                  QPoint& lastMovePoint)
{
    m_imageController.rectSelectionMouseMoveEvent(event, paintEvent, lastMovePoint);
}

void PaintingManager::copySelectedImage()
{
    m_imageController.copySelectedImage();
}

void PaintingManager::paintImage(QPainter& painter, QRect& dirtyRectangle)
{
    m_imageController.paintImage(painter, dirtyRectangle);
}

void PaintingManager::paintSelectionOverImage(QPainter& painter, QRect& dirtyRectangle)
{
    m_imageController.paintSelectionOverImage(painter, dirtyRectangle);
}

void PaintingManager::paintMoveSelectionOverImage(QPainter& painter, QRect& dirtyRectangle)
{
    m_imageController.paintMoveSelectionOverImage(painter, dirtyRectangle);
}

void PaintingManager::paintText(QPainter& painter, QRect& dirtyRectangle,
                                QPoint& m_textPosition, QString& imageText)
{
    m_imageController.paintText(painter, dirtyRectangle, m_textPosition, imageText);
}
