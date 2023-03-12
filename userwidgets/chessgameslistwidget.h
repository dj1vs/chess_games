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
    explicit ChessGamesListWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~ChessGamesListWidget();
public slots:
    void loadGame(DMap map);
    void loadGamesCrossRequest(DTable table);
    void loadAllChessplayersNames(QStringList names);
private:
    //void setMaxInd() {curInd = worker->getMaxGameID();};
    void loadPage();
    void connectWorker();

    QLineEdit *date, *whiteName, *blackName, *format, *timeControl, *opening, *result; 
    QTextBrowser *moves;
    QLineEdit *whiteRating, *blackRating;
    QTableView *ratingDifs;

    QStringList chessplayersNames;
signals:
    void getGame(quint32 ind);
    void getGamesCrossRequest();
    void getAllChessplayersNames();
};
#endif //CHESSGAMESLISTWIDGET_H
