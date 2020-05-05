#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

// QT WIDGETS
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QImageWriter>
#include <QPushButton>

// USER-DEFINED
#include "../EditorModule/EditorView.h"
//#include "EditorView.h"



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

    virtual EditorView* getEditorView() = 0;

protected:
    QMenuBar* m_menuBar;

    // MENU ITEMS
    QMenu *m_fileMenu = nullptr;
    QMenu *m_saveAsMenu = nullptr;
    QMenu *m_optionMenu = nullptr;
    QMenu *m_helpMenu = nullptr;

    // Menu->File
    QAction *m_newAction = nullptr;
    QAction *m_openAction = nullptr;
    QList<QAction*> m_saveAsActions;  // this is the saveAsMenu = it is the LIST of FILE.formats to be saved
    QAction *m_exitAction = nullptr;

    QAction *m_penColorAction = nullptr;
    QAction *m_penWidthAction = nullptr;
    QAction *m_clearDrawingAreaAction = nullptr;
    QAction *m_aboutAction = nullptr;

    QMenu *m_editMenu = nullptr;
    QAction *m_editCutAction = nullptr;
    QAction *m_editCopyAction = nullptr;
    QAction *m_editPasteAction = nullptr;
    QAction *m_editUndoAction = nullptr;
    QAction *m_editRedoAction = nullptr;

    QStatusBar *m_statusbar = nullptr;

    // CONTROL BUTTONS
    QHBoxLayout *m_horizontalLayout = nullptr;
    QPushButton *m_upperButton0 = nullptr;
    QPushButton *m_upperButton1 = nullptr;
    QPushButton *m_upperButton2 = nullptr;
    QPushButton *m_upperButton3 = nullptr;
    QPushButton *m_upperButton4 = nullptr;

    QPushButton *m_button = nullptr;

    QGridLayout *m_mainLayout = nullptr;
};

#endif // MAINLAYOUT_H
