#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
//#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
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
}

void MainWindow:: on_actionSave_triggered() {
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

}



