#include <QtWidgets>
#include "DrawingArea.h"

DrawingArea::DrawingArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    m_isModified = false;
    m_isDrawingAllowed = false;
    m_penWidth = 1;
    m_penColor = Qt::blue;
}

void DrawingArea::setFileName(QString fileName)
{
    m_fileName = fileName;
}

bool DrawingArea::openImage(const QString &fileName)
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

bool DrawingArea::saveImage(const char *fileFormat)
{
    QImage visibleImage = m_image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(m_fileName, fileFormat))
    {
        m_isModified = false;
        return true;
    }
    else
    {
        return false;
    }
}

void DrawingArea::setPenColor(const QColor &newColor)
{
    m_penColor = newColor;
}

void DrawingArea::setPenWidth(int newWidth)
{
    m_penWidth = newWidth;
}

void DrawingArea::clearImage()
{
    m_image.fill(qRgb(255, 255, 255));
    m_isModified = true;
    update();
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lastPoint = event->pos();
        m_isDrawingAllowed = true;
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawingAllowed)
    {
        drawLineTo(event->pos());
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawingAllowed)
    {
        drawLineTo(event->pos());
        m_isDrawingAllowed = false;
    }
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void DrawingArea::resizeEvent(QResizeEvent *event)
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

void DrawingArea::drawLineTo(const QPoint &endPoint)
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

void DrawingArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

bool DrawingArea::saveFile(const QByteArray format)
{
    QString initialPath = QDir::currentPath() + '/' + m_fileName + '.' + format;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    initialPath,
                                                    tr("%1 Files (*.%2);; All FIles(*)")
                                                    .arg(QString::fromLatin1(format.toUpper()))
                                                    .arg(QString::fromLatin1(format)));

    m_fileName = fileName;

    if (fileName.isEmpty())
    {
        return false;
    }
    else
    {
        return saveImage(format.constData());
    }
}
