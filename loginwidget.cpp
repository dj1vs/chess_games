#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
        loginButton = new QPushButton("Login");

        layout = new QVBoxLayout;
        layout->addWidget(loginButton);

        setLayout(layout);
        
}
