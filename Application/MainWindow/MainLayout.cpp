#include "MainLayout.h"

MainLayout::MainLayout(QWidget *centralWidget, QWidget *parent)
{
    QGridLayout::setColumnStretch(0, 1);
    QGridLayout::setColumnStretch(3, 1);
    // this means that the DrawingArea will expand on all-columns
    // of the LAYOUT
    QGridLayout::addWidget(centralWidget, 1, 0, 1, 4);

    createActions();
    createMenuBar();
}

MainLayout::~MainLayout()
{
    delete m_newAction;
    delete m_openAction;

    // delete from QList algorithm < go through all ELEMENTS
    // and only after incrementing to the FIRST POINTER > you
    // will be allowed to DELETE the PREVIOUS POINTER
    auto it = m_saveAsActions.begin();
    while (it != m_saveAsActions.end())
    {
        auto toBeDeleted = it;
        it++;
        delete *toBeDeleted;
    }
    delete m_penColorAction;
    delete m_penWidthAction;
    delete m_clearDrawingAreaAction;
    delete m_aboutAction;
    delete m_exitAction;

    delete m_saveAsMenu;
    delete m_fileMenu;
    delete m_optionMenu;
    delete m_helpMenu;

    delete m_horizontalLayout;
    delete m_upperButton0;
    delete m_upperButton1;
    delete m_upperButton2;
    delete m_upperButton3;
    delete m_upperButton4;
}

void MainLayout::setControlButtons(QPushButton *upperButton0,
                                   QPushButton *upperButton1,
                                   QPushButton *upperButton2,
                                   QPushButton *upperButton3,
                                   QPushButton *upperButton4)
{
    m_upperButton0 = upperButton0;
    m_upperButton1 = upperButton1;
    m_upperButton2 = upperButton2;
    m_upperButton3 = upperButton3;
    m_upperButton4 = upperButton4;

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
    this->addLayout(m_horizontalLayout, 0, 0, 1, 3);

    m_horizontalLayout->setObjectName(QString("verticalLayout"));
    m_horizontalLayout->addWidget(m_upperButton1);
    m_horizontalLayout->addWidget(m_upperButton0);
    m_horizontalLayout->addWidget(m_upperButton2);
    m_horizontalLayout->addWidget(m_upperButton3);
    m_horizontalLayout->addWidget(m_upperButton4);
}

void MainLayout::setStatusBar(QStatusBar *statusBar)
{
    m_statusbar = statusBar;
    m_statusbar->setObjectName(QString::fromUtf8("statusBar"));
    m_statusbar->showMessage(QString("A inceput aplicatia"), 3000);
    m_statusbar->setGeometry(QRect(10, 781, 781, 20));
    this->addWidget(m_statusbar, 2, 0, 1, 4);
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
