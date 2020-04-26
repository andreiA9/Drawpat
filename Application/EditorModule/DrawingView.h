#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H


#include <QMouseEvent>
#include <QPainter>

// USER-DEFINED
#include "EditorView.h"
#include "Events.h"


/** \brief Getter needed when the User modifies the Image without changing it
  * \param level an integer setting how useful to be
  * \return Output that is extra useful
  */


class DrawingView : public EditorView
{
    Q_OBJECT

public:
    DrawingView(Events *events, QWidget *parent = nullptr);

    bool openImage(const QString &fileName);
    bool saveImage(QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);

    /** \brief Getter needed when the User modifies the Image without changing it
      * \return true - if the image was modified
      */
    bool inline isModified() const { return m_isModified; }
    QColor inline getPenColor() const { return m_penColor; }
    int inline getPenWidth() const { return m_penWidth; }


public slots:
    /** \brief clears the AREA=drawing
      */
    void clearImage();

protected:
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
    void resizeImage(QImage *image, const QSize &newSize);

    void rotateTo90Degrees(QImage &dstImg);

private:
    bool m_isDrawingAllowed;
    bool m_isModified;
    Events *m_events;

    QImage m_image;
    QPoint m_lastPoint;
    QColor m_penColor;
    int m_penWidth;
};

#endif // DRAWINGAREA_H
