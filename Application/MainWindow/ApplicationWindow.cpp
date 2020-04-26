#include "ApplicationWindow.h"



ApplicationWindow::ApplicationWindow(QWidget *parent)
{
    // SET WINDOW PARAMETERS
    setWindowTitle(tr("Drawpat"));
    QWidget::resize(800, 600);

    initializeMainLayout();

    initializeMenuConnects();

    drawButton();

    initializeStatusBar();
}

ApplicationWindow::~ApplicationWindow()
{
//    delete ui;
    delete m_editorModule;
}

void ApplicationWindow::drawButton()
{
    // Create the button, make "this" the parent
    m_button = new QPushButton("My Button", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(100, 30)));

    // Connect button signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &ApplicationWindow::handleButton);
}

void ApplicationWindow::initializeMainLayout()
{
    Events *events = new Events;

    // this is the Widget that will be shown when drawing
    //    QWidget *drawingArea = new DrawingView;
    DrawingView *drawingArea = new DrawingView(events, this);
    drawingArea->resize(700, 400);
    m_editorModule = new EditorModule(drawingArea, events);
    m_centralWidget = drawingArea;

    m_mainLayout = new MainLayout(m_centralWidget, this);
    m_mainLayout->setContentsMargins(10, 30, 10, 10);
    /* ECHIVALENT cu
    m_mainLayout->setGeometry(QRect(10, 100, 781, 521)); */

    initializeControlButtons();

    // setting the WIDGET.LAYOUT<a WIDGET will contain 1MAIN-LAYOUT
    // the same as QMainWindow that contains a single 1MAIN-LAYOUT
    setLayout(m_mainLayout);
}

void ApplicationWindow::initializeMenuConnects()
{
    connect(m_mainLayout->m_newAction, &QAction::triggered, m_editorModule, &EditorModule::create);
    connect(m_mainLayout->m_openAction, &QAction::triggered, this, &ApplicationWindow::open);

    QList<QAction *> &saveAsActions = m_mainLayout->m_saveAsActions;
    int i = 0;
    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        connect(saveAsActions.at(i), &QAction::triggered, this, &ApplicationWindow::save);
        i++;
    }

    connect(m_mainLayout->m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_mainLayout->m_penColorAction, &QAction::triggered, this, &ApplicationWindow::editPenColor);
    connect(m_mainLayout->m_penWidthAction, &QAction::triggered, this, &ApplicationWindow::editPenWidth);
    connect(m_mainLayout->m_clearDrawingAreaAction, &QAction::triggered, m_editorModule, &EditorModule::clear);
    connect(m_mainLayout->m_aboutAction, &QAction::triggered, this, &ApplicationWindow::showAbout);
}

void ApplicationWindow::initializeControlButtons()
{
    QPushButton *upperButton0 = new QPushButton(this);
    QPushButton *upperButton1 = new QPushButton(this);
    QPushButton *upperButton2 = new QPushButton(this);
    QPushButton *upperButton3 = new QPushButton(this);
    QPushButton *upperButton4 = new QPushButton(this);

    m_mainLayout->setControlButtons(upperButton0,
                                    upperButton1,
                                    upperButton2,
                                    upperButton3,
                                    upperButton4);

//    connect(m_mainLayout->getUpperButton4(), &QPushButton::pressed, this, &ApplicationWindow::handleButton, Qt::DirectConnection);
    connect(m_mainLayout->m_upperButton4, &QPushButton::released, this, &ApplicationWindow::handleButton, Qt::DirectConnection);
}

void ApplicationWindow::handleButton()
{
    QCoreApplication::processEvents();
    m_editorModule->rotationTriggered(true);
}

void ApplicationWindow::initializeStatusBar()
{
    QStatusBar *statusbar = new QStatusBar(this);
    m_mainLayout->setStatusBar(statusbar);
}

void ApplicationWindow::closeEvent(QCloseEvent *event)
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

void ApplicationWindow::open()
{
    // DE REZOLVAT
    if (trySave())
    {
        // open a Dialog Box
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open File"),
            QDir::currentPath());

        if (!fileName.isEmpty())
        {
            m_editorModule->setFileName(fileName);
            m_editorModule->openFile();
        }
    }
}

void ApplicationWindow::save()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    QByteArray fileFormat = action->data().toByteArray();

    QString initialPath = QDir::currentPath();
    QUrl fileUrl = QFileDialog::getSaveFileUrl(this,
                                            initialPath,
                                            tr("%1 Files (*.%2);; All FIles(*)")
                                            .arg(QString::fromLatin1(fileFormat.toUpper()))
                                            .arg(QString::fromLatin1(fileFormat)));

    m_editorModule->setFileName(fileUrl.fileName());
    m_editorModule->saveFile(fileFormat);
}

void ApplicationWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("About Scribble"),
                       tr("<p>The <b>Scribble</b> application</p>"));
}

bool ApplicationWindow::trySave()
{
    bool retVal = true;

    if (m_editorModule->isDirty())
    {

        QMessageBox::StandardButton option;
        option = QMessageBox::warning(this,
                                      tr("Scribble"),
                                      tr("Your file was not saved.\n"
                                         "Do you want to save it ?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (option == QMessageBox::Save)
        {
            m_editorModule->create();
            retVal = m_editorModule->saveFile("png");
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

void ApplicationWindow::editPenColor()
{
    // getColor(iniatialColor from m_scribbleArea)
    QColor newColor = QColorDialog::getColor(m_editorModule->getPenColor());

    if (newColor.isValid())
    {
        m_editorModule->setPenColor(newColor);
    }
}

void ApplicationWindow::editPenWidth()
{
    // if BUTTON = OK was being pressed
    bool okPressed;

    int newWidth = QInputDialog::getInt(this,
                                        tr("Scribble"),
                                        tr("Select pen width: "),
                                        m_editorModule->getPenWidth(),
                                        1, 50, 1, &okPressed);     // minimumValue, maximumValue, step, ok = show OK BUTTON

    if (okPressed)
    {
        m_editorModule->setPenWidth(newWidth);
    }
}
