#include <QtWidgets>
#include "DrawingArea.h"

DrawingView::DrawingView(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    m_isModified = false;
    m_isDrawingAllowed = false;
    m_penWidth = 1;
    m_penColor = Qt::blue;
}

bool DrawingView::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    m_image = loadedImage;
    m_isModified = false;
    update();
    return true;
}

bool DrawingView::saveImage(QString &fileName, const char *fileFormat)
{
    QImage visibleImage = m_image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat))
    {
        m_isModified = false;
        return true;
    }
    else
    {
        return false;
    }
}

void DrawingView::setPenColor(const QColor &newColor)
{
    m_penColor = newColor;
}

void DrawingView::setPenWidth(int newWidth)
{
    m_penWidth = newWidth;
}

void DrawingView::clearImage()
{
    m_image.fill(qRgb(255, 255, 255));
    m_isModified = true;
    update();
}

void DrawingView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lastPoint = event->pos();
        m_isDrawingAllowed = true;
    }
}

void DrawingView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawingAllowed)
    {
        drawLineTo(event->pos());
    }
}

void DrawingView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawingAllowed)
    {
        drawLineTo(event->pos());
        m_isDrawingAllowed = false;
    }
}

void DrawingView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void DrawingView::resizeEvent(QResizeEvent *event)
{
    const int WIDTH_PADDING = 50;
    const int HEIGHT_PADDING = 50;
    int width = QWidget::width();
    int height = QWidget::height();
    int imageWidth = m_image.width();
    int imageHeight = m_image.height();

    if (width > imageWidth || height > imageHeight)
    {
        int newWidth = qMax(width + WIDTH_PADDING, imageWidth);
        int newHeight = qMax(height + HEIGHT_PADDING, imageHeight);
        resizeImage(&m_image, QSize(newWidth, newHeight));
        update();
    }

    QWidget::resizeEvent(event);
}

void DrawingView::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&m_image);
    painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(m_lastPoint, endPoint);
    m_isModified = true;

    int rad = (m_penWidth / 2) + 2;
    update(QRect(m_lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    m_lastPoint = endPoint;
}

void DrawingView::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
