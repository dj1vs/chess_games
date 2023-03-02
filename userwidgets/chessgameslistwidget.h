#ifndef CHESSGAMESLISTWIDGET_H
#define CHESSGAMESLISTWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QTextBrowser>
#include <QSpinBox>
#include <QTableWidget>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QSqlQuery>

class ChessGamesListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessGamesListWidget(QWidget *parent = nullptr);
    ~ChessGamesListWidget();
private:
    void loadFromDB();
    quint32 curInd = 1;
    FormHeader *formHeader;

    QLineEdit *date, *whiteName, *blackName, *format, *timeControl, *opening; 
    QTextBrowser *moves;
    QSpinBox *whiteRating, *blackRating;
    QTableView *ratingDifs;


    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //CHESSGAMESLISTWIDGET_H