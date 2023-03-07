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

#include <QCompleter>

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
    void loadTournaments();

    QLineEdit *search, *tournamentName, *winnersName, *judgesName, *country, *city;
    QSpinBox *ratingRestriction, *gamesAmount;
    QTableView *strongestPlayersWhite, *strongestPlayersBlack;
    QChartView *results;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

    QCompleter *searchCompleter;
    QStringList tournametns;

};
#endif //TOURNAMENTSSTATSWIDGET_H
