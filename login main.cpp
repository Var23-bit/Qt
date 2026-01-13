#include "login_main.h"
#include "ui_login_main.h"

login_main::login_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login_main)
{
    ui->setupUi(this);
}

login_main::~login_main()
{
    delete ui;
}
