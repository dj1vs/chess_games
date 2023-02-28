#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
        loginButton = new QPushButton("Login");

        loginLineEdit = new QLineEdit;
        passwordLineEdit = new QLineEdit;
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        loginLabel = new QLabel("Login:");
        passwordLabel = new QLabel("Password:");
        titleLabel = new QLabel("АСС Шахматные партии");

        loginLayout = new QHBoxLayout();
        loginLayout->addWidget(loginLabel);
        loginLayout->addWidget(loginLineEdit);

        passwordLayout = new QHBoxLayout();
        passwordLayout->addWidget(passwordLabel);
        passwordLayout->addWidget(passwordLineEdit);

        layout = new QVBoxLayout;
        layout->addWidget(titleLabel);
        layout->addLayout(loginLayout);
        layout->addLayout(passwordLayout);
        layout->addWidget(loginButton);

        setLayout(layout);

        connect(loginButton, &QPushButton::clicked, this, [this] {emit authorize();});
        
}

LoginWidget::~LoginWidget() {
    delete loginButton;
    delete loginLineEdit, loginLabel, loginLayout;
    delete passwordLabel, passwordLayout, passwordLineEdit;
    delete titleLabel;
    delete layout;
}

QPair <QString, QString> LoginWidget::getUserInputs() {
    return {loginLineEdit->text(), passwordLineEdit->text()};
}
