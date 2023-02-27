#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);
}

MainWindow::~MainWindow()
{
}

