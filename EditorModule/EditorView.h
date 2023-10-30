#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

// local project headers
// ----------------------
#include "TextEditor.h"
#include "ImageEditor.h"

// standard C/C++ headers
// ----------------------
#include <QPushButton>
#include <QStackedWidget>

class EditorView : public QObject
{
    Q_OBJECT

public:
    EditorView(QStackedWidget* stackedWorkArea, ImageEditor *imageEditor, TextEditor* textEditor, Events *events);
    ~EditorView();

    void initializeTabs();

private:
    QPushButton* tab0 = nullptr;
    QPushButton* tab1 = nullptr;
    QPushButton* tab2 = nullptr;
    QPushButton* tab3 = nullptr;
    QPushButton* tab4 = nullptr;

    QStackedWidget* m_stackedWorkArea = nullptr;
    ImageEditor* m_imageEditor = nullptr;
    TextEditor* m_textEditor = nullptr;
    Events* m_events = nullptr;
};

#endif // EDITOR_VIEW_H
