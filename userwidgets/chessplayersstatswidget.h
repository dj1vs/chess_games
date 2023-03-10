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
    explicit ChessplayersStatsWidget(FormWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
private:
    void setMaxInd() {curInd = worker->getMaxChessplayerID();};
    void loadPage();
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
    QLineEdit *rating;
    QLineEdit *birthYear;
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
