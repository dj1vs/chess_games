#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwidget.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QMenuBar *menu;
    QAction *about;
    QAction *quit;
};
#endif // MAINWINDOW_H
