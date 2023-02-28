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
        
}

LoginWidget::~LoginWidget() {
    delete loginButton;
    delete loginLineEdit, loginLabel, loginLayout;
    delete passwordLabel, passwordLayout, passwordLineEdit;
    delete titleLabel;
    delete layout;
}
