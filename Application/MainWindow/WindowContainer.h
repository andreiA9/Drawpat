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
    /** \brief will create the ACTIONS for each MENU.BUTTON
      */
    void createActions();

    /** \brief will create the MENUBAR<that contains many BUTTONS
      */
    void createMenuBar();

    /** \brief will create the BUTTONS of the MENUBAR
      */
    void addMenuBarButtons(QMenuBar *menuBar);

protected:
    // MENU ITEMS
    QMenu *m_saveAsMenu;
    QMenu *m_fileMenu;
    QMenu *m_optionMenu;
    QMenu *m_helpMenu;

    // ACTIONS inside the MENUS
    QAction *m_newAction;
    QAction *m_openAction;
    QList<QAction*> m_saveAsActions;  // this is the saveAsMenu = it is the LIST of FILE.formats to be saved
    QAction *m_penColorAction;
    QAction *m_penWidthAction;
    QAction *m_clearDrawingAreaAction;
    QAction *m_aboutAction;
    QAction *m_exitAction;

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
