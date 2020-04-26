#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

// QT WIDGETS
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QImageWriter>
#include <QPushButton>



class MainLayout : public QGridLayout
{
    Q_OBJECT

public:
    MainLayout(QWidget *centralWidget, QWidget *parent = nullptr);
    ~MainLayout();

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

    // SETTERS
    void setControlButtons(QPushButton *upperButton0,
                           QPushButton *upperButton1,
                           QPushButton *upperButton2,
                           QPushButton *upperButton3,
                           QPushButton *upperButton4);
    void setStatusBar(QStatusBar *statusbar);

private:
    /** \brief will create the ACTIONS for each MENU.BUTTON
      */
    void createActions();

    /** \brief will create the MENUBAR<that contains many BUTTONS
      */
    void createMenuBar();

    /** \brief will create the BUTTONS of the MENUBAR
      */
    void addMenuBarButtons(QMenuBar *menuBar);

private:

};

#endif // MAINLAYOUT_H
