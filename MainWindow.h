#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// QT WIDGETS
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QImageWriter>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>

#include <QList>

#include "DrawingArea.h"



class DrawingArea;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /** \brief this is for preventing the USER to close the APPLICATION
      *        without SAVING FILES
      * \note this is called when the USER was pressing CLOSE
      * \param - event
      */
    void closeEvent(QCloseEvent *event) override;

private slots:
    // FUNCTIONS = IMAGE

    /** \brief is creating a new file
      */
    void create();

    /** \brief check if changes have been made before our last save
      *        before opening a FILE.new
      */
    void open();

    /** \brief depending on the ACTION that was being pressed>the
      *        FILE is being saved in the corresponding FORMAT
      */
    void save();

    // FUNCTIONS = PEN
    /** \brief the color is received from the DIALOG BOX<with the
      *        color to be selected=this from a Circle=colors
      */
    void editPenColor();
    void editPenWidth();

    // FUNCTIONS = ABOUT
    void showAbout();

private:
    /** \brief will create the ACTIONS for each MENU.BUTTON
      */
    void createActions();

    /** \brief will create the MENUBAR<that contains many BUTTONS
      */
    void createMenuBar(QGridLayout *layout);

    /** \brief will create the BUTTONS of the MENUBAR
      */
    void addMenuBarButtons(QMenuBar *menuBar);

    /** \brief the user cannot[0 = open a file/1 = close the application]
      *        if the current file was not saved
      */
    bool trySave();
    bool saveFile(const QByteArray &fileFormat);

private:
    Ui::MainWindow *ui;
    DrawingArea *m_drawingArea;
    // MENU ITEMS
    QMenu *m_saveAsMenu;
    QMenu *m_fileMenu;
    QMenu *m_optionMenu;
    QMenu *m_helpMenu;
    // ACTIONS inside the MENUS
    QAction *m_createAction;
    QAction *m_openAction;
    QList<QAction*> m_saveAsActions;  // this is the saveAsMenu = it is the LIST of FILE.formats to be saved
    QAction *m_penColorAction;
    QAction *m_penWidthAction;
    QAction *m_clearDrawingAreaAction;
    QAction *m_aboutAction;
    QAction *m_exitAction;
};
#endif // MAINWINDOW_H
