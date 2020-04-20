#include "Mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
{
    // this is the Widget that will be shown when drawing
    m_drawingArea = new DrawingArea;
    m_drawingArea->resize(1000, 500);

//    QGridLayout *mainLayout = new QGridLayout;
    m_mainLayout = new MainLayout(m_drawingArea, this);

    // setting the WIDGET.LAYOUT<a WIDGET will contain 1MAIN-LAYOUT
    // the same as QMainWindow that contains a single 1MAIN-LAYOUT
    setLayout(m_mainLayout);

    // SET WINDOW PARAMETERS
    setWindowTitle(tr("Drawpat"));
    QWidget::resize(500, 500);

    initializeConnects();
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
        // the event will be refused
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

void MainWindow::initializeConnects()
{
    connect(m_mainLayout->getCreateAction(), &QAction::triggered, this, &MainWindow::create);
    connect(m_mainLayout->getOpenAction(), &QAction::triggered, this, &MainWindow::open);

    QList<QAction *> &saveAsActions = m_mainLayout->getSaveAsActions();
    int i = 0;
    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        connect(saveAsActions.at(i), &QAction::triggered, this, &MainWindow::save);
        i++;
    }

    connect(m_mainLayout->getExitAction(), &QAction::triggered, this, &QWidget::close);
    connect(m_mainLayout->getPenColorAction(), &QAction::triggered, this, &MainWindow::editPenColor);
    connect(m_mainLayout->getPenWidthAction(), &QAction::triggered, this, &MainWindow::editPenWidth);
    connect(m_mainLayout->getClearDrawingAreaAction(), &QAction::triggered, m_drawingArea, &DrawingArea::clearImage);
    connect(m_mainLayout->getAboutAction(), &QAction::triggered, this, &MainWindow::showAbout);
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
        else if (option == QMessageBox::Discard)
        {
            retVal = true;
        }
        else if (option == QMessageBox::Cancel)
        {
            retVal = false;
        }

    }

    return retVal;
}
