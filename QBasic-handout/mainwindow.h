#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "program.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    program BasicStr;

private slots:
    void on_cmdLineEdit_editingFinished();

    void load();
    void run();
    void clear();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
