#include "EditorModule.h"



EditorModule::EditorModule(QStackedWidget* container)
{
    Q_ASSERT(container);

    Events *m_events = new Events;
    m_drawingView = new DrawingView(m_events);
    m_textEditor = new TextEditor;
    m_container = container;

    m_editorView = new EditorView(m_container, m_drawingView, m_textEditor, m_events);
}

EditorModule::~EditorModule()
{
    delete m_container;
    delete m_editorView;

    /* Note: when removing widgets from QStackedWidget > the widget is not deleted,
    but simply removed from the widget's stacked layout, causing it to be hidden. */
    m_container->removeWidget(m_drawingView);
    m_container->removeWidget(m_textEditor);
    delete m_drawingView;
    delete m_textEditor;
    delete m_events;
}

void EditorModule::setPenColor(const QColor &color)
{
    m_drawingView->setPenColor(color);
}

void EditorModule::setPenWidth(int width)
{
    m_drawingView->setPenWidth(width);
}

void EditorModule::rotationTriggered(bool rotated)
{
    m_events->setImageRoted(rotated);
    m_drawingView->processEvents();
}

void EditorModule::create()
{
    QString fileName = "Untitled.png";
    setFileName(fileName);
}

void EditorModule::openFile()
{
    m_drawingView->openImage(m_fileName);
}

bool EditorModule::saveFile(const QByteArray &format)
{
    if (m_fileName.isEmpty())
    {
        return false;
    }
    else
    {
        return m_drawingView->saveImage(m_fileName, format.constData());
    }
}

void EditorModule::clear()
{
    m_drawingView->clearImage();
}
