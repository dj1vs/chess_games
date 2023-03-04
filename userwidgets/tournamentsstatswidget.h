#ifndef TOURNAMENTSSTATSWIDGET_H
#define TOURNAMENTSSTATSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include <QTableView>

#include <QChart>
#include <QChartView>

#include <QGridLayout>
#include <QVBoxLayout>

using namespace QtCharts;
class TournamentsStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit TournamentsStatsWidget(FormWidget *parent = nullptr);
    ~TournamentsStatsWidget();
private:
    void loadPage();
    void loadBasics();
    void loadGameAmount();
    void loadChart();
    void loadTables();

    QLineEdit *search, *tournamentName, *winnersName, *judgesName, *country, *city;
    QSpinBox *ratingRestriction, *gamesAmount;
    QTableView *strongestPlayersWhite, *strongestPlayersBlack;
    QChartView *results;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //TOURNAMENTSSTATSWIDGET_H
