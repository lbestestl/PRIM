/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef LOGIN_H
#define LOGIN_H


#include <QDialog>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    bool isCorrectPw();
    
private:
    void connectWidgets();
    Ui::Login *ui;

private slots:
    void loginButtonClicked();
    void cancelButtonClicked();
    void modifyButtonClicked();
};


#endif // LOGIN_H
