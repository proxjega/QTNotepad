#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QFont>
#include <QMessageBox>
#include "includeFunctions.h"
#include <QCloseEvent>
#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
//#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _saved = true;
    _existing = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered() {
    if(!_existing) {
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
    _saved = true;
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
    _existing = true;
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
    auto file = [this](const QString filename, const QString &content) {
        if(filename.isEmpty()) {
            return;
        }
        else {
            this->ui->textEdit->setPlainText(content);
            _filename = filename;
            _existing = true;
            _saved = true;
            this->setWindowTitle(getTitle(_filename));
        }
    };
    QFileDialog::getOpenFileContent(tr("Text Files (*.txt);;All Files (*)"), file);
}
void MainWindow::on_actionCreate_triggered(){
    this->ui->textEdit->setPlainText("");
    this->setWindowTitle("Untitled - qNotepad");
    _filename = "";
    _saved = false;
    _existing = false;
}
void MainWindow::on_actionPage_Settings_triggered(){

}

void MainWindow::on_actionPrint_triggered(){
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    if (dialog.exec() == QDialog::Accepted) {
        this->ui->textEdit->print(&printer);
    }
}

void MainWindow::on_textEdit_textChanged() {
    _saved = false;
    this->setWindowTitle("*" + getTitle(_filename));
}

void MainWindow:: on_actionWord_Wrap_triggered(bool checked){
    if(checked == true) this->ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    else this->ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(!_saved) {
        event->ignore();
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("Unsaved Changes");
        messageBox->setText("Do you want to save your changes?");
        messageBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        messageBox->setDefaultButton(QMessageBox::Yes);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setAttribute(Qt::WA_DeleteOnClose);
        messageBox->show();
        int res = messageBox->exec();
        switch(res){
        case QMessageBox::Yes:
            on_actionSave_triggered();
            event->accept();
            break;
        case QMessageBox::No:
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        }
    }
}
