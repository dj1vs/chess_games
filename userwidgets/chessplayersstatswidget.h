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

#include <QSqlQuery>

#include <QVector>

#include <QVBoxLayout>
#include <QGridLayout>

using namespace QtCharts;


class ChessplayersStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersStatsWidget(FormWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
private:
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

    QVBoxLayout *mainLayout;
    QGridLayout *pageLayout;

};
#endif //CHESSPLAYERSSTATSWIDGET_H
