#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

#include <QFormLayout>
#include <QVBoxLayout>

#include <QSqlQuery>

class ChessplayersWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(FormWidget *parent = nullptr);
    ~ChessplayersWidget();
private:
    void loadPage();

    QLineEdit *name;
    QSpinBox *id, *rating, *birthYear;


    QFormLayout *pageLayout;
    QVBoxLayout *mainLayout;
};
#endif //CHESSPLAYERSWIDGET_H
