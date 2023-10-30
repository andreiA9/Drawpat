// local project headers
// ----------------------
#include "ImageEditor.h"
#include "EditorModule.h"

// standard C/C++ headers
// ----------------------
#include <QtWidgets>

ImageEditor::ImageEditor(Events *events, PaintingManager* paintingManager, QWidget *parent)
    : m_events(events), m_paintingManager(paintingManager)
{
    Q_ASSERT(events);

    setAttribute(Qt::WA_StaticContents);
    m_penWidth = 1;
    m_penColor = Qt::blue;
}

void ImageEditor::setPenColor(const QColor &newColor)
{
    m_penColor = newColor;
}

void ImageEditor::setPenWidth(int newWidth)
{
    m_penWidth = newWidth;
}

void ImageEditor::clearImage()
{
    m_paintingManager->clearImage();
    update();
}

void ImageEditor::mouseDoubleClickEvent(QMouseEvent *event)
{
    // for tests...
}

void ImageEditor::mousePressEvent(QMouseEvent *event)
{
    PaintEvent paintEvent = m_events->getCurrentEvent();
    if (event->button() == Qt::LeftButton)
    {
        if (paintEvent == PaintEvent::Drawing)
        {
            m_lastDrawingPoint = event->pos();
        }
        else if ((paintEvent == PaintEvent::Selection)
                 || (paintEvent == PaintEvent::SelectionMove))
        {
            bool resetToPreviousEvent;
            m_paintingManager->rectSelectionMousePressEvent(event, paintEvent, resetToPreviousEvent);

            if (paintEvent == PaintEvent::SelectionMove)
            {
                if (resetToPreviousEvent)
                {
                    m_events->resetToPreviousEvent();
                }

                // AICI VERIFICI daca ai facut CLICK.pe SELECTIE>incat sa faci MOVE
                m_lastMovePoint = event->pos();
            }
        }
        else if (paintEvent == PaintEvent::Writing)
        {
            m_textPosition = event->pos();
        }
    }

//    update();
    repaint();
}

void ImageEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        PaintEvent paintEvent = m_events->getCurrentEvent();
        if (paintEvent == PaintEvent::Drawing)
        {
            drawLineTo(event->pos());
        }
        else if ((paintEvent == PaintEvent::Selection)
                 || (paintEvent == PaintEvent::SelectionMove))
        {
            switchToSelectCursor();
            m_paintingManager->rectSelectionMouseMoveEvent(event, paintEvent, m_lastMovePoint);

            if (paintEvent == PaintEvent::SelectionMove)
            {
                m_lastMovePoint = event->pos();
            }
        }
    }
}

void ImageEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        PaintEvent paintEvent = m_events->getCurrentEvent();
        if (paintEvent == PaintEvent::Drawing)
        {
            drawLineTo(event->pos());
            emit mouseReleased();
        }
        else if (paintEvent == PaintEvent::Selection)
        {
            m_events->setEventEnabled(PaintEvent::SelectionMove);
            m_paintingManager->copySelectedImage();
        }
    }
}

void ImageEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // INAINTE era
    // QRect dirtyRectangle = event->rect();
    QRect dirtyRectangle = QWidget::rect();

    if (m_events->getCurrentEvent() == PaintEvent::Selection)
    {
        m_paintingManager->paintSelectionOverImage(painter, dirtyRectangle);

        update();
    }
    else if (m_events->getCurrentEvent() == PaintEvent::SelectionMove)
    {
        m_paintingManager->paintMoveSelectionOverImage(painter, dirtyRectangle);

        update();
    }
    else if (m_events->getCurrentEvent() == PaintEvent::Rotation)
    {
        painter.drawImage(dirtyRectangle, m_paintingManager->getCurrentImage(), dirtyRectangle);
        QImage dstImg;
        rotateTo90Degrees(dstImg);

        painter.drawImage(dirtyRectangle, dstImg, dirtyRectangle);

        update();
    }
    else if (m_events->getCurrentEvent() == PaintEvent::Writing)
    {
        QString imageText = "Qt by\nDigia";
        m_paintingManager->paintText(painter, dirtyRectangle, m_textPosition, imageText);

        update();
    }
    else
    {
        m_paintingManager->paintImage(painter, dirtyRectangle);

        update();
    }
    painter.end();
}

void ImageEditor::processEvents()
{
    QWidget::update();
}

void ImageEditor::resizeEvent(QResizeEvent *event)
{
    const int WIDTH_PADDING = 50;
    const int HEIGHT_PADDING = 50;
    int width = QWidget::width();
    int height = QWidget::height();
    int imageWidth = m_paintingManager->getCurrentImage().width();
    int imageHeight = m_paintingManager->getCurrentImage().height();

    if (width > imageWidth || height > imageHeight)
    {
        int newWidth = qMax(width + WIDTH_PADDING, imageWidth);
        int newHeight = qMax(height + HEIGHT_PADDING, imageHeight);
        m_paintingManager->resizeImage(QSize(newWidth, newHeight));
        update();
    }

    QWidget::resizeEvent(event);
}

void ImageEditor::resizeCurrentImage()
{
    m_paintingManager->resizeImage(QWidget::size());
}

void ImageEditor::fillWithImage(const QImage& currentImage)
{
    m_paintingManager->fillWithImage(currentImage, QWidget::size());
    update();
}

void ImageEditor::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&m_paintingManager->getCurrentImage());
    painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(m_lastDrawingPoint, endPoint);

    int rad = (m_penWidth / 2) + 2;
    QWidget::update(QRect(m_lastDrawingPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    m_lastDrawingPoint = endPoint;
}

void ImageEditor::rotateTo90Degrees(QImage &dstImg)
{
    QMatrix matrix;
//        matrix.translate(+10.0, +20.0);
//    matrix.rotate(+15);

    /* EXPLICATIE
    there needs to be initial translation to do the rotation around the centre of the image RECTANGLE.
    Move it to the origin, rotate, then move it back. And remember, transformations are applied in
    reverse order from how you'd expect, given how you specify them in the code. */
    matrix.translate(dstImg.width() / 2.0 , dstImg.height() / 2.0);
    matrix.rotate(90);
    matrix.translate(-dstImg.width() / 2.0 , -dstImg.height() / 2.0);

    dstImg = m_paintingManager->getCurrentImage().transformed(matrix);

    // IDENTICA cu
//    painter.setMatrix(matrix);
//    painter.drawImage(dirtyRectangle, m_paintingManager->getImage(), dirtyRectangle);
}

void ImageEditor::switchToSelectCursor()
{
    if(isInsideWidget(*this))
    {
        QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));

    }
    else
    {
        QApplication::restoreOverrideCursor();
    }
}

bool ImageEditor::isInsideWidget(QWidget& widget)
{
    QRect widgetRect = widget.geometry();
    QPoint mousePos = QWidget::mapFromGlobal(QCursor::pos());
    return widgetRect.contains(mousePos);
}
