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

// USER-DEFINED
#include "Events.h"
#include "DrawingView.h"
#include "TextEditor.h"



// TODO: REMOVE Q_OBJECT from EditorModule < a MODULE cannot be QObject
class EditorModule : public QObject
{
    Q_OBJECT

public:
    EditorModule(DrawingView *drawingView, TextEditor *textEditor, Events *events);
    ~EditorModule();

    /** \brief if both{DrawingView/TextEditor} have been modified
      * \return if one from{DrawingView/TextEditor} has been modified
      */
    bool isDirty() const { return m_drawingView->isModified(); }

    void setFileName(const QString &fileName) { m_fileName = fileName; }
    void setPenColor(const QColor &color);
    void setPenWidth(int width);

    QString getFileName() const { return m_fileName; }
    QColor getPenColor() const { return m_drawingView->getPenColor(); }
    int getPenWidth() const { return m_drawingView->getPenWidth(); }

    /** \brief is signaling EVENT=ROTATION to class=Events
      */
    void rotationTriggered(bool rotated);

    /** \brief is creating a new FILE
      */
    void create();

    /** \brief will open an existing FILE
      */
    void openFile();

    /** \brief calls save on DrawingView
      */
    bool saveFile(const QByteArray &format);


    void clear();

    // DRAWING VIEW \ PEN FUNCTIONS
    /** \brief the color is received from the DIALOG BOX<with the
      *        color to be selected=this from a Circle=colors
      */
    void editPenColor();
    void editPenWidth();

private:
    QString m_fileName;
    DrawingView *m_drawingView = nullptr;
    TextEditor *m_textEditor = nullptr;
    Events *m_events = nullptr;
};

#endif // EDITORMODULE_H
