#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwidget.h"
#include "sqlworker.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QScrollArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void processAuthorization(QPair <QString, QString> authorizationParams);

    void setupMenu();
    void setupUser();
    void setupAdmin();

    inline void setScrollWidget(QWidget *w);

    SQLWorker *worker;

    QMenuBar *menu;
    QAction *about;
    QAction *quit;
};
#endif // MAINWINDOW_H
