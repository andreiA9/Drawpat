#ifndef EDITORVIEW_H
#define EDITORVIEW_H

// WIDGETS
#include <QPushButton>
#include <QStackedWidget>

// USER-DEFINED
#include "TextEditor.h"
#include "DrawingView.h"


class EditorView : public QWidget
{
    Q_OBJECT

public:
    EditorView(DrawingView *drawingView, TextEditor *textEditor, QWidget *parent = nullptr);

    void initializeTabs();

private:
    QPushButton *tab0 = nullptr;
    QPushButton *tab1 = nullptr;
    QPushButton *tab2 = nullptr;
    QPushButton *tab3 = nullptr;
    QPushButton *tab4 = nullptr;

    QStackedWidget m_container;
};

#endif // EDITORVIEW_H
