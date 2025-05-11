#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "includeFunctions.h"
//#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _font = QFont("Arial", 12);
    _saved = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered() {
    if(!_saved) {
        on_actionSave_as_triggered();
    }
    else {
        QFile file(_filename);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << this->ui->textEdit->toPlainText();
        file.close();
        QMessageBox::information(this, tr("File Saved"), tr("File saved successfully!"));
    }
    //set title
    this->setWindowTitle(getTitle(_filename) + " - qNotepad");
}

void MainWindow:: on_actionSave_as_triggered() {
    auto filename = QFileDialog::getSaveFileName(this, tr("Save File"),
    "", tr("Text Files (*.txt);;All Files (*)"));
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QTextStream out(&file);
    out << this->ui->textEdit->toPlainText();
    file.close();
    QMessageBox::information(this, tr("File Saved"), tr("File saved successfully!"));
    _filename = filename;
    _saved = true;
    //set title
    this->setWindowTitle(getTitle(_filename) + " - qNotepad");
}



