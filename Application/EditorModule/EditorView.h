#ifndef EDITORVIEW_H
#define EDITORVIEW_H

// WIDGETS
#include <QPushButton>
#include <QStackedWidget>

// USER-DEFINED
#include "TextEditor.h"
#include "DrawingView.h"
#include "EditorModule.h"



class EditorView : public QWidget
{
    Q_OBJECT

public:
    EditorView(QStackedWidget* container, QWidget *parent = nullptr);

    void initializeTabs();

    QStackedWidget * getContainer() const { return m_container; }

private:
    QPushButton *tab0 = nullptr;
    QPushButton *tab1 = nullptr;
    QPushButton *tab2 = nullptr;
    QPushButton *tab3 = nullptr;
    QPushButton *tab4 = nullptr;

    QStackedWidget* m_container = nullptr;
    EditorModule * m_editorModule = nullptr;
};

#endif // EDITORVIEW_H
