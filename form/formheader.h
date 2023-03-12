#ifndef FORMHEADER_H
#define FORMHEADER_H
#include <QWidget>
#include <QApplication>
#include <QStyle>

#include <QPushButton>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

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
    void beginning();
    void ending();
    void print();
private:
    QPushButton *exitButton, *prevButton, *nextButton, *beginningButton, *endingButton, *printButton;
    QLabel *titleLabel;

    QHBoxLayout *buttonsLayout;
    QVBoxLayout *mainLayout;
};
#endif
