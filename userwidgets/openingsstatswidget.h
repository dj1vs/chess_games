#ifndef OPENINGSSTATSWIDGET_H
#define OPENINGSSTATSWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableView>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>

#include <QGridLayout>

using namespace QtCharts;


class OpeningsStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit OpeningsStatsWidget(QWidget *parent = nullptr);
    ~OpeningsStatsWidget();
private:
    QLineEdit *search, *name, *altName, *group, *moves, *namedAfter, *probability;
    QComboBox *amount, *whiteWins, *blackWins, *draws;
    QTableView *chessplayersWhite, *chessplayersBlack;
    QChartView *chartView;

    QPushButton *goBack, *prev, *next, *print;


    QGridLayout *layout;



};
#endif //OPENINGSSTATSWIDGET_H
