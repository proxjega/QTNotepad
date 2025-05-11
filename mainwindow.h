#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionPage_Settings_triggered();
    void on_actionFont_triggered();
    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QString _filename;
    bool _saved;
};
#endif // MAINWINDOW_H
