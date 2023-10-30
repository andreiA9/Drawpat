#ifndef EDITORMODULE_H
#define EDITORMODULE_H

// QT WIDGETS
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>

// QT
#include <QString>
#include <QTranslator>
#include "Logger.h"

// USER-DEFINED
#include "EditorView.h"
#include "Events.h"
#include "ImageEditor.h"
#include "TextEditor.h"
#include "DocumentContainer.h"

// TODO: REMOVE Q_OBJECT from EditorModule < a MODULE cannot be QObject
class EditorModule : public QObject
{
    Q_OBJECT

public:
    EditorModule(QStackedWidget* stackedWorkArea);
    ~EditorModule();

    /** \brief if both{DrawingView/TextEditor} have been modified
      * \return if one from{DrawingView/TextEditor} has been modified
      */
    bool isDirty() const { return m_isModified; }

    void setPenColor(const QColor &color);
    void setPenWidth(int width);

    QColor getPenColor() const { return m_imageEditor->getPenColor(); }
    int getPenWidth() const { return m_imageEditor->getPenWidth(); }

    void drawingTriggered();

    void selectionTriggered();

    void writingTriggered();

    /** \brief is signaling EVENT=ROTATION to class=Events
      */
    void rotationTriggered();

    /** \brief is creating a new FILE
      */
    void addFile();

    /** \brief is generating an UNIQUE new FILE
      */
    QString generateNewFile();

    /** \brief will open an existing FILE
      */
    void loadImage(const QString &fileName);

    /** \brief calls save on DrawingView
      */
    bool saveImage(const QString &imagePathWithFileName, const QByteArray &format);


    void clear();

    // DRAWING VIEW \ PEN FUNCTIONS
    /** \brief the color is received from the DIALOG BOX<with the
      *        color to be selected=this from a Circle=colors
      */
    void editPenColor();
    void editPenWidth();

public slots:
    void setIsModified();

private:
    EditorView* m_editorView = nullptr;
    ImageEditor* m_imageEditor = nullptr;
    TextEditor* m_textEditor = nullptr;
    Events* m_events = nullptr;
    bool m_isModified;
    DocumentContainer m_documentContainer;
};

#endif // EDITORMODULE_H
