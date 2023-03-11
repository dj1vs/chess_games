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
public slots:
    void loadTournament(DMap map);
private:    
    void setMaxInd() {curInd = worker->getMaxTournamentID();};
    void loadPage();
    void connectWorker();
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
signals:
    void getTournament(quint32 ind);

};
#endif //TOURNAMENTSSTATSWIDGET_H
