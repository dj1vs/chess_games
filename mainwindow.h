#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwidget.h"
#include "sqlworker.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QScrollArea>
#include <QThread>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void processAuthResults(bool result);
private:
    void processAuthorization(QPair <QString, QString> authorizationParams);
    void initWorker();

    void setupMenu();
    void setupUser();
    void setupAdmin();

    inline void setScrollWidget(QWidget *w);

    SQLWorker *worker;
    QThread *workerThread;

    QString login, pass;

    QMenuBar *menu;
    QAction *about;
    QAction *quit;
signals:
    void getAuthResult(QString login, QString pass);
};
#endif // MAINWINDOW_H
