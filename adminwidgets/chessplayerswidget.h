#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>

#include <QFormLayout>
#include <QVBoxLayout>

#include <QSqlQuery>

class ChessplayersWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(QWidget *parent = nullptr);
    ~ChessplayersWidget();
signals:
    void exit();
private:
    void fillFields();

    quint32 currentIndex = 1;

    FormHeader *formHeader;

    QLineEdit *name;
    QSpinBox *id, *rating, *birthYear;


    QFormLayout *pageLayout;
    QVBoxLayout *mainLayout;
};
#endif //CHESSPLAYERSWIDGET_H