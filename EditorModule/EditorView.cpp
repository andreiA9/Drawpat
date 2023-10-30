// local project headers
// ----------------------
#include "EditorView.h"

// standard C/C++ headers
// ----------------------

EditorView::EditorView(QStackedWidget* stackedWorkArea, ImageEditor *imageEditor, TextEditor* textEditor, Events *events)
{
    Q_ASSERT(stackedWorkArea);
    Q_ASSERT(imageEditor);
    Q_ASSERT(textEditor);
    Q_ASSERT(events);

    m_events = events;
    m_textEditor = textEditor;
    m_textEditor->resize(700, 400);

    m_imageEditor = imageEditor;
    m_imageEditor->resize(700, 400);

    m_stackedWorkArea = stackedWorkArea;
    m_stackedWorkArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWorkArea->addWidget(m_imageEditor);
    m_stackedWorkArea->addWidget(m_textEditor);
    m_stackedWorkArea->setCurrentWidget(m_imageEditor);
//    m_stackedWorkArea->setCurrentWidget(m_textEditor);
}

EditorView::~EditorView()
{
    /* Note: when removing widgets from QStackedWidget > the widget is not deleted,
    but simply removed from the widget's stacked layout, causing it to be hidden. */
    m_stackedWorkArea->removeWidget(m_imageEditor);
    m_stackedWorkArea->removeWidget(m_textEditor);
    delete m_stackedWorkArea;
}

void EditorView::initializeTabs()
{
    QPushButton *tab0 = new QPushButton(m_stackedWorkArea);
    tab0->setObjectName(QString("tab0"));
    tab0->setText("Tab0");
    tab0->setGeometry(QRect(20, 10, 80, 25));

    QPushButton *tab1 = new QPushButton(m_stackedWorkArea);
    tab1->setObjectName(QString("tab1"));
    tab1->setText("Tab1");
    tab1->setGeometry(QRect(110, 10, 80, 25));

    QPushButton *tab2 = new QPushButton(m_stackedWorkArea);
    tab2->setObjectName(QString("tab2"));
    tab2->setText("Tab2");
    tab2->setGeometry(QRect(200, 10, 80, 25));

    QPushButton *tab3 = new QPushButton(m_stackedWorkArea);
    tab3->setObjectName(QString("tab3"));
    tab3->setText("Tab3");
    tab3->setGeometry(QRect(290, 10, 80, 25));

    QPushButton *tab4 = new QPushButton(m_stackedWorkArea);
    tab4->setObjectName(QString("tab4"));
    tab4->setText("Tab4");
    tab4->setGeometry(QRect(380, 10, 80, 25));
}
