#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtPrintSupport/QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionCreate_triggered();
    void on_actionPage_settings_triggered();
    void on_actionFont_triggered();
    void on_actionPrint_triggered();
    void on_textEdit_textChanged();
    //edit
    void on_actionChoose_everything_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionUndo_triggered();
    void on_actionDate_and_time_triggered();
    void on_actionDelete_triggered();
    void on_actionFind_triggered();
    void on_actionFind_next_triggered();
    void on_actionFind_previous_triggered();
    void on_actionGo_to_triggered();
    void on_actionReplace_triggered();
    void on_actionSearch_with_Bing_triggered();
    //view
    void on_actionWord_Wrap_triggered(bool checked);
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QString _filename;
    bool _saved;
    bool _existing;
    QPrinter _printer;
};
#endif // MAINWINDOW_H
