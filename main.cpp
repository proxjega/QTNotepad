#include "mainwindow.h"
#include <QTextEdit>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    // QTextEdit *textEdit = new QTextEdit();
    // textEdit->setGeometry(10, 10, 400, 300);
    // textEdit->setFont(QFont("Arial", 12));
    // textEdit->show();
    w.show();
    return a.exec();
}
