#ifndef CHESSGAMESLISTWIDGET_H
#define CHESSGAMESLISTWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QTableView>

#include <QVBoxLayout>
#include <QGridLayout>

class ChessGamesListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessGamesListWidget(QWidget *parent = nullptr);
    ~ChessGamesListWidget();
private:
    FormHeader *formHeader;

    QLineEdit *date, *whiteName, *blackName, *format, *timeControl, *opening; 
    QTextBrowser *moves;
    QComboBox *whiteRating, *blackRating;
    QTableView *ratingDifs;


    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //CHESSGAMESLISTWIDGET_H