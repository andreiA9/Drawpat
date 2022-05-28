#ifndef EDITORVIEW_H
#define EDITORVIEW_H

// WIDGETS
#include <QPushButton>
#include <QStackedWidget>

// USER-DEFINED
#include "TextEditor.h"
#include "DrawingView.h"



class EditorView : public QObject
{
    Q_OBJECT

public:
    EditorView(QStackedWidget* container, DrawingView *drawingView, TextEditor* textEditor, Events *events);
    ~EditorView();

    void initializeTabs();

    QStackedWidget * getContainer() const { return m_container; }

private:
    QPushButton *tab0 = nullptr;
    QPushButton *tab1 = nullptr;
    QPushButton *tab2 = nullptr;
    QPushButton *tab3 = nullptr;
    QPushButton *tab4 = nullptr;

    QStackedWidget* m_container = nullptr;
    DrawingView *m_drawingView = nullptr;
    TextEditor *m_textEditor = nullptr;
    Events *m_events = nullptr;
};

#endif // EDITORVIEW_H
