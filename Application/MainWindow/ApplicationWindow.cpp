#include "ApplicationWindow.h"



ApplicationWindow::ApplicationWindow()
{
    // SET WINDOW PARAMETERS
    setWindowTitle(tr("Drawpat"));
    QWidget::resize(800, 600);

    QStackedWidget* container = new QStackedWidget(this);

    m_editorView = new EditorView(container);

    initializeMainLayout();

    createFileMenu();
    createMenuBar();

    initializeMenuConnects();

    initializeButtonsConnects();

    initializeStatusBar();
}

ApplicationWindow::~ApplicationWindow()
{
    delete m_editorModule;
    delete m_editorView;
}

void ApplicationWindow::initializeButtonsConnects()
{
    connect(m_upperButton4, &QPushButton::released, this, &ApplicationWindow::handleButton);
}

void ApplicationWindow::initializeMenuConnects()
{
    connect(m_newAction, &QAction::triggered, m_editorModule, &EditorModule::create);
    connect(m_openAction, &QAction::triggered, this, &ApplicationWindow::open);

    int i = 0;
    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        connect(m_saveAsActions.at(i), &QAction::triggered, this, &ApplicationWindow::save);
        i++;
    }

    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_penColorAction, &QAction::triggered, this, &ApplicationWindow::editPenColor);
    connect(m_penWidthAction, &QAction::triggered, this, &ApplicationWindow::editPenWidth);
    connect(m_clearDrawingAreaAction, &QAction::triggered, m_editorModule, &EditorModule::clear);
    connect(m_aboutAction, &QAction::triggered, this, &ApplicationWindow::showAbout);
}

void ApplicationWindow::handleButton()
{
    qDebug() << "process";
    m_editorModule->rotationTriggered(true);
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
