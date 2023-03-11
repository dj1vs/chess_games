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

#include <QCompleter>

using namespace QtCharts;
class TournamentsStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit TournamentsStatsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~TournamentsStatsWidget();
private:
    void setMaxInd() {curInd = worker->getMaxTournamentID();};
    void loadPage();
    void loadBasics();
    void loadChart();
    void loadTables();

    QLineEdit *search, *tournamentName, *winnersName, *judgesName, *country, *city;
    QLineEdit *ratingRestriction;
    QSpinBox *gamesAmount;
    QTableView *strongestPlayersWhite, *strongestPlayersBlack;
    QChartView *results;

    QCompleter *searchCompleter;
    QStringList tournaments;

};
#endif //TOURNAMENTSSTATSWIDGET_H
