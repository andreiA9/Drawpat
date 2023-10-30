// local project headers
// ----------------------
#include "EditorModule.h"
#include "PaintingManager.h"
#include "Logger.h"

// standard C/C++ headers
// ----------------------
#include <QThread>

EditorModule::EditorModule(QStackedWidget* stackedWorkArea)
    : m_isModified(false)
{
    Q_ASSERT(stackedWorkArea);    // SAME as -> if (!stackedWorkArea) { return; }

    PaintingManager* paintingManager = new PaintingManager;
    m_events = new Events;
    m_imageEditor = new ImageEditor(m_events, paintingManager);
    m_textEditor = new TextEditor;
    m_editorView = new EditorView(stackedWorkArea, m_imageEditor, m_textEditor, m_events);

    connect(m_imageEditor, &ImageEditor::mouseReleased, this, &EditorModule::setIsModified);
}

EditorModule::~EditorModule()
{
    delete m_editorView;

    delete m_imageEditor;
    delete m_textEditor;
    delete m_events;
}

void EditorModule::setPenColor(const QColor &color)
{
    m_imageEditor->setPenColor(color);
}

void EditorModule::setPenWidth(int width)
{
    m_imageEditor->setPenWidth(width);
}

void EditorModule::drawingTriggered()
{
    m_events->setEventEnabled(PaintEvent::Drawing);
}

void EditorModule::selectionTriggered()
{
    m_events->setEventEnabled(PaintEvent::Selection);
}

void EditorModule::writingTriggered()
{
    m_events->setEventEnabled(PaintEvent::Writing);
}

void EditorModule::rotationTriggered()
{
    m_events->setEventEnabled(PaintEvent::Rotation);
}

void EditorModule::addFile()
{
    m_documentContainer.addFile();
}

QString EditorModule::generateNewFile()
{
    return m_documentContainer.generateNewFile();
}

void EditorModule::loadImage(const QString &fileName)
{
    QImage loadedImage;
    if (m_documentContainer.openImage(fileName, loadedImage))
    {
        m_isModified = false;

        m_imageEditor->fillWithImage(loadedImage);
    }
}

bool EditorModule::saveImage(const QString &imagePathWithFileName, const QByteArray &format)
{
    QImage& currentImage = m_imageEditor->getCurrentImage();
    if (!m_documentContainer.saveImage(imagePathWithFileName, currentImage, format.constData()))
    {
        editorDebug() << "Could not save file, because file name is empy.";
        return false;
    }

    editorDebug() << "Saving file " << imagePathWithFileName << " to disk.";
    m_isModified = false;
    return true;
}

void EditorModule::clear()
{
    m_imageEditor->clearImage();
    m_isModified = true;
}

void EditorModule::setIsModified()
{
    m_isModified = true;
}
