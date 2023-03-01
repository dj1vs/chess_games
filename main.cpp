#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    if (!file.isOpen()) {
        qDebug() << file.errorString();
    }
    QString styleSheet = QLatin1String(file.readAll());

    a.setStyleSheet(styleSheet);
    
    MainWindow w;
    w.show();

    return a.exec();
}
