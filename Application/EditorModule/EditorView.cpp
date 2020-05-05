#include "EditorView.h"


EditorView::EditorView(QStackedWidget* container,  QWidget *parent)
    : QWidget(parent)
{
    Events *events = new Events;

    // this is the Widget that will be shown when drawing
    DrawingView *drawingView = new DrawingView(events, this);
    drawingView->resize(700, 400);

    TextEditor *textEditor = new TextEditor(this);
    textEditor->resize(700, 400);

    m_editorModule = new EditorModule(drawingView, textEditor, events);

    m_container = container;
    m_container->addWidget(drawingView);
    m_container->addWidget(textEditor);
    m_container->setCurrentWidget(drawingView);
}

void EditorView::initializeTabs()
{
    QPushButton *tab0 = new QPushButton(this);
    tab0->setObjectName(QString("tab0"));
    tab0->setText("Tab0");
    tab0->setGeometry(QRect(20, 10, 80, 25));

    QPushButton *tab1 = new QPushButton(this);
    tab1->setObjectName(QString("tab1"));
    tab1->setText("Tab1");
    tab1->setGeometry(QRect(110, 10, 80, 25));

    QPushButton *tab2 = new QPushButton(this);
    tab2->setObjectName(QString("tab2"));
    tab2->setText("Tab2");
    tab2->setGeometry(QRect(200, 10, 80, 25));

    QPushButton *tab3 = new QPushButton(this);
    tab3->setObjectName(QString("tab3"));
    tab3->setText("Tab3");
    tab3->setGeometry(QRect(290, 10, 80, 25));

    QPushButton *tab4 = new QPushButton(this);
    tab4->setObjectName(QString("tab4"));
    tab4->setText("Tab4");
    tab4->setGeometry(QRect(380, 10, 80, 25));
}
