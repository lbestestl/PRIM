/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef LOGIN_H
#define LOGIN_H


#include <QDialog>
#include <QRegExpValidator>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    
private:
    void initWidgets();
    void connectWidgets();
    Ui::Login *ui;
    QValidator *validator;
    bool isLoginState;

private slots:
    void passwordLengthCheck(QString);
    void loginButtonClicked();
    void cancelButtonClicked();
    void registerButtonClicked();
};


#endif // LOGIN_H
