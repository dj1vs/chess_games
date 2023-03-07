#include "loginwidget.h"

#include <QLabel>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
        loginButton = new QPushButton("Login");

        login = new QLineEdit;
        password = new QLineEdit;
        password->setEchoMode(QLineEdit::Password);

        layout = new QGridLayout(this);
        layout->addWidget(new QLabel("АСС Шахматные партии"), 0, 0, 1, 2);
        layout->addWidget(new QLabel("Login:"), 1, 0, 1, 1);
        layout->addWidget(login, 1, 1, 1, 1);
        layout->addWidget(new QLabel("Password:"), 2, 0, 1, 1);
        layout->addWidget(password, 2, 1, 1, 1);
        layout->addWidget(loginButton, 3, 0, 1, 2);

        layout->setRowStretch(0, false);

        connect(loginButton, &QPushButton::clicked, this, [this] {emit authorize();});
        
}

LoginWidget::~LoginWidget() {

}

QPair <QString, QString> LoginWidget::getUserInputs() {
    return {login->text(), password->text()};
}
