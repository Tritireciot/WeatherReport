#include "AuthDialog.h"

#include <QtWidgets>

AuthDialog::AuthDialog(QWidget* pwgt): QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint){
    login = new QLineEdit;
    password = new QLineEdit;

    QLabel* loginLabel = new QLabel("Логин");
    QLabel* passwordLabel = new QLabel("АпиКлюч");

    loginLabel->setBuddy(login);
    passwordLabel->setBuddy(password);

    QPushButton* okButton = new QPushButton("Ок");
    QPushButton* cancelButton = new QPushButton("Отменить");

    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));

    QGridLayout* formLayout = new QGridLayout;
    formLayout->addWidget(loginLabel, 0, 0);
    formLayout->addWidget(login, 0, 1);
    formLayout->addWidget(passwordLabel, 1, 0);
    formLayout->addWidget(password, 1, 1);
    formLayout->addWidget(okButton, 2, 0);
    formLayout->addWidget(cancelButton, 2, 1);
    setLayout(formLayout);
}

QString AuthDialog::getLogin() const {
    return login->text();
}
QString AuthDialog::getPassword() const {
    return password->text();
}