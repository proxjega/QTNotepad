#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QFont>
#include <QMessageBox>
#include "includeFunctions.h"
int main(int argc, char *argv[]);
//#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    this->setWindowTitle(getTitle(_filename));
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
    this->setWindowTitle(getTitle(_filename));
}

void MainWindow::on_actionFont_triggered() {
    bool ok;
    auto font = QFontDialog::getFont(&ok, this->ui->textEdit);
    if (ok) {
        this->ui->textEdit->setFont(font);
    }
    else {
        return;
    }
}

void MainWindow::on_actionNew_triggered() {
    MainWindow *newWindow = new MainWindow();
    newWindow->setAttribute( Qt::WA_DeleteOnClose);
    newWindow->show();
}

void MainWindow::on_actionOpen_triggered(){

}
void MainWindow::on_actionCreate_triggered(){

}
void MainWindow::on_actionPage_Settings_triggered(){

}

void MainWindow::on_actionPrint_triggered(){

}


