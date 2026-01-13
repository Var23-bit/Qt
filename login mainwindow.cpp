#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QMessageBox>
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

void MainWindow::on_login_btn_clicked()
{
    QString Username=ui->lineEdituser->text();
    QString password=ui->lineEdit_pass->text();

    if(Username=="varun" && password == "code"){
        hide();
        login_success = new login_main(this);
        login_success->show();
    }else{
        QMessageBox::critical(this,"Login failed","Username or password are incorrect");
    }
}

