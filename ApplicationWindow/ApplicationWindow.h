#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

// local project headers
// ----------------------
#include "WindowContainer.h"

// standard C/C++ headers
// ----------------------
#include <QWidget>
#include <QImageWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QList>

//QT_BEGIN_NAMESPACE
//namespace Ui { class ApplicationWindow; }
//QT_END_NAMESPACE

class ApplicationWindow : public WindowContainer
{
    Q_OBJECT

public:
    ApplicationWindow();
    ~ApplicationWindow();

protected:
    /** \brief this is for preventing the USER to close the APPLICATION
      *        without SAVING FILES
      * \note this is called when the USER was pressing CLOSE
      * \param - event
      */
    void closeEvent(QCloseEvent *event) override;

private slots:
    // FUNCTIONS = IMAGE

    /** \brief check if changes have been made before our last save
      *        before opening a FILE.new
      */
    void open();

    /** \brief simple save<which means overwritting the image file
      */
    void save();

    /** \brief depending on the ACTION that was being pressed>the
      *        FILE is being saved in the corresponding FORMAT
      */
    void saveAs();

    void editPenColor();
    void editPenWidth();

    // FUNCTIONS = ABOUT
    void showAbout();

    void handleFunction();

    void getTreeViewSelection();

private:
    /** \brief the interraction BUTTONS are put here
      */
    void initializeConnects();

    /** \brief the CONNECTIONS from MainLayout are made here
      */
    void initializeMenuConnects();

    /** \brief the user cannot[0 = open a file/1 = close the application]
      *        if the current file was not saved
      */
    bool trySave();
    bool saveFile(const QByteArray &fileFormat);

private:
    EditorModule* m_editorModule = nullptr;
};
#endif // APPLICATION_WINDOW_H
