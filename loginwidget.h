#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    QPushButton *loginButton;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLabel *titleLabel;

    QHBoxLayout *loginLayout;
    QHBoxLayout *passwordLayout;
    QVBoxLayout *layout;

signals:

};

#endif // LOGINWIDGET_H
