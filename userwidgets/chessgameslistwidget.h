#ifndef CHESSGAMESLISTWIDGET_H
#define CHESSGAMESLISTWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QTextBrowser>
#include <QSpinBox>
#include <QTableWidget>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QSqlQuery>

class ChessGamesListWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessGamesListWidget(FormWidget *parent = nullptr);
    ~ChessGamesListWidget();
private:
    void loadPage();

    QLineEdit *date, *whiteName, *blackName, *format, *timeControl, *opening; 
    QTextBrowser *moves;
    QSpinBox *whiteRating, *blackRating;
    QTableView *ratingDifs;


    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //CHESSGAMESLISTWIDGET_H
