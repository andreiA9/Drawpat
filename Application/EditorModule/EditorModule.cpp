#include "EditorModule.h"



EditorModule::EditorModule(DrawingView *drawingView, Events *events)
{
    m_drawingView = drawingView;
    m_events = events;
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
