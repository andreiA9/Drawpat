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

    // GETTERS
    QAction* getCreateAction() const { return m_newAction; }
    QAction* getOpenAction() const { return m_openAction; }
    QList<QAction*>& getSaveAsActions()  { return m_saveAsActions; }
    QAction* getPenColorAction() const { return m_penColorAction; }
    QAction* getPenWidthAction() const { return m_penWidthAction; }
    QAction* getClearDrawingAreaAction() const { return m_clearDrawingAreaAction; }
    QAction* getAboutAction() const { return m_aboutAction; }
    QAction* getExitAction() const { return m_exitAction; }

    QPushButton * getUpperButton0() const { return m_upperButton0; }
    QPushButton * getUpperButton1() const { return m_upperButton1; }
    QPushButton * getUpperButton2() const { return m_upperButton2; }
    QPushButton * getUpperButton3() const { return m_upperButton3; }
    QPushButton * getUpperButton4() const { return m_upperButton4; }

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
};

#endif // MAINLAYOUT_H
