#ifndef ApplicationWindow_H
#define ApplicationWindow_H

// QT WIDGETS
#include <QWidget>
#include <QImageWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

// QT
#include <QList>

// USER-DEFINED
#include "MainLayout.h"
#include "../EditorModule/EditorModule.h"



class DrawingView;


//QT_BEGIN_NAMESPACE
//namespace Ui { class ApplicationWindow; }
//QT_END_NAMESPACE

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget *parent = nullptr);
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

    /** \brief depending on the ACTION that was being pressed>the
      *        FILE is being saved in the corresponding FORMAT
      */
    void save();

    void editPenColor();
    void editPenWidth();

    // FUNCTIONS = ABOUT
    void showAbout();

    void handleButton();

private:
    void drawButton();

    /** \brief the CONNECTIONS from MainLayout are made here
      */
    void initializeMenuConnects();

    /** \brief the interraction BUTTONS are put here
      */
    void initializeUpperButtons();

    /** \brief add the STATUS BAR to the MainLayout
      */
    void initializeStatusBar();

    /** \brief the user cannot[0 = open a file/1 = close the application]
      *        if the current file was not saved
      */
    bool trySave();
    bool saveFile(const QByteArray &fileFormat);

private:
//    Ui::ApplicationWindow *ui;
    MainLayout *m_mainLayout;
    EditorModule * m_editorModule;
    QPushButton *m_button;
};
#endif // ApplicationWindow_H
