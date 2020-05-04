#include "EditorModule.h"



EditorModule::EditorModule(DrawingView *drawingView, TextEditor* textEditor, Events *events)
{
    Q_ASSERT(drawingView);
    Q_ASSERT(textEditor);
    Q_ASSERT(events);

    m_drawingView = drawingView;
    m_textEditor = textEditor;
    m_events = events;
}

EditorModule::~EditorModule()
{
    // !!!!PE ASTEA nu se face delete nicaieri
    delete m_drawingView;
    delete m_textEditor;
    //Note: The ownership of widget remains the same. The widget is not deleted, but simply removed from the widget's stacked layout, causing it to be hidden.
    //So you have to do it yourself:
    //Qt Code
    //stackedWidget->removeWidget(pageWidget);
    //pageWidget->deleteLater(); // or: delete pageWidget;
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
