#include "EditorModule.h"



EditorModule::EditorModule(DrawingView *drawingView)
{
    m_drawingView = drawingView;
}

bool EditorModule::isDirty() const
{
    return m_drawingView->isModified();
}

void EditorModule::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void EditorModule::setPenColor(const QColor &color)
{
    m_drawingView->setPenColor(color);
}

void EditorModule::setPenWidth(int width)
{
    m_drawingView->setPenWidth(width);
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
