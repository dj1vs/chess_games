#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);

private:
    QPushButton *loginButton;

    QVBoxLayout *layout;

signals:

};

#endif // LOGINWIDGET_H
