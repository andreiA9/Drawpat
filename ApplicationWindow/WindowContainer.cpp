#include "WindowContainer.h"

#include <QFile>
#include <QUrl>
#include <QFileSystemModel>

WindowContainer::WindowContainer(QWidget *parent)
{
    // SET WINDOW PARAMETERS
    setWindowTitle(tr("Drawpat"));
    QWidget::resize(1600, 800);

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    // this will set the margin from html, outside the layout
    m_mainLayout->setContentsMargins(0, 10, 0, 0);
    QWidget::setLayout(m_mainLayout);
}

WindowContainer::~WindowContainer()
{
    // daca pui asta > ai CRASH
    // INTREBARE: cine sterge acest LAYOUT ???
    // in EXMPLUL.lor > nu exista COD pentru stergerea acestor OBIECTE
    // pentru ca el a fost adaugat la QGridLayout
//    delete m_buttonLayout;
}

void WindowContainer::initializeControlButtons()
{
    // addLayout(QLayout * layout, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = 0)
    m_buttonLayout = new QHBoxLayout();
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addLayout(m_buttonLayout, 0, 0, 1, 8);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // AI RAMAS
    // 1. SPACING ul nu iti merge
    // 2. trebuie sa faci SIZE POLICY = EXPANDING pentru QIMAGE = DrawingView
    m_buttonLayout->setSpacing(20);

    m_penButton0 = new QPushButton(this);
    m_selectButton1 = new QPushButton(this);
    m_writeButton2 = new QPushButton(this);
    m_upperButton3 = new QPushButton(this);
    m_rotateButton4 = new QPushButton(this);

    m_penButton0->setObjectName(QString("penButton0"));
    m_penButton0->setIcon(QIcon(QString(":/icons-image/pen")));
    m_penButton0->setGeometry(QRect(20, 30, 40, 25));

    m_selectButton1->setObjectName(QString("selectButton1"));
    m_selectButton1->setIcon(QIcon(QString(":/icons-image/rect-selection")));
    m_selectButton1->setGeometry(QRect(110, 30, 40, 25));

    m_writeButton2->setObjectName(QString("pushButton2"));
    m_writeButton2->setText("Write");
    m_writeButton2->setGeometry(QRect(200, 30, 40, 25));

    m_upperButton3->setObjectName(QString("pushButton3"));
    m_upperButton3->setText("Button3");
    m_upperButton3->setGeometry(QRect(290, 30, 40, 25));

    m_rotateButton4->setObjectName(QString("pushButton4"));
    m_rotateButton4->setText("Rotate");
    m_rotateButton4->setGeometry(QRect(380, 30, 40, 25));

    m_buttonLayout->setObjectName(QString("verticalLayout"));
    m_buttonLayout->addWidget(m_penButton0);
    m_buttonLayout->addWidget(m_selectButton1);
    m_buttonLayout->addWidget(m_writeButton2);
    m_buttonLayout->addWidget(m_upperButton3);
    m_buttonLayout->addWidget(m_rotateButton4);
}

void WindowContainer::initializeBottomGrid()
{
    m_bottomGridWithoutSpacing = new QGridLayout(this);
    m_bottomGridWithoutSpacing->setObjectName(QString::fromUtf8("verticalLayout"));
    m_bottomGridWithoutSpacing->setContentsMargins(0, 0, 0, 0);
    m_bottomGridWithoutSpacing->setSpacing(0);

    m_tabsLayout = new QHBoxLayout(this);
    m_tabsLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    m_tabsLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* tab0 = new QLabel(this);
    tab0->setObjectName(QString("Tab0"));
    tab0->setText("Untitled");
    tab0->setGeometry(QRect(20, 10, 20, 25));
    // this is the border
    tab0->setFrameShape(QFrame::Box);
    // these are the colors for: background, text
    // vezi ca din pacate cu setColor zice de la
    // Qt ca nu este garantat sa mearga pe toate platformele
    tab0->setStyleSheet("QLabel { background-color : red; color : blue; }");
    m_tabsLayout->addWidget(tab0);
    m_tabVector.append(tab0);

    m_mainLayout->addLayout(m_bottomGridWithoutSpacing, 1, 0, 7, 8);
    m_bottomGridWithoutSpacing->addLayout(m_tabsLayout, 0, 3, 1, 8);
}

