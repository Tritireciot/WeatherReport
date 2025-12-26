#pragma once

#include<QDialog>
#include<QLineEdit>

class QLineEdit;

class AuthDialog:public QDialog{
    Q_OBJECT

    private:
        QLineEdit* login;
        QLineEdit* password;
    
    public:
        AuthDialog(QWidget* pwgt = nullptr);

        QString getLogin() const;
        QString getPassword() const;
};