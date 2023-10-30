// local project headers
// ----------------------
#include "DocumentContainer.h"

// standard C/C++ headers
// ----------------------

void DocumentContainer::addFile()
{
    QString fileName = "Untitled.png";
    m_fileName = fileName;
}

QString DocumentContainer::generateNewFile()
{
    // search in files with "New 1" - vezi in Notepad++
    return QString("New 1.png");
}

bool DocumentContainer::openImage(const QString &fileName, QImage& loadedImage)
{
    QString newFileName;
    if (!fileName.isEmpty())
    {
        newFileName = fileName;
    }
    else
    {
        newFileName = m_fileName;
    }

    if (!loadedImage.load(newFileName))
    {
        // DEBUG: the IMAGE could not be loaded
        return false;
    }

    return true;
}

bool DocumentContainer::saveImage(const QString &imagePathWithFileName, QImage& currentImage,
                         const char *fileFormat)
{
    QString newFileName;
    if (!imagePathWithFileName.isEmpty())
    {
        newFileName = imagePathWithFileName;
    }
    else
    {
        newFileName = m_fileName;
    }

    if (!currentImage.save(imagePathWithFileName, fileFormat))
    {
        return false;
    }

    return true;
}
