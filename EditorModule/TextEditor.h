#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif
