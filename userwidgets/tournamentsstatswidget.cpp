#include "tournamentsstatswidget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QSqlTableModel>
TournamentsStatsWidget::TournamentsStatsWidget(FormWidget *parent):
    FormWidget{parent} {
        formHeader = new FormHeader();
        formHeader->setTitle("Tournaments statistics");

        pageLayout = new QGridLayout();

        search = new QLineEdit();
        tournamentName = new QLineEdit();
        winnersName = new QLineEdit();
        judgesName = new QLineEdit();
        country = new QLineEdit();
        city = new QLineEdit();
        
        ratingRestriction = new QSpinBox();
        gamesAmount = new QSpinBox();

        results = new QChartView;

        strongestPlayersBlack = new QTableView;
        strongestPlayersWhite = new QTableView;

        pageLayout->addWidget(new QLabel("Search:"), 0, 0, 1, 1);
        pageLayout->addWidget(search, 0, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Tournament name:"), 1, 0, 1, 1);
        pageLayout->addWidget(tournamentName, 1, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Rating restriction:"), 2, 0, 1, 1);
        pageLayout->addWidget(ratingRestriction, 2, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Winner:"), 3, 0, 1, 1);
        pageLayout->addWidget(winnersName, 3, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Judge:"), 4, 0, 1, 1);
        pageLayout->addWidget(judgesName, 4, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Tournament location:"), 5, 0, 1, 4);
        pageLayout->addWidget(new QLabel("Country:"), 6, 0, 1, 1);
        pageLayout->addWidget(country, 6, 1, 1, 1);
        pageLayout->addWidget(new QLabel("City:"), 6, 2, 1, 1);
        pageLayout->addWidget(city, 6, 3, 1, 1);
        pageLayout->addWidget(new QLabel("Games played:"), 7, 0, 1, 1);
        pageLayout->addWidget(gamesAmount, 7, 1, 1, 1);
        pageLayout->addWidget(results, 8, 0, 1, 4);
        pageLayout->addWidget(new QLabel("Strongest players as white:"), 9, 0, 1, 1);
        pageLayout->addWidget(strongestPlayersWhite, 9, 1, 1, 2);
        pageLayout->addWidget(new QLabel("Strongest players as black:"), 10, 0, 1, 1);
        pageLayout->addWidget(strongestPlayersBlack, 10, 1, 1, 2);
        

        mainLayout = new QVBoxLayout();
        mainLayout->addWidget(formHeader);
        mainLayout->addLayout(pageLayout);

        connectFormHeader();

        setLayout(mainLayout);

        loadPage();

        searchCompleter = new QCompleter(tournametns, this);
        search->setCompleter(searchCompleter);

        connect(search, &QLineEdit::returnPressed, this, [this] {
            QSqlQuery query("SELECT tournament_id"
                " FROM tournaments"
                " WHERE name = \'" + search->text() + "\'");
            
            if (query.next()) {
                curInd = query.value(0).toInt();
                loadPage();
            } else {
                qDebug() << query.lastError().text();
                qDebug() << "ERROR";
                search->clear();
            }
        });
}

TournamentsStatsWidget::~TournamentsStatsWidget() {
    
}

inline void TournamentsStatsWidget::loadPage() {
    loadTournaments();
    loadBasics();
    loadGameAmount();
    loadChart();
    loadTables();
}

void TournamentsStatsWidget::loadBasics() {
    QString str = "SELECT tournaments.name, tournaments.rating_restriction, winner.name, judge.name, place.city, place.country"
                    " FROM tournaments"
                    " INNER JOIN chessplayers AS winner ON tournaments.winner_id = winner.chessplayer_id"
                    " INNER JOIN judges AS judge ON tournaments.judge_id = judge.judge_id"
                    " INNER JOIN places AS place ON place.place_id = tournaments.place_id"
                    " WHERE tournaments.tournament_id = " + QString::number(curInd);
    QSqlQuery query(str);
    while(query.next()) {
        tournamentName->setText(query.value(0).toString().simplified());
        ratingRestriction->setValue(query.value(1).toInt());
        winnersName->setText(query.value(2).toString().simplified());
        judgesName->setText(query.value(3).toString().simplified());
        city->setText(query.value(4).toString().simplified());
        country->setText(query.value(5).toString().simplified());
    }
}
void TournamentsStatsWidget::loadGameAmount() {
    QString str = "SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(curInd);

    QSqlQuery query(str);
    while(query.next()) {
        gamesAmount->setValue(query.value(0).toInt());
    }
}
void TournamentsStatsWidget::loadChart() {
    QString begin = "SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(curInd);
    begin += " AND result = \'";

    quint32 whiteWins = 0, blackWins = 0, draws = 0;

    QSqlQuery query(begin + "1-0\'");
    while(query.next()) {
        whiteWins = query.value(0).toInt();
    }
    query = QSqlQuery(begin + "0-1\'");
    while(query.next()) {
        blackWins = query.value(0).toInt();
    }
    query = QSqlQuery(begin  + "1-1\'");
    while (query.next()) {
        draws = query.value(0).toInt();
    }

    QPieSeries *series = new QPieSeries;
    series->append("White wins", whiteWins);
    series->append("Black wins", blackWins);
    series->append("Draws", draws);

    QChart *chart = new QChart;
    chart->addSeries(series);

    results->setChart(chart);
    results->show();
}
void TournamentsStatsWidget::loadTables() {
    QString str = "SELECT chessplayers.name AS Имя, chessplayers.elo_rating AS Рейтинг, COUNT(*) AS cnt FROM chess_games"
            " INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id"
            " WHERE tournament_id = " + QString::number(curInd) + " AND result='1-0'"
            " GROUP BY chessplayers.name, chessplayers.elo_rating"
            " ORDER BY cnt DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(str);
    model->setHeaderData(2, Qt::Horizontal, tr("Количество побед"));
    strongestPlayersWhite->setModel(model);
    strongestPlayersWhite->show();

    str = "SELECT chessplayers.name AS Имя, chessplayers.elo_rating AS Рейтинг, COUNT(*) AS cnt FROM chess_games"
                " INNER JOIN chessplayers ON black_id = chessplayers.chessplayer_id"
                " WHERE tournament_id = " + QString::number(curInd) + " AND result='0-1'"
                " GROUP BY chessplayers.name, chessplayers.elo_rating"
                " ORDER BY cnt DESC";
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setQuery(str);
    model1->setHeaderData(2, Qt::Horizontal, tr("Количество побед"));
    strongestPlayersBlack->setModel(model1);
    strongestPlayersBlack->show();
}

void TournamentsStatsWidget::loadTournaments() {
    QSqlQuery query("SELECT name FROM tournaments");
    while (query.next()) {
        tournametns.push_back(query.value(0).toString().simplified());
    }
}