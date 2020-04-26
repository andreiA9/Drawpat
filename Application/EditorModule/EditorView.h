#ifndef EDITORVIEW_H
#define EDITORVIEW_H

// WIDGETS
#include <QWidget>
#include <QPushButton>



class EditorView : public QWidget
{
    Q_OBJECT

public:
    EditorView(QWidget *parent = nullptr);

    void initializeTabs();

private:
    QPushButton *tab0;
    QPushButton *tab1;
    QPushButton *tab2;
    QPushButton *tab3;
    QPushButton *tab4;
};

#endif // EDITORVIEW_H
