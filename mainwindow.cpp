#include "mainwindow.h"
#include "userwidget.h"
#include "adminwidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);

    about = new QAction(tr("About"));
    quit = new QAction(tr("Exit"));


    menu = new QMenuBar;

    menu->addAction(about);
    menu->addAction(quit);

    this->setMenuBar(menu);
    this->setWindowTitle("Chess games");

    connect(about, &QAction::triggered, this, [this] {
        QMessageBox msg;
        msg.setWindowTitle("About");
        msg.setText("(c) Djivs 2023\ngithub.com/Djivs");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    });
    connect(quit, &QAction::triggered, this, [this] {
        this->close();
    });
    connect(loginWidget, &LoginWidget::authorize, this, [this, loginWidget] {
        processAuthorization(loginWidget->getUserInputs());
        });

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("chess_games");
    db.setUserName("postgres");
    db.setPassword("123");

    if (db.open()) {
        qDebug() << "Auth db successfully opened";
    } else {
        qDebug() << "Can't connect to auth db";
    }

    
}

MainWindow::~MainWindow() {
    delete about, quit;
    delete menu;
}

void MainWindow::processAuthorization(QPair <QString, QString> authorizationParams) {
    const QString login = authorizationParams.first;
    const QString pass = authorizationParams.second;

    QSqlQuery query("SELECT pass FROM users WHERE login = \'" + login + "\';");
    int count = 0;
    bool isAuthorized = false;
    while(query.next()) {
        if (query.value(0).toString() == pass) {
            ++count;
            isAuthorized = true;
        }
    }

    if (isAuthorized && count == 1) {
        qDebug() << "Successfully logged in as " + login;
    } else {
        qDebug() << "Auth failed";
    }

    if (login == "admin") {
        AdminWidget *adminWidget = new AdminWidget();
        setCentralWidget(adminWidget);
    } else if (login == "user") {
        UserWidget *userWidget = new UserWidget();
        setCentralWidget(userWidget);
    }

}

