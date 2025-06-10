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
#include <QPageSetupDialog>
#include <QInputDialog>
#include <QDesktopServices>
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
        this->setWindowTitle(getTitle(_filename));
        _saved = true;
    }
    //set title

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
void MainWindow::on_actionPage_settings_triggered(){
    QPageSetupDialog *pageSetupDialog = new QPageSetupDialog( &_printer, this);
    pageSetupDialog->setWindowTitle(tr("Page Setup"));
    pageSetupDialog->setAttribute(Qt::WA_DeleteOnClose);
    pageSetupDialog->show();
    connect(pageSetupDialog, &QPageSetupDialog::accepted, this, [=]() {
        QMessageBox::information(this, tr("Page Setup"), tr("Page setup completed!"));
    });
}

void MainWindow::on_actionPrint_triggered() {
    QPrintDialog dialog(&_printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    if (dialog.exec() == QDialog::Accepted) {
        this->ui->textEdit->print(&_printer);
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
//edit
void MainWindow::on_actionChoose_everything_triggered() {
    this->ui->textEdit->selectAll();
}

void MainWindow::on_actionCut_triggered() {
    this->ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered() {
    this->ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered() {
    this->ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered() {
    this->ui->textEdit->undo();
}

void MainWindow::on_actionDelete_triggered() {
    this->ui->textEdit->textCursor().removeSelectedText();
}
void MainWindow::on_actionFind_triggered() {
    QString searchText = QInputDialog::getText(this, tr("Find"), tr("Enter text to find:"));
    if (!searchText.isEmpty()) {
        QTextCursor cursor = this->ui->textEdit->textCursor();
        cursor = this->ui->textEdit->document()->find(searchText, cursor);
        if (!cursor.isNull()) {
            this->ui->textEdit->setTextCursor(cursor);
        } else {
            QMessageBox::information(this, tr("Not Found"), tr("Text not found."));
        }
    }
}

void MainWindow::on_actionFind_next_triggered() {
    QString searchText = QInputDialog::getText(this, tr("Find Next"), tr("Enter text to find:"));
    if (!searchText.isEmpty()) {
        QTextCursor cursor = this->ui->textEdit->textCursor();
        cursor = this->ui->textEdit->document()->find(searchText, cursor);
        if (!cursor.isNull()) {
            this->ui->textEdit->setTextCursor(cursor);
        } else {
            QMessageBox::information(this, tr("Not Found"), tr("Text not found."));
        }
    }
}

void MainWindow::on_actionFind_previous_triggered() {
    QString searchText = QInputDialog::getText(this, tr("Find Previous"), tr("Enter text to find:"));
    if (!searchText.isEmpty()) {
        QTextCursor cursor = this->ui->textEdit->textCursor();
        cursor = this->ui->textEdit->document()->find(searchText, cursor, QTextDocument::FindBackward);
        if (!cursor.isNull()) {
            this->ui->textEdit->setTextCursor(cursor);
        } else {
            QMessageBox::information(this, tr("Not Found"), tr("Text not found."));
        }
    }
}

void MainWindow::on_actionDate_and_time_triggered() {
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    this->ui->textEdit->insertPlainText(dateTime);
}

void MainWindow::on_actionGo_to_triggered() {
    bool ok;
    int lineNumber = QInputDialog::getInt(this, tr("Go to Line"), tr("Line number:"), 1, 1, this->ui->textEdit->document()->lineCount(), 1, &ok);
    if (ok) {
        QTextCursor cursor = this->ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber - 1);
        this->ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::on_actionReplace_triggered() {
    QString findText = QInputDialog::getText(this, tr("Find"), tr("Enter text to find:"));
    if (findText.isEmpty()) return;

    QString replaceText = QInputDialog::getText(this, tr("Replace"), tr("Enter text to replace with:"));
    if (replaceText.isEmpty()) return;

    QTextDocument *document = this->ui->textEdit->document();
    QTextCursor cursor = document->find(findText);
    while (!cursor.isNull()) {
        cursor.insertText(replaceText);
        cursor = document->find(findText, cursor);
    }
}

void MainWindow::on_actionSearch_with_Bing_triggered() {
    QString searchText = this->ui->textEdit->textCursor().selectedText();
    if (!searchText.isEmpty()) {
        QString url = QString("https://www.bing.com/search?q=%1").arg(QUrl::toPercentEncoding(searchText));
        QDesktopServices::openUrl(QUrl(url));
    }
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
