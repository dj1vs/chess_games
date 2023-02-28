#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

class UserWidget : public QWidget {
    Q_OBJECT
public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
};
#endif //USERWIDGET_H