#include "EditorView.h"


EditorView::EditorView(QStackedWidget* container, DrawingView *drawingView, TextEditor* textEditor, Events *events)
{
    Q_ASSERT(container);
    Q_ASSERT(drawingView);
    Q_ASSERT(textEditor);
    Q_ASSERT(events);

    m_events = events;
    m_textEditor = textEditor;
    m_textEditor->resize(700, 400);

    m_drawingView = drawingView;
    m_drawingView->resize(700, 400);

    m_container = container;
    m_container->addWidget(m_drawingView);
    m_container->addWidget(m_textEditor);
    m_container->setCurrentWidget(m_drawingView);
}

EditorView::~EditorView()
{
}

void EditorView::initializeTabs()
{
    QPushButton *tab0 = new QPushButton(m_container);
    tab0->setObjectName(QString("tab0"));
    tab0->setText("Tab0");
    tab0->setGeometry(QRect(20, 10, 80, 25));

    QPushButton *tab1 = new QPushButton(m_container);
    tab1->setObjectName(QString("tab1"));
    tab1->setText("Tab1");
    tab1->setGeometry(QRect(110, 10, 80, 25));

    QPushButton *tab2 = new QPushButton(m_container);
    tab2->setObjectName(QString("tab2"));
    tab2->setText("Tab2");
    tab2->setGeometry(QRect(200, 10, 80, 25));

    QPushButton *tab3 = new QPushButton(m_container);
    tab3->setObjectName(QString("tab3"));
    tab3->setText("Tab3");
    tab3->setGeometry(QRect(290, 10, 80, 25));

    QPushButton *tab4 = new QPushButton(m_container);
    tab4->setObjectName(QString("tab4"));
    tab4->setText("Tab4");
    tab4->setGeometry(QRect(380, 10, 80, 25));
}
