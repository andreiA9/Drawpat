// local project headers
// ----------------------
#include "ImageController.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

void ImageController::clearImage()
{
    m_image.fill(qRgb(255, 255, 255));
}

void ImageController::fillWithImage(const QImage& currentImage, const QSize& imageSize)
{
    QSize newSize = m_image.size().expandedTo(imageSize);
    resizeImage(newSize);
    m_image = currentImage;
}

void ImageController::resizeImage(const QSize &newSize)
{
    if (m_image.size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    m_image = newImage;
}

void ImageController::rectSelectionMousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                                   bool& resetToPreviousEvent)
{
    m_rectangleSelectionOperator.mousePressEvent(event, paintEvent, resetToPreviousEvent);
}

void ImageController::rectSelectionMouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                                                  QPoint& lastMovePoint)
{
    m_rectangleSelectionOperator.mouseMoveEvent(event, paintEvent, lastMovePoint);
}

void ImageController::copySelectedImage()
{
    m_rectangleSelectionOperator.copySelectedImage(m_image);
}

void ImageController::paintImage(QPainter& painter, QRect& dirtyRectangle)
{
    painter.drawImage(dirtyRectangle, m_image, dirtyRectangle);
}

void ImageController::paintSelectionOverImage(QPainter& painter, QRect& dirtyRectangle)
{
    painter.drawImage(dirtyRectangle, m_image, dirtyRectangle);
    // PEN-ul de mai jos<va determina cum sa iti arate MARGINILE.pentru RECTANGLE
    painter.setPen(QPen(QBrush(QColor(0, 0, 0, 180)), 1, Qt::DashLine));
    // VEZI ca BRUSH-ul de mai JOS<iti va COLORA RECTANGLE-ul.in INTERIOR
//    painter.setBrush(QBrush(QColor(255, 255, 255, 120)));

    painter.drawRect(m_rectangleSelectionOperator.getSelectionRect());

    // VEZI ca SELECTUL-ul de la EI are TRANSPARENCY = 0 = alphat
    // ESTE ECHIVALENT.cu FUNCTIA.de mai JOS
//     painter.fillRect(m_selectionRectangle, QBrush(QColor(128, 128, 255, 0)));
}

void ImageController::paintMoveSelectionOverImage(QPainter& painter, QRect& dirtyRectangle)
{
    painter.drawImage(dirtyRectangle, m_image, dirtyRectangle);
    painter.setPen(QPen(QBrush(QColor(0, 0, 0, 180)), 1, Qt::DashLine));
//    painter.setBrush(QBrush(QColor(255, 255, 255, 120)));

    // NU incerca sa schimbi
    // m_transformedRectangle->getSelectedRect() -> m_transformedRectangle->getTranslatedRect()
    // PENTRU ca este un BUG>incat nu iti mai merge SELECTIA
    painter.drawImage(m_rectangleSelectionOperator.getTransformedRect(),
                      m_rectangleSelectionOperator.getSelectedImage());
    painter.drawRect(m_rectangleSelectionOperator.getSelectionRect());
}

void ImageController::paintText(QPainter& painter, QRect& dirtyRectangle,
                                QPoint& m_textPosition, QString& imageText)
{
    painter.drawImage(dirtyRectangle, m_image, dirtyRectangle);
    painter.drawText(m_textPosition, imageText);
}
