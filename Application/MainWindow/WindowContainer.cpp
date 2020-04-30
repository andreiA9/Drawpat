#include "WindowContainer.h"
#include <QFile>
#include <QUrl>

WindowContainer::WindowContainer(QWidget *parent)
{
}

WindowContainer::~WindowContainer()
{
    delete m_saveAsMenu;
    delete m_fileMenu;
    delete m_optionMenu;
    delete m_helpMenu;

    delete m_upperButton0;
    delete m_upperButton1;
    delete m_upperButton2;
    delete m_upperButton3;
    delete m_upperButton4;

    // daca pui asta > ai CRASH
    // INTREBARE: cine sterge acest LAYOUT ???
    // in EXMPLUL.lor > nu exista COD pentru stergerea acestor OBIECTE
    // pentru ca el a fost adaugat la QGridLayout
//    delete m_horizontalLayout;
}

void WindowContainer::initializeMainLayout()
{
    m_gridLayout = new QGridLayout(this);
    // NU SE STIE CE FAC
//    m_gridLayout->setColumnStretch(0, 1);
//    m_gridLayout->setColumnStretch(3, 1);
    m_gridLayout->setContentsMargins(10, 30, 10, 10);
    /* ECHIVALENT cu
    m_mainLayout->setGeometry(QRect(10, 100, 781, 521)); */

    // this means that the DrawingArea will expand on all-columns
    // of the LAYOUT
    m_gridLayout->addWidget(m_centralWidget, 1, 0, 1, 4);


    initializeControlButtons();


    // setting the WIDGET.LAYOUT<a WIDGET will contain 1MAIN-LAYOUT
    // the same as QMainWindow that contains a single 1MAIN-LAYOUT
    setLayout(m_gridLayout);
}

void WindowContainer::initializeControlButtons()
{
    m_upperButton0 = new QPushButton(this);
    m_upperButton1 = new QPushButton(this);
    m_upperButton2 = new QPushButton(this);
    m_upperButton3 = new QPushButton(this);
    m_upperButton4 = new QPushButton(this);

    m_upperButton0->setObjectName(QString("pushButton0"));
    m_upperButton0->setText("Button0");
    m_upperButton0->setGeometry(QRect(20, 30, 80, 25));

    m_upperButton1->setObjectName(QString("pushButton1"));
    m_upperButton1->setText("Button1");
    m_upperButton1->setGeometry(QRect(110, 30, 80, 25));

    m_upperButton2->setObjectName(QString("pushButton2"));
    m_upperButton2->setText("Button2");
    m_upperButton2->setGeometry(QRect(200, 30, 80, 25));

    m_upperButton3->setObjectName(QString("pushButton3"));
    m_upperButton3->setText("Button3");
    m_upperButton3->setGeometry(QRect(290, 30, 80, 25));

    m_upperButton4->setObjectName(QString("pushButton4"));
    m_upperButton4->setText("Button4");
    m_upperButton4->setGeometry(QRect(380, 30, 80, 25));

    // addLayout(QLayout * layout, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = 0)
    QHBoxLayout *m_horizontalLayout = new QHBoxLayout();
    m_horizontalLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->addLayout(m_horizontalLayout, 0, 0, 1, 3);

    m_horizontalLayout->setObjectName(QString("verticalLayout"));
    m_horizontalLayout->addWidget(m_upperButton1);
    m_horizontalLayout->addWidget(m_upperButton0);
    m_horizontalLayout->addWidget(m_upperButton2);
    m_horizontalLayout->addWidget(m_upperButton3);
    m_horizontalLayout->addWidget(m_upperButton4);
}

void WindowContainer::initializeStatusBar()
{
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusBar"));
    m_statusbar->showMessage(QString("A inceput aplicatia"), 3000);
    m_statusbar->setGeometry(QRect(10, 761, 781, 20));
    m_gridLayout->addWidget(m_statusbar, 2, 0, 1, 4);
}

void WindowContainer::createFileMenu()
{
    m_newAction = new QAction(tr("&New"), this);
    m_newAction->setShortcuts(QKeySequence::New);
//    m_newAction->setIcon(QIcon(QUrl::fromLocalFile("Icons/new-file-96.png").toString()));
    m_newAction->setIcon(QIcon(QString("qrc:/icons/Icons/new-file-96.png")));
//    m_newAction->setIcon(QIcon(QString("qrc:/icons/new-file-96.png")));
//                                       "qrc:/prodlogqmlresources/icons/icons/18x18-ladeeinheit.svg"
//    m_newAction->setIcon(QIcon(QString("C:\\Programe\\Drawpat-cmake\\Application\\Icons\\new-file-96.png")));
    m_newAction->setIconVisibleInMenu(true);

    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setIcon(QIcon(QString("qrc:/icons/Icons/open-file-96.png")));

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
    QIcon icon2;
    m_saveAsMenu->setIcon(QIcon(QString(":/icons/icons/save-as-file-96.png")));

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/exit-96.png")));

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
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/cut-text-96.png")));

    m_editCopyAction = new QAction(tr("&Copy"), this);
    m_editCopyAction->setShortcuts(QKeySequence::Copy);
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/copy-text-96.png")));

    m_editPasteAction = new QAction(tr("&Paste"), this);
    m_editPasteAction->setShortcuts(QKeySequence::Paste);
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/paste-text-96.png")));

    m_editUndoAction = new QAction(tr("&Undo"), this);
    m_editUndoAction->setShortcuts(QKeySequence::Undo);
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/undo-96.png")));

    m_editRedoAction = new QAction(tr("&Redo"), this);
    m_editRedoAction->setShortcuts(QKeySequence::Redo);
    m_exitAction->setIcon(QIcon(QString(":/icons/icons/redo-96.png")));

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

    m_gridLayout->setMenuBar(m_menuBar);
}
