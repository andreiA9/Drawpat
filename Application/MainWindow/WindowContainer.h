#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

// QT WIDGETS
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QImageWriter>
#include <QPushButton>



class WindowContainer : public QWidget
{
    Q_OBJECT

public:
    WindowContainer(QWidget *parent = nullptr);
    ~WindowContainer();

    // INITIALIZATION
    void initializeControlButtons();

    /** \brief add the STATUS BAR to the MainLayout
      */
    void initializeStatusBar();

    /** \brief the main LAYOUT of the ApplicationWindow
      */
    void initializeMainLayout();

protected:
    /** \brief will create the ACTIONS for each Menu->File
      */
    void createFileMenu();

    /** \brief will create the ACTIONS for each Menu->Edit
      */
    void createEditMenu();

    /** \brief will create the BUTTONS of the MENUBAR
      */
    void createOtherMenus();

    /** \brief will create the MENUBAR<that contains many BUTTONS
      */
    void createMenuBar();

protected:
    QMenuBar* m_menuBar;

    // MENU ITEMS
    QMenu *m_fileMenu;
    QMenu *m_saveAsMenu;
    QMenu *m_optionMenu;
    QMenu *m_helpMenu;

    // Menu->File
    QAction *m_newAction;
    QAction *m_openAction;
    QList<QAction*> m_saveAsActions;  // this is the saveAsMenu = it is the LIST of FILE.formats to be saved
    QAction *m_exitAction;

    QAction *m_penColorAction;
    QAction *m_penWidthAction;
    QAction *m_clearDrawingAreaAction;
    QAction *m_aboutAction;

    QMenu *m_editMenu;
    QAction *m_editCutAction;
    QAction *m_editCopyAction;
    QAction *m_editPasteAction;
    QAction *m_editUndoAction;
    QAction *m_editRedoAction;

    QStatusBar *m_statusbar;

    // CONTROL BUTTONS
    QHBoxLayout *m_horizontalLayout;
    QPushButton *m_upperButton0;
    QPushButton *m_upperButton1;
    QPushButton *m_upperButton2;
    QPushButton *m_upperButton3;
    QPushButton *m_upperButton4;

    QPushButton *m_button;

    QGridLayout *m_gridLayout;
    QWidget *m_centralWidget;
};

#endif // MAINLAYOUT_H
