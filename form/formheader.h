#ifndef FORMHEADER_H
#define FORMHEADER_H
#include <QWidget>
#include <QApplication>
#include <QStyle>

#include <QPushButton>
#include <QLabel>

#include <QHBoxLayout>

class FormHeader : public QWidget {
    Q_OBJECT
public:
    explicit FormHeader(QWidget *parent = nullptr);
    ~FormHeader();

    void setTitle(QString title) {titleLabel->setText(title);}
signals:
    void exit();
    void prev();
    void next();
    void print();
private:
    QPushButton *exitButton, *prevButton, *nextButton, *printButton;
    QLabel *titleLabel;

    QHBoxLayout *layout;
};
#endif