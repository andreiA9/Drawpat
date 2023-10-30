#ifndef IMAGE_EDITOR_H
#define IMAGE_EDITOR_H

// local project headers
// ----------------------
#include "Events.h"
#include "PaintingManager.h"

// standard C/C++ headers
// ----------------------
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

/** \brief Getter needed when the User modifies the Image without changing it
  * \param level an integer setting how useful to be
  * \return Output that is extra useful
  */

class ImageEditor : public QWidget
{
    Q_OBJECT

public:
    ImageEditor(Events *events, PaintingManager* paintingManager, QWidget *parent = nullptr);

    void setPenColor(const QColor &color);

    void setPenWidth(int width);

    /** \brief EVENTS PROCESSING
      */
    void processEvents();

    /** \brief Getter needed when the User modifies the Image without changing it
      * \return true - if the image was modified
      */
    QColor inline getPenColor() const { return m_penColor; }

    int inline getPenWidth() const { return m_penWidth; }

    inline QImage& getCurrentImage() const { return m_paintingManager->getCurrentImage(); };

    void resizeImage(QImage *image, const QSize &newSize);

    void resizeCurrentImage();

    void fillWithImage(const QImage& currentImage);

signals:
    void mouseReleased();

public slots:
    /** \brief clears the AREA=drawing
      */
    void clearImage();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    /** \brief Update paint area
      * \param event - WIDGET.EVENT
      */
    // REIMPLEMENTING void QWidget::paintEvent ( QPaintEvent * event ) >
    // will allow to DRAW inside the WIDGET
    void paintEvent(QPaintEvent *event) override;

    /** \brief Used at window resizing
      * \param event - WIDGET.EVENT
      */
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);

    void rotateTo90Degrees(QImage &dstImg);

    void switchToSelectCursor();

    bool isInsideWidget(QWidget& widget);

private:
    Events* m_events = nullptr;
    PaintingManager* m_paintingManager;
    QPoint m_lastDrawingPoint;
    QPoint m_lastMovePoint;
    QColor m_penColor;
    QPoint m_textPosition;
    int m_penWidth;
//    TransformedRectangle* m_transformedRectangle;
};

#endif // IMAGE_EDITOR_H
