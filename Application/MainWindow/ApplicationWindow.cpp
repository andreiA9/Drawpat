#include "ApplicationWindow.h"
//#include "ui_mainwindow.h"



ApplicationWindow::ApplicationWindow(QWidget *parent)
{
    // SET WINDOW PARAMETERS
    setWindowTitle(tr("Drawpat"));
    QWidget::resize(800, 600);

    Events *events = new Events;

    // this is the Widget that will be shown when drawing
//    QWidget *drawingArea = new DrawingView;
    DrawingView *drawingArea = new DrawingView(events, this);
    drawingArea->resize(700, 500);
    m_editorModule = new EditorModule(drawingArea, events);

    m_mainLayout = new MainLayout(drawingArea, this);
    m_mainLayout->setGeometry(QRect(10, 100, 781, 521));
    // setting the WIDGET.LAYOUT<a WIDGET will contain 1MAIN-LAYOUT
    // the same as QMainWindow that contains a single 1MAIN-LAYOUT
    setLayout(m_mainLayout);

    initializeMenuConnects();

    drawButton();

    initializeUpperButtons();

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

void ApplicationWindow::handleButton()
{
    m_editorModule->rotationTriggered(true);
}

void ApplicationWindow::initializeMenuConnects()
{
    connect(m_mainLayout->getCreateAction(), &QAction::triggered, m_editorModule, &EditorModule::create);
    connect(m_mainLayout->getOpenAction(), &QAction::triggered, this, &ApplicationWindow::open);

    QList<QAction *> &saveAsActions = m_mainLayout->getSaveAsActions();
    int i = 0;
    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        connect(saveAsActions.at(i), &QAction::triggered, this, &ApplicationWindow::save);
        i++;
    }

    connect(m_mainLayout->getExitAction(), &QAction::triggered, this, &QWidget::close);
    connect(m_mainLayout->getPenColorAction(), &QAction::triggered, this, &ApplicationWindow::editPenColor);
    connect(m_mainLayout->getPenWidthAction(), &QAction::triggered, this, &ApplicationWindow::editPenWidth);
    connect(m_mainLayout->getClearDrawingAreaAction(), &QAction::triggered, m_editorModule, &EditorModule::clear);
    connect(m_mainLayout->getAboutAction(), &QAction::triggered, this, &ApplicationWindow::showAbout);
}

void ApplicationWindow::initializeUpperButtons()
{
    QPushButton *upperButton0 = new QPushButton(this);

    QPushButton *upperButton1 = new QPushButton(this);

    QPushButton *upperButton2 = new QPushButton(this);

    QPushButton *upperButton3 = new QPushButton(this);

    QPushButton *upperButton4 = new QPushButton(this);
    upperButton0->setObjectName(QString("pushButton0"));
    upperButton0->setText("Button0");
    upperButton0->setGeometry(QRect(20, 10, 80, 25));

    upperButton1->setObjectName(QString("pushButton1"));
    upperButton1->setText("Button1");
    upperButton1->setGeometry(QRect(110, 10, 80, 25));

    upperButton2->setObjectName(QString("pushButton2"));
    upperButton2->setText("Button2");
    upperButton2->setGeometry(QRect(200, 10, 80, 25));

    upperButton3->setObjectName(QString("pushButton3"));
    upperButton3->setText("Button3");
    upperButton3->setGeometry(QRect(290, 10, 80, 25));

    upperButton4->setObjectName(QString("pushButton4"));
    upperButton4->setText("Button5");
    upperButton4->setGeometry(QRect(380, 10, 80, 25));
}

void ApplicationWindow::initializeStatusBar()
{
    QStatusBar *statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusBar"));
    statusbar->showMessage(QString("A inceput aplicatia"), 3000);
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
