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
#include "DrawingArea.h"



// TODO: REMOVE Q_OBJECT from EditorModule < a MODULE cannot be QObject
class EditorModule : public QObject
{
    Q_OBJECT

public:
    EditorModule(DrawingView *drawingView);

    /** \brief if both{DrawingView/TextEditor} have been modified
      * \return if one from{DrawingView/TextEditor} has been modified
      */
    bool isDirty() const;

    void setFileName(const QString &fileName);
    QString getFileName() const { return m_fileName; }

    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    QColor getPenColor() const { return m_drawingView->getPenColor(); }
    int getPenWidth() const { return m_drawingView->getPenWidth(); }

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
    DrawingView *m_drawingView;
};

#endif // EDITORMODULE_H
