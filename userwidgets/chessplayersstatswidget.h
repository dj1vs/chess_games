#ifndef CHESSPLAYERSSTATSWIDGET_H
#define CHESSPLAYERSSTATSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QSpinBox>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QCompleter>

#include <QVector>

using namespace QtCharts;


class ChessplayersStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersStatsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
public:
    void loadChessplayer(DMap map);
private:
    void setMaxInd() {curInd = worker->getMaxChessplayerID();};
    void loadPage();
    void connectWorker();
    void loadBasicFields();
    void loadColorAmountFields();
    inline void loadAmountFields();
    inline void loadGamesTables();
    inline void loadOpeningsTables();
    void loadStrongestOpponentsTable();
    void loadColorOpeningsChart(QString color);
    inline void loadOpeningsCharts();

    QSqlQuery query;

    QLineEdit *search;
    QLineEdit *name;
    QSpinBox *rating, *birthYear;
    QSpinBox *amount, *wins, *loses, *draws;
    QTableView *gamesWhite, *gamesBlack;
    QSpinBox *amountWhite,*winsWhite, *losesWhite, *drawsWhite;
    QSpinBox *amountBlack,*winsBlack,*losesBlack,*drawsBlack;
    QTableView *openingsWhite, *openingsBlack;
    QChartView *whiteOpeningsGraph,*blackOpeningsGraph;
    QTableView *strongestOponents;

    QCompleter *searchCompleter;
signals:
    void getChessplayer(quint32 ind);

};
#endif //CHESSPLAYERSSTATSWIDGET_H
