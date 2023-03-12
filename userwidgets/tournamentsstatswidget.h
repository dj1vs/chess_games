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
    void loadTournaments(QStringList names);
    void loadTournamentGamesAmount(quint32 amount);
    void loadTournamentWinsAmount(quint32 amount, QString color);
    void processSearchID(quint32 id);
    void loadBestTournamentPlayers(DTable table, QString color);
private:    
    //void setMaxInd() {curInd = worker->getMaxTournamentID();};
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

    quint32 whiteWins = 0, blackWins = 0;
signals:
    void getTournament(quint32 ind);
    void getTournaments();
    void getBestTournamentsPlayers(quint32 ind, QString color);
    void getSearchID(QString search);
    void getTournamentGamesAmount(quint32 ind);
    void getTournamentWinsAmount(quint32 ind, QString color);

};
#endif //TOURNAMENTSSTATSWIDGET_H
