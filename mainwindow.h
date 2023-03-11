#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwidget.h"
#include "sqlworker.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QScrollArea>
#include <QThread>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void processAuthorization(QPair <QString, QString> authorizationParams);
    void initWorker();

    void setupMenu();
    void setupUser();
    void setupAdmin();

    inline void setScrollWidget(QWidget *w);

    SQLWorker *worker;
    QThread *workerThread;

    QMenuBar *menu;
    QAction *about;
    QAction *quit;
};
#endif // MAINWINDOW_H
