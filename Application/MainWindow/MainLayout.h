#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

// QT WIDGETS
#include <QGridLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QImageWriter>



class MainLayout : public QGridLayout
{
    Q_OBJECT

public:
    MainLayout(QWidget *drawingArea, QWidget *parent = nullptr);

    // GETTERS
    QAction* getCreateAction() const { return m_newAction; }
    QAction* getOpenAction() const { return m_openAction; }
    QList<QAction*>& getSaveAsActions()  { return m_saveAsActions; }
    QAction* getPenColorAction() const { return m_penColorAction; }
    QAction* getPenWidthAction() const { return m_penWidthAction; }
    QAction* getClearDrawingAreaAction() const { return m_clearDrawingAreaAction; }
    QAction* getAboutAction() const { return m_aboutAction; }
    QAction* getExitAction() const { return m_exitAction; }

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
};

#endif // MAINLAYOUT_H
