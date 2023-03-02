#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QSqlDatabase>
#include <QScrollArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void processAuthorization(QPair <QString, QString> authorizationParams);

    void setupUser();
    void setupAdmin();

    QSqlDatabase db;

    QMenuBar *menu;
    QAction *about;
    QAction *quit;
};
#endif // MAINWINDOW_H
