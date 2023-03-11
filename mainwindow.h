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
    void test(const QMap<QString, QVariant> &ind) {qDebug() << 1;}
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
signals:
    void get(const QMap<QString, QVariant> &ind);
};
#endif // MAINWINDOW_H
