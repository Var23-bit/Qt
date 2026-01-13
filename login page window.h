#ifndef LOGIN_MAIN_H
#define LOGIN_MAIN_H

#include <QMainWindow>

namespace Ui {
class login_main;
}

class login_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit login_main(QWidget *parent = nullptr);
    ~login_main();

private:
    Ui::login_main *ui;
};

#endif // LOGIN_MAIN_H
