#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>



class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor(QWidget *parent = nullptr);
};

#endif
