#ifndef DOCUMENT_CONTAINER_H
#define DOCUMENT_CONTAINER_H

#include <QVector>
#include <QString>
#include <QImage>

class DocumentContainer
{
public:
    /** \brief is creating a new FILE
      */
    void addFile();

    /** \brief is generating an UNIQUE new FILE
      */
    QString generateNewFile();

    bool openImage(const QString &fileName, QImage& loadedImage);

    bool saveImage(const QString &imagePathWithFileName, QImage& currentImage,
                   const char *fileFormat);

private:
    QVector<QString*> m_openFileNames;
    QString m_fileName;
};

#endif // DOCUMENT_CONTAINER_H
