#include "Mainwindow.h"
#include "ui_mainwindow.h"

// QT
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QImageWriter>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_drawingArea = new DrawingArea;

    // this is the Widget that will be shown when drawing
    setCentralWidget(m_drawingArea);
    setWindowTitle(tr("Drawpat"));

    createActions();
    createMenus();

    QWidget::resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trySave())
    {
        // the event will be accepted
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::create()
{
    QString fileName = "Untitled.txt";
    m_drawingArea->setFileName(fileName);
}

void MainWindow::open()
{
    if (trySave())
    {
        // open a Dialog Box
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open File"),
            QDir::currentPath());

        if (!fileName.isEmpty())
        {
            m_drawingArea->setFileName(fileName);
            m_drawingArea->openImage(fileName);
        }
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    QByteArray fileFormat = action->data().toByteArray();

    m_drawingArea->saveFile(fileFormat);
}

void MainWindow::editPenColor()
{
    // getColor(iniatialColor from m_scribbleArea)
    QColor newColor = QColorDialog::getColor(m_drawingArea->getPenColor());

    if (newColor.isValid())
    {
        m_drawingArea->setPenColor(newColor);
    }
}

void MainWindow::editPenWidth()
{
    // if BUTTON = OK was being pressed
    bool okPressed;

    int newWidth = QInputDialog::getInt(this,
                                        tr("Scribble"),
                                        tr("Select pen width: "),
                                        m_drawingArea->getPenWidth(),
                                        1, 50, 1, &okPressed);     // minimumValue, maximumValue, step, ok = show OK BUTTON

    if (okPressed)
    {
        m_drawingArea->setPenWidth(newWidth);
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("About Scribble"),
                       tr("<p>The <b>Scribble</b> application</p>"));
}

void MainWindow::createActions()
{
    m_createAction = new QAction(tr("New"), this);
    m_createAction->setShortcuts(QKeySequence::New);
    connect(m_createAction, &QAction::triggered, this, &MainWindow::create);

    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence::Open);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::open);

    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format.toUpper()));
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        m_saveAsActions.append(action);
    }

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    connect(m_exitAction, &QAction::triggered, this, &QMainWindow::close);

    m_penColorAction = new QAction(tr("&Pen color"), this);
    connect(m_penColorAction, &QAction::triggered, this, &MainWindow::editPenColor);

    m_penWidthAction = new QAction(tr("&Pen width"), this);
    connect(m_penWidthAction, &QAction::triggered, this, &MainWindow::editPenWidth);

    m_clearDrawingAreaAction = new QAction(tr("&Clear screen"), this);
//    m_clearScreenAction->setShortcuts(tr("Ctrl + L"));
    connect(m_clearDrawingAreaAction, &QAction::triggered, m_drawingArea, &DrawingArea::clearImage);

    m_aboutAction = new QAction(tr("&About"), this);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::createMenus()
{
    m_saveAsMenu = new QMenu(tr("&Save as"), this);
    for (QAction *action : m_saveAsActions)
    {
        m_saveAsMenu->addAction(action);
    }

    m_fileMenu = new QMenu(tr("&File"), this);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addMenu(m_saveAsMenu);
    // will add "-----------------" to the MENU
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_optionMenu = new QMenu(tr("&Option"), this);
    m_optionMenu->addAction(m_penColorAction);
    m_optionMenu->addAction(m_penWidthAction);
    m_optionMenu->addSeparator();
    m_optionMenu->addAction(m_clearDrawingAreaAction);

    m_helpMenu = new QMenu(tr("&Help"), this);
    m_helpMenu->addAction(m_aboutAction);

    QMenuBar *windowMenuBar = menuBar();
    windowMenuBar->addMenu(m_fileMenu);
    windowMenuBar->addMenu(m_optionMenu);
    windowMenuBar->addMenu(m_helpMenu);
}

bool MainWindow::trySave()
{
    bool retVal = true;

    if (m_drawingArea->isModified())
    {

        QMessageBox::StandardButton option;
        option = QMessageBox::warning(this,
                                      tr("Scribble"),
                                      tr("Your file was not saved.\n"
                                         "Do you want to save it ?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (option == QMessageBox::Save)
        {
            retVal = m_drawingArea->saveFile("png");
        }
        else
        {
            retVal = false;
        }

    }

    return retVal;
}
