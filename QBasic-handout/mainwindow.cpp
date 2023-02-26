#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <fstream>

list<QString> tree;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(load()));
    connect(ui->btnRunCode,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");
    if(cmd == "RUN")
    {
        run();
        return;
    }
    else if(cmd == "LOAD")
    {
        load();
        return;
    }
    else if(cmd == "List")
    {
        return;
    }
    else if(cmd == "CLEAR")
    {
        clear();
        return;
    }
    else if(cmd == "HELP")
    {
        qDebug()<<"Do you need help?";
        return;
    }
    BasicStr.push(cmd);
    ui->CodeDisplay->clear();
    list<NumState>::iterator itr1 = BasicStr.str.begin();
    list<NumState>::iterator itr2 = BasicStr.str.end();
    do
    {
        ui->CodeDisplay->append(QString::number((*itr1).num) + " " + (*itr1).statement);
        ++itr1;
    }while(itr1 != itr2);
}

void MainWindow::load()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("load txt"), "/home",tr("files(*.txt)"));
    ifstream loadFile(filename.toStdString());
    if(!loadFile.is_open())
    {
        qDebug() << "can't open this file";
        return ;
    }
    clear();
    string s1;
    while (getline(loadFile,s1))
    {
        QString s2 = QString::fromStdString(s1);
        BasicStr.push(s2);
    }
    list<NumState>::iterator itr1 = BasicStr.str.begin();
    list<NumState>::iterator itr2 = BasicStr.str.end();
    do
    {
        ui->CodeDisplay->append(QString::number((*itr1).num) + " " + (*itr1).statement);
        ++itr1;
    }while(itr1 != itr2);
}

void MainWindow::run()
{
    BasicStr.pro_run();
    list<QString>::iterator itr1 = tree.begin();
    list<QString>::iterator itr2 = tree.end();
    while(itr1 != itr2)
    {
        ui->treeDisplay->append((*itr1));
        ++itr1;
    }
    list<QString>::iterator itre1 = BasicStr.print.begin();
    list<QString>::iterator itre2 = BasicStr.print.end();
    while(itre1 != itre2)
    {
        ui->textBrowser->append(*itre1);
        ++itre1;
    }
}

void MainWindow::clear()
{
    BasicStr.pro_clear();
    ui->CodeDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();

}

