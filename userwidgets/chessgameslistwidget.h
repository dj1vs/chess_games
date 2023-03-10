#ifndef CHESSGAMESLISTWIDGET_H
#define CHESSGAMESLISTWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QTextBrowser>
#include <QTableWidget>

#include <QVBoxLayout>
#include <QGridLayout>

class ChessGamesListWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessGamesListWidget(FormWidget *parent = nullptr);
    ~ChessGamesListWidget();
private:
    void setMaxInd() {curInd = worker->getMaxGameID();};
    void loadPage();

    QLineEdit *date, *whiteName, *blackName, *format, *timeControl, *opening, *result; 
    QTextBrowser *moves;
    QLineEdit *whiteRating, *blackRating;
    QTableView *ratingDifs;


    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //CHESSGAMESLISTWIDGET_H
