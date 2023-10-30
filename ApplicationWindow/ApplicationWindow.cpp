#include "ApplicationWindow.h"

#include <QFileSystemModel>

static const char *IMAGES_PATH = "/Images";

ApplicationWindow::ApplicationWindow()
{
    // this is the Widget that will be shown when drawing
    QStackedWidget* stackedWorkArea = new QStackedWidget(this);
    m_editorModule = new EditorModule(stackedWorkArea);

    createMenuBar();
    initializeMenuConnects();

    initializeControlButtons();

    initializeBottomGrid();
    initializeDrawingViewAndTreeView(stackedWorkArea);

    initializeConnects();

    initializeStatusBar();
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::initializeMenuConnects()
{
    connect(m_newAction, &QAction::triggered, m_editorModule, &EditorModule::addFile);
    connect(m_openAction, &QAction::triggered, this, &ApplicationWindow::open);
    connect(m_saveAction, &QAction::triggered, this, &ApplicationWindow::save);

    int i = 0;
    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        connect(m_saveAsActions.at(i), &QAction::triggered, this, &ApplicationWindow::saveAs);
        i++;
    }

    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_penColorAction, &QAction::triggered, this, &ApplicationWindow::editPenColor);
    connect(m_penWidthAction, &QAction::triggered, this, &ApplicationWindow::editPenWidth);
    connect(m_clearDrawingAreaAction, &QAction::triggered, m_editorModule, &EditorModule::clear);

//    connect(m_aboutAction, &QAction::triggered, this, &ApplicationWindow::showAbout);
}

void ApplicationWindow::initializeConnects()
{
    connect(m_filesTreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ApplicationWindow::getTreeViewSelection);

    connect(m_penButton0, &QPushButton::released, this, &ApplicationWindow::handleFunction);
    connect(m_selectButton1, &QPushButton::released, this, &ApplicationWindow::handleFunction);
    connect(m_writeButton2, &QPushButton::released, this, &ApplicationWindow::handleFunction);
    connect(m_rotateButton4, &QPushButton::released, this, &ApplicationWindow::handleFunction);
}

void ApplicationWindow::handleFunction()
{
    QObject* sender = QObject::sender();
    if      (sender == m_penButton0)
    {
        m_editorModule->drawingTriggered();
    }
    else if (sender == m_selectButton1)
    {
        m_editorModule->selectionTriggered();
    }
    else if (sender == m_writeButton2)
    {
        m_editorModule->writingTriggered();
    }
    else if (sender == m_rotateButton4)
    {
        m_editorModule->rotationTriggered();
    }
}

void ApplicationWindow::getTreeViewSelection()
{
    qDebug() << "DA";
    QModelIndexList indexes = m_filesTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_filesTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QString filePath = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << filePath;
        m_editorModule->loadImage(filePath);
    }
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
        QString path = QDir::currentPath() + IMAGES_PATH;
        // open a Dialog Box
        QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open File"),
            path);

        if (!fileName.isEmpty())
        {
            m_editorModule->loadImage(fileName);
        }
    }
}

void ApplicationWindow::save()
{

}

void ApplicationWindow::saveAs()
{
    QAction *action = qobject_cast<QAction*>(QObject::sender());
    QByteArray fileFormat = action->data().toByteArray();

    QString path = QDir::currentPath() + IMAGES_PATH;
    QUrl fileUrl = QFileDialog::getSaveFileUrl(this,
                                            QString(),
                                            path,
                                            tr("%1 Files (*.%2);; All FIles(*)")
                                            .arg(QString::fromLatin1(fileFormat.toUpper()))
                                            .arg(QString::fromLatin1(fileFormat)));

    m_editorModule->saveImage(fileUrl.toLocalFile(), fileFormat);
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
                                      tr("Drawpat"),
                                      tr("Your file was not saved.\n"
                                         "Do you want to save it ?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (option == QMessageBox::Save)
        {
            QString newFileName = m_editorModule->generateNewFile();
            retVal = m_editorModule->saveImage(newFileName, "png");
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