void WindowContainer::initializeDrawingViewAndTreeView(QStackedWidget* stackedWorkArea)
{
//    m_bottomLayout = new QHBoxLayout();
//    m_bottomLayout->setContentsMargins(0, 0, 0, 0);
//    // GRESIT
//    m_mainLayout->addLayout(m_bottomLayout, 1, 0, 7, 8);
//    m_bottomLayout->setSpacing(20);

    const QString resourcesPath = QDir::currentPath() + "/Images";
    // create the file system model
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    model->setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
    QStringList filter;
    filter << "*.jpg";
    filter << "*.jpeg";
    filter << "*.png";
    filter << "*.bmp";
    model->setNameFilters(filter);

    // create the tree view associated to that model
    m_filesTreeView = new QTreeView();
    m_filesTreeView->setModel(model);
    m_filesTreeView->setRootIndex(model->index(resourcesPath));
    // SET SIZE POLICY
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(6);
    sizePolicy.setHeightForWidth(m_filesTreeView->sizePolicy().hasHeightForWidth());
    m_filesTreeView->setSizePolicy(sizePolicy);
    m_bottomGridWithoutSpacing->addWidget(m_filesTreeView, 1, 0, 7, 3);

    // SET SIZE POLICY
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(6);
    sizePolicy1.setVerticalStretch(6);
    sizePolicy1.setHeightForWidth(stackedWorkArea->sizePolicy().hasHeightForWidth());
    stackedWorkArea->setSizePolicy(sizePolicy1);
    m_bottomGridWithoutSpacing->addWidget(stackedWorkArea, 1, 3, 7, 5);
}

void WindowContainer::initializeStatusBar()
{
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusBar"));
    m_statusbar->showMessage(QString("A inceput aplicatia"), 3000);
    m_statusbar->setGeometry(QRect(10, 761, 781, 20));
//    m_mainLayout->addWidget(m_statusbar, 8, 0, 1, 8);
}

void WindowContainer::createFileMenu()
{
    m_newAction = new QAction(tr("&New"), this);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setIcon(QIcon(QString(":/icons-edit/new-file")));

    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setIcon(QIcon(QString(":/icons-edit/open-file")));

    m_saveAction = new QAction(tr("&Save"), this);
    m_saveAction->setShortcut(QKeySequence::Save);
    m_openAction->setIcon(QIcon(QString(":/icons-edit/save-file")));

    for (QByteArray format : QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format.toUpper()));
        QAction *action = new QAction(text, this);
        action->setData(format);
        m_saveAsActions.append(action);
    }

    m_saveAsMenu = new QMenu(tr("&Save as"), parentWidget());
    for (QAction *action : m_saveAsActions)
    {
        m_saveAsMenu->addAction(action);
    }

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setIcon(QIcon(QString(":/../icons/exit")));

    m_fileMenu = new QMenu(tr("&File"), this);
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addMenu(m_saveAsMenu);
    // will add "-----------------" to the MENU
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);
}

void WindowContainer::createEditMenu()
{
    m_editCutAction = new QAction(tr("&Cut"), this);
    m_editCutAction->setShortcuts(QKeySequence::Cut);
    m_editCutAction->setIcon(QIcon(QString(":/icons/cut-text")));

    m_editCopyAction = new QAction(tr("&Copy"), this);
    m_editCopyAction->setShortcuts(QKeySequence::Copy);
    m_editCopyAction->setIcon(QIcon(QString(":/icons/copy-text")));

    m_editPasteAction = new QAction(tr("&Paste"), this);
    m_editPasteAction->setShortcuts(QKeySequence::Paste);
    m_editPasteAction->setIcon(QIcon(QString(":/icons/paste-text")));

    m_editUndoAction = new QAction(tr("&Undo"), this);
    m_editUndoAction->setShortcuts(QKeySequence::Undo);
    m_editUndoAction->setIcon(QIcon(QString(":/icons/undo")));

    m_editRedoAction = new QAction(tr("&Redo"), this);
    m_editRedoAction->setShortcuts(QKeySequence::Redo);
    m_editRedoAction->setIcon(QIcon(QString(":/icons/redo")));

    m_editMenu = new QMenu(tr("&Edit"), this);
    m_editMenu->addAction(m_editCutAction);
    m_editMenu->addAction(m_editCopyAction);
    m_editMenu->addAction(m_editPasteAction);
    m_editMenu->addAction(m_editUndoAction);
    m_editMenu->addAction(m_editRedoAction);
}

void WindowContainer::createOtherMenus()
{
    m_penColorAction = new QAction(tr("&Pen color"), this);

    m_penWidthAction = new QAction(tr("&Pen width"), this);

    m_clearDrawingAreaAction = new QAction(tr("&Clear screen"), this);
//    m_clearScreenAction->setShortcuts(tr("Ctrl + L"));

    m_aboutAction = new QAction(tr("&About"), this);

    m_optionMenu = new QMenu(tr("&Option"), this);
    m_optionMenu->addAction(m_penColorAction);
    m_optionMenu->addAction(m_penWidthAction);
    m_optionMenu->addSeparator();
    m_optionMenu->addAction(m_clearDrawingAreaAction);

    m_helpMenu = new QMenu(tr("&Help"), this);
    m_helpMenu->addAction(m_aboutAction);
}

void WindowContainer::createMenuBar()
{
    m_menuBar = new QMenuBar(this);
    createFileMenu();
    createEditMenu();
    createOtherMenus();

    m_menuBar->addMenu(m_fileMenu);
    m_menuBar->addMenu(m_editMenu);
    m_menuBar->addMenu(m_optionMenu);
    m_menuBar->addMenu(m_helpMenu);

    m_mainLayout->setMenuBar(m_menuBar);
}
