#include "RectangleSelectionOperator.h"

static bool isInsideRectangle(QPoint mousePosition, QRect& rectangle)
{
    return rectangle.contains(mousePosition);
}

void RectangleSelectionOperator::copySelectedImage(const QImage& sourceImage)
{
    m_selectedImage = sourceImage.copy(m_selectionRectangle);
}

void RectangleSelectionOperator::translate(int xDelta, int yDelta)
{
    m_transformedRect = m_selectionRectangle;
    QPoint selectionTopLeft = m_transformedRect.topLeft();
    QPoint selectionBottomRight = m_transformedRect.bottomRight();
    QPoint translatedTopLeft(selectionTopLeft.x() + xDelta, selectionTopLeft.y() + yDelta);
    QPoint translatedBottomRight(selectionBottomRight.x() + xDelta, selectionBottomRight.y() + yDelta);
    // AI BUG AICI daca INCERCI sa CREEZI o
    // VARIABILA.noua
    // QRect m_translatedRect;
    m_transformedRect.setTopLeft(translatedTopLeft);
    m_transformedRect.setBottomRight(translatedBottomRight);
}

void RectangleSelectionOperator::mousePressEvent(QMouseEvent *event, PaintEvent paintEvent,
                                           bool& resetToPreviousEvent)
{
    resetToPreviousEvent = false;
    if (paintEvent == PaintEvent::Selection)
    {
        // ASTA este SELECTION
        m_selectionRectangle.setTopLeft(event->pos());
        m_selectionRectangle.setBottomRight(event->pos());
    }
    else if (paintEvent == PaintEvent::SelectionMove)
    {
        // check to see if the rectangle needs to be invalidated
        if (!isInsideRectangle(event->pos(), m_selectionRectangle))
        {
            resetToPreviousEvent = true;
            // invalidate rectangle
            m_selectionRectangle.setTopLeft(QPoint(0, 0));
            m_selectionRectangle.setBottomRight(QPoint(0, 0));
        }
    }
}

void RectangleSelectionOperator::mouseMoveEvent(QMouseEvent *event, PaintEvent paintEvent,
                                          QPoint& lastMovePoint)
{
    if (paintEvent == PaintEvent::Selection)
    {
        m_selectionRectangle.setBottomRight(event->pos());
    }
    else if (paintEvent == PaintEvent::SelectionMove)
    {
        // !!!!
        // BUG: la MOVE<SELECTIA are[WIDTH + 1/HEIGHT + 1]fata de ORIGINAL
        int deltaX = event->pos().x() - lastMovePoint.x();
        int deltaY = event->pos().y() - lastMovePoint.y();
        m_selectionRectangle.translate(deltaX, deltaY);
        translate(deltaX, deltaY);
    }
}
