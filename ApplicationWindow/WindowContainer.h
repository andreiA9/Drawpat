#ifndef WINDOW_CONTAINER_H
#define WINDOW_CONTAINER_H

// local project headers
// ----------------------
#include "EditorModule.h"

// standard C/C++ headers
// ----------------------
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QImageWriter>
#include <QPushButton>
#include <QTreeView>
#include <QLabel>

class WindowContainer : public QWidget
{
    Q_OBJECT

public:
    WindowContainer(QWidget *parent = nullptr);
    ~WindowContainer();

    /** \brief initializes the PAINT BUTTONS
      */
    void initializeControlButtons();

    /** \brief initializes the tree view with the file system model
      */
    void initializeDrawingViewAndTreeView(QStackedWidget* stackedWorkArea);

    void initializeBottomGrid();

    /** \brief add the STATUS BAR to the MainLayout
      */
    void initializeStatusBar();

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
    // main layout
    QGridLayout* m_mainLayout = nullptr;

    // bottom grid layout
    QGridLayout* m_bottomGridWithoutSpacing;

    // files tree view
    QTreeView* m_filesTreeView;

    // file tabs from here
    QHBoxLayout* m_tabsLayout;
    QVector<QLabel*> m_tabVector;

    // Menu items
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu = nullptr;
    QMenu* m_saveAsMenu = nullptr;
    QMenu* m_optionMenu = nullptr;
    QMenu* m_helpMenu = nullptr;

    // Menu -> File
    QAction* m_newAction = nullptr;
    QAction* m_openAction = nullptr;
    QAction* m_saveAction = nullptr;
    QList<QAction*> m_saveAsActions;  // this is the saveAsMenu = it is the LIST of FILE.formats to be saved
    QAction* m_exitAction = nullptr;

    // Menu -> Edit
    QMenu* m_editMenu = nullptr;
    QAction* m_editCutAction = nullptr;
    QAction* m_editCopyAction = nullptr;
    QAction* m_editPasteAction = nullptr;
    QAction* m_editUndoAction = nullptr;
    QAction* m_editRedoAction = nullptr;

    // Menu -> Option
    QAction* m_penColorAction = nullptr;
    QAction* m_penWidthAction = nullptr;
    QAction* m_clearDrawingAreaAction = nullptr;

    // Menu -> About
    QAction* m_aboutAction = nullptr;

    QStatusBar* m_statusbar = nullptr;

    // CONTROL BUTTONS
    QHBoxLayout* m_buttonLayout = nullptr;
    QPushButton* m_penButton0 = nullptr;
    QPushButton* m_selectButton1 = nullptr;
    QPushButton* m_writeButton2 = nullptr;
    QPushButton* m_upperButton3 = nullptr;
    QPushButton* m_rotateButton4 = nullptr;
};

#endif // WINDOW_CONTAINER_H
