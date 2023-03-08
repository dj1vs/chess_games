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

#include <QSqlQuery>

#include <QVector>

using namespace QtCharts;


class ChessplayersStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersStatsWidget(FormWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
private:
    void setMaxInd() {QSqlQuery query("SELECT MAX(chessplayer_id) FROM chessplayers");
    if (query.next()) {
        curInd = query.value(0).toInt();
    }};
    void loadPage();
    void loadBasicFields();
    void loadColorAmountFields(QString color);
    inline void loadAmountFields();
    void loadColorGamesTable(QString color);
    inline void loadGamesTables();
    void loadColorOpeningsTable(QString color);
    inline void loadOpeningsTables();
    void loadStrongestOpponentsTable();
    void loadColorOpeningsChart(QString color);
    inline void loadOpeningsCharts();
    void loadChessplayers();

    QSqlQuery query;

    QLineEdit *search;
    QLineEdit *name;
    QSpinBox *rating;
    QSpinBox *birthYear;
    QSpinBox *amount;
    QSpinBox *wins;
    QSpinBox *loses;
    QSpinBox *draws;
    QTableView *gamesWhite;
    QTableView *gamesBlack;
    QSpinBox *amountWhite;
    QSpinBox *winsWhite;
    QSpinBox *losesWhite;
    QSpinBox *drawsWhite;
    QSpinBox *amountBlack;
    QSpinBox *winsBlack;
    QSpinBox *losesBlack;
    QSpinBox *drawsBlack;
    QTableView *openingsWhite;
    QTableView *openingsBlack;
    QChartView *whiteOpeningsGraph;
    QChartView *blackOpeningsGraph;
    QTableView *strongestOponents;

    QCompleter *searchCompleter;
    QStringList chessplayers;

};
#endif //CHESSPLAYERSSTATSWIDGET_H
