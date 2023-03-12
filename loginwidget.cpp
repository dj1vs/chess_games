#include "loginwidget.h"

#include <QLabel>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
        loginButton = new QPushButton("Войти");

        login = new QLineEdit;
        password = new QLineEdit;
        password->setEchoMode(QLineEdit::Password);
        title = new QLabel("АСС Шахматные партии");
        title->setFont(QFont("Consolas", 30, QFont::Bold));

        layout = new QGridLayout(this);
        layout->addWidget(title, 0, 0, 1, 2);
        layout->addWidget(new QLabel("Логин:"), 1, 0, 1, 1);
        layout->addWidget(login, 1, 1, 1, 1);
        layout->addWidget(new QLabel("Пароль:"), 2, 0, 1, 1);
        layout->addWidget(password, 2, 1, 1, 1);
        layout->addWidget(loginButton, 3, 0, 1, 2);

        connect(login, &QLineEdit::returnPressed, this, [this] {loginButton->click();});
        connect(password, &QLineEdit::returnPressed, this, [this] {loginButton->click();});

        connect(loginButton, &QPushButton::clicked, this, [this] {emit authorize();});
        
}

LoginWidget::~LoginWidget() {

}

QPair <QString, QString> LoginWidget::getUserInputs() {
    return {login->text(), password->text()};
}
