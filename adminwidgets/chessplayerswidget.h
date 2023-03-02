#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QComboBox>

#include <QFormLayout>
#include <QVBoxLayout>

class ChessplayersWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(QWidget *parent = nullptr);
    ~ChessplayersWidget();
private:
    FormHeader *formHeader;

    QLineEdit *name;
    QComboBox *id, *rating, *birthYear;


    QFormLayout *pageLayout;
    QVBoxLayout *mainLayout;
};
#endif //CHESSPLAYERSWIDGET_H