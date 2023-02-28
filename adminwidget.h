#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>

class AdminWidget : public QWidget {
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = nullptr);
    ~AdminWidget();
};


#endif //ADMINWIDGET_H