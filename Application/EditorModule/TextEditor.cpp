#include "TextEditor.h"



TextEditor::TextEditor(QWidget *parent)
{
    QTextEdit *textEdit;
    textEdit = new QTextEdit(this);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
}
