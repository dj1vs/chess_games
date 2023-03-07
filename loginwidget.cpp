#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
        loginButton = new QPushButton("Login");

        login = new QLineEdit;
        password = new QLineEdit;
        password->setEchoMode(QLineEdit::Password);

        titleLabel = new QLabel("АСС Шахматные партии");
        titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


        layout = new QFormLayout(this);
        layout->addWidget(titleLabel);
        layout->addRow("Login:", login);
        layout->addRow("Password:", password);
        layout->addWidget(loginButton);

        connect(loginButton, &QPushButton::clicked, this, [this] {emit authorize();});
        
}

LoginWidget::~LoginWidget() {

}

QPair <QString, QString> LoginWidget::getUserInputs() {
    return {login->text(), password->text()};
}
