#include "mainwindow.h"

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
    connect(loginWidget, &LoginWidget::authorize, this, [this, loginWidget] {qDebug() << loginWidget->getUserInputs();});
}

MainWindow::~MainWindow() {
    delete about, quit;
    delete menu;
}

