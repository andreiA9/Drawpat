#include "MainLayout.h"

MainLayout::MainLayout(QWidget *drawingArea, QWidget *parent)
{
    QGridLayout::setColumnStretch(0, 1);
    QGridLayout::setColumnStretch(3, 1);
    // this means that the DrawingArea will expand on all-columns
    // of the LAYOUT
    QGridLayout::addWidget(drawingArea, 0, 0, 1, 4);

    createActions();
    createMenuBar();
}

void MainLayout::createActions()
{
    m_newAction = new QAction(tr("&New"), this);
    m_newAction->setShortcuts(QKeySequence::New);

    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence::Open);

    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format.toUpper()));
        QAction *action = new QAction(text, this);
        action->setData(format);
        m_saveAsActions.append(action);
    }

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);

    m_penColorAction = new QAction(tr("&Pen color"), this);

    m_penWidthAction = new QAction(tr("&Pen width"), this);

    m_clearDrawingAreaAction = new QAction(tr("&Clear screen"), this);
//    m_clearScreenAction->setShortcuts(tr("Ctrl + L"));

    m_aboutAction = new QAction(tr("&About"), this);
}

void MainLayout::createMenuBar()
{
    QMenuBar* menuBar = new QMenuBar();
    addMenuBarButtons(menuBar);

    this->setMenuBar(menuBar);
}

void MainLayout::addMenuBarButtons(QMenuBar* menuBar)
{
    m_saveAsMenu = new QMenu(tr("&Save as"), parentWidget());
    for (QAction *action : m_saveAsActions)
    {
        m_saveAsMenu->addAction(action);
    }

    m_fileMenu = new QMenu(tr("&File"), parentWidget());
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addMenu(m_saveAsMenu);
    // will add "-----------------" to the MENU
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_optionMenu = new QMenu(tr("&Option"), parentWidget());
    m_optionMenu->addAction(m_penColorAction);
    m_optionMenu->addAction(m_penWidthAction);
    m_optionMenu->addSeparator();
    m_optionMenu->addAction(m_clearDrawingAreaAction);

    m_helpMenu = new QMenu(tr("&Help"), parentWidget());
    m_helpMenu->addAction(m_aboutAction);

    menuBar->addMenu(m_fileMenu);
    menuBar->addMenu(m_optionMenu);
    menuBar->addMenu(m_helpMenu);
}

void MainLayout::setStatusBar(QStatusBar *statusBar)
{
    m_statusbar = statusBar;
}
