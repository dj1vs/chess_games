#include "tournamentsstatswidget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

TournamentsStatsWidget::TournamentsStatsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

        formHeader = new FormHeader();
        formHeader->setTitle("Стутистика по турнирам");

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
        layout->addWidget(new QLabel("Поиск по названию"));
        layout->addWidget(search);
        layout->addWidget(new QLabel("Название"));
        layout->addWidget(tournamentName);
        layout->addWidget(new QLabel("Ограничение рейтинга"));
        layout->addWidget(ratingRestriction);
        layout->addWidget(new QLabel("Победитель"));
        layout->addWidget(winnersName);
        layout->addWidget(new QLabel("Судья"));
        layout->addWidget(judgesName);
        layout->addWidget(new QLabel("Место проведения турнира"));
        layout->addWidget(new QLabel("Страна"));
        layout->addWidget(country);
        layout->addWidget(new QLabel("Город"));
        layout->addWidget(city);
        layout->addWidget(new QLabel("Игр сыграно"));
        layout->addWidget(gamesAmount);
        layout->addWidget(results);
        layout->addWidget(new QLabel("Сильнейшие шахматисты на белых фигурах"));
        layout->addWidget(strongestPlayersWhite);
        layout->addWidget(new QLabel("Сильнейшие шахматисты на чёрных фигурах"));
        layout->addWidget(strongestPlayersBlack);

        connectFormHeader();
        connectWorker();
        
        emit getTournaments();

        loadPage();

        connect(search, &QLineEdit::returnPressed, this, [this] {
            emit getSearchID(search->text());
        });
}

TournamentsStatsWidget::~TournamentsStatsWidget() {   
}

void TournamentsStatsWidget::loadTournaments(QStringList names) {
    searchCompleter = new QCompleter(names);
    search->setCompleter(searchCompleter);

}
void TournamentsStatsWidget::loadTournamentGamesAmount(quint32 amount) {
    gamesAmount->setValue(amount);
}
void TournamentsStatsWidget::loadTournamentWinsAmount(quint32 amount, QString color) {
    if (color == "white") {
        whiteWins = amount;
    } else {
        blackWins = amount;
        loadChart();
    }
}
void TournamentsStatsWidget::processSearchID(quint32 id) {
    if (id != -1) {
        curInd = id;
        loadPage();
    } else {
        showSearchError();
        search->clear();
    }
}
void TournamentsStatsWidget::loadTournament(DMap map) {
    tournamentName->setText(map["name"].toString());
    ratingRestriction->setText(map["rating_restriction"].toString());
    winnersName->setText(map["winner"].toString());
    judgesName->setText(map["judge"].toString());
    city->setText(map["city"].toString());
    country->setText(map["country"].toString());
}

void TournamentsStatsWidget::loadBestTournamentPlayers(DTable table, QString color) {
    QTableView *view = (color == "white" ? strongestPlayersWhite : strongestPlayersBlack);
    view->setModel(DTableToModel(table,\
        {"Имя", "Рейтинг", "Побед"}));
    resizeTableView(view);
    view->show();   
}

void TournamentsStatsWidget::connectWorker() {
    connect(this, &TournamentsStatsWidget::getTournament, worker, &SQLWorker::getTournament);
    connect(worker, &SQLWorker::tournamentReady, this, &TournamentsStatsWidget::loadTournament);

    connect(this, &TournamentsStatsWidget::getBestTournamentsPlayers, worker, &SQLWorker::getBestTournamentPlayers);
    connect(worker, &SQLWorker::bestTournamentPlayersReady, this, &TournamentsStatsWidget::loadBestTournamentPlayers);

    connect(this, &TournamentsStatsWidget::getSearchID, worker, &SQLWorker::getTournamentID);
    connect(worker, &SQLWorker::tournamentIDReady, this, &TournamentsStatsWidget::processSearchID);
    connect(this, &TournamentsStatsWidget::getTournamentGamesAmount, worker, &SQLWorker::getTournamentGamesAmount);
    connect(worker, &SQLWorker::tournamentGamesAmountReady, this, &TournamentsStatsWidget::loadTournamentGamesAmount);
    connect(this, &TournamentsStatsWidget::getTournamentWinsAmount, worker, &SQLWorker::getTournamentWinsAmount);
    connect(worker, &SQLWorker::tournamentWinsAmountReady, this, &TournamentsStatsWidget::loadTournamentWinsAmount);


    connect(this, &TournamentsStatsWidget::setMaxInd, worker, &SQLWorker::getMaxTournamentID);
    connect(worker, &SQLWorker::maxTournamentIDReady, this, &TournamentsStatsWidget::loadMaxInd);
}

inline void TournamentsStatsWidget::loadPage() {
    loadBasics();
    emit getTournamentWinsAmount(curInd, "white");
    emit getTournamentWinsAmount(curInd, "black");
    loadTables();
}

void TournamentsStatsWidget::loadBasics() {
    emit getTournament(curInd);

    emit getTournamentGamesAmount(curInd);

}
void TournamentsStatsWidget::loadChart() {
    quint32 draws = gamesAmount->value() - whiteWins - blackWins;

    QPieSeries *series = new QPieSeries;
    series->setHoleSize(0.35);
    series->append("Побед за белых", whiteWins);
    series->append("Побед за чёрных", blackWins);
    series->append("Ничьих", draws);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Исходы партий на турнире");

    results->setChart(chart);
    results->setMinimumHeight(300);
    results->show();
}
void TournamentsStatsWidget::loadTables() {
    emit getBestTournamentsPlayers(curInd, "white");
    emit getBestTournamentsPlayers(curInd, "black");
}
