#include "tournamentsstatswidget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

TournamentsStatsWidget::TournamentsStatsWidget(FormWidget *parent):
    FormWidget{parent} {
        formHeader = new FormHeader();
        formHeader->setTitle("Tournaments statistics");

        search = new QLineEdit();
        tournamentName = new QLineEdit();
        winnersName = new QLineEdit();
        judgesName = new QLineEdit();
        country = new QLineEdit();
        city = new QLineEdit();
        
        ratingRestriction = new QLineEdit();
        gamesAmount = new QSpinBox();

        results = new QChartView;

        tournamentName->setReadOnly(true);
        winnersName->setReadOnly(true);
        judgesName->setReadOnly(true);
        country->setReadOnly(true);
        city->setReadOnly(true);
        ratingRestriction->setReadOnly(true);
        gamesAmount->setReadOnly(true);

        strongestPlayersBlack = new QTableView;
        strongestPlayersWhite = new QTableView;

        layout = new QVBoxLayout(this);
        layout->addWidget(formHeader);
        layout->addWidget(new QLabel("Search:"));
        layout->addWidget(search);
        layout->addWidget(new QLabel("Tournament name:"));
        layout->addWidget(tournamentName);
        layout->addWidget(new QLabel("Rating restriction:"));
        layout->addWidget(ratingRestriction);
        layout->addWidget(new QLabel("Winner:"));
        layout->addWidget(winnersName);
        layout->addWidget(new QLabel("Judge:"));
        layout->addWidget(judgesName);
        layout->addWidget(new QLabel("Tournament location:"));
        layout->addWidget(new QLabel("Country:"));
        layout->addWidget(country);
        layout->addWidget(new QLabel("City:"));
        layout->addWidget(city);
        layout->addWidget(new QLabel("Games played:"));
        layout->addWidget(gamesAmount);
        layout->addWidget(results);
        layout->addWidget(new QLabel("Strongest players as white:"));
        layout->addWidget(strongestPlayersWhite);
        layout->addWidget(new QLabel("Strongest players as black:"));
        layout->addWidget(strongestPlayersBlack);

        connectFormHeader();
        initWorker();


        loadPage();

        searchCompleter = new QCompleter(worker->getAllTournamentsNames(), this);
        search->setCompleter(searchCompleter);

        connect(search, &QLineEdit::returnPressed, this, [this] {
            quint32 id = worker->getTournamentID(search->text());
            
            if (id != -1) {
                curInd = id;
                loadPage();
            } else {
                showSearchError();
                search->clear();
            }
        });
}

TournamentsStatsWidget::~TournamentsStatsWidget() {
    
}

inline void TournamentsStatsWidget::loadPage() {
    loadBasics();
    loadChart();
    loadTables();
}

void TournamentsStatsWidget::loadBasics() {
    auto map = worker->getTournament(curInd);
    tournamentName->setText(map["name"]);
    ratingRestriction->setText(map["rating_restriction"]);
    winnersName->setText(map["winner"]);
    judgesName->setText(map["judge"]);
    city->setText(map["city"]);
    country->setText(map["country"]);

    gamesAmount->setValue(worker->getTournamentGamesAmount(curInd));

}
void TournamentsStatsWidget::loadChart() {
    quint32 whiteWins = worker->getTournamentWinsAmount(curInd, "white");
    quint32 blackWins = worker->getTournamentWinsAmount(curInd, "black");
    quint32 draws = gamesAmount->value() - whiteWins - blackWins;

    QPieSeries *series = new QPieSeries;
    series->append("White wins", whiteWins);
    series->append("Black wins", blackWins);
    series->append("Draws", draws);

    QChart *chart = new QChart;
    chart->addSeries(series);

    results->setChart(chart);
    results->setMinimumHeight(300);
    results->show();
}
void TournamentsStatsWidget::loadTables() {
    strongestPlayersWhite->setModel(worker->getBestTournamentPlayers(curInd, "white"));
    resizeTableView(strongestPlayersWhite);
    strongestPlayersWhite->show();

    strongestPlayersBlack->setModel(worker->getBestTournamentPlayers(curInd, "black"));
    resizeTableView(strongestPlayersBlack);
    strongestPlayersBlack->show();
}
