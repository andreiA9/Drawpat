#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>


/** \brief Getter needed when the User modifies the Image without changing it
  * \param level an integer setting how useful to be
  * \return Output that is extra useful
  */


class DrawingView : public QWidget
{
    Q_OBJECT

public:
    DrawingView(QWidget *parent = nullptr);

    bool openImage(const QString &fileName);
//    bool saveImage(const char *format);
    bool saveImage(QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);

    /** \brief Getter needed when the User modifies the Image without changing it
      * \return true - if the image was modified
      */
    bool isModified() const { return m_isModified; }
    QColor getPenColor() const { return m_penColor; }
    int getPenWidth() const { return m_penWidth; }

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

private:
    bool m_isDrawingAllowed;
    bool m_isModified;

    QImage m_image;
    QPoint m_lastPoint;
    QColor m_penColor;
    int m_penWidth;
};

#endif // DRAWINGAREA_H
