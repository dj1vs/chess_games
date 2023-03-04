#include "tournamentswidget.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>

TournamentsWidget::TournamentsWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Tournaments");

    pageLayout = new QGridLayout;
    id = new QSpinBox;
    name = new QLineEdit;
    ratingRestriction = new QSpinBox;
    winner = new QLineEdit;
    city = new QLineEdit;
    country = new QLineEdit;
    judge = new QLineEdit;
    playedGames = new QTableView;

    pageLayout->addWidget(new QLabel("ID"), 0, 0, 1, 1);
    pageLayout->addWidget(id, 0, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Tournaments name"), 1, 0, 1, 1);
    pageLayout->addWidget(name, 1, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Rating restriction"), 2, 0, 1, 1);
    pageLayout->addWidget(ratingRestriction, 2, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Winner"), 3, 0, 1, 1);
    pageLayout->addWidget(winner, 3, 1, 1, 1);
    pageLayout->addWidget(new QLabel("City"), 4, 0, 1, 1);
    pageLayout->addWidget(city, 4, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Country"), 4, 2, 1, 1);
    pageLayout->addWidget(country, 4, 3, 1, 1);
    pageLayout->addWidget(new QLabel("Judge"), 5, 0, 1, 1);
    pageLayout->addWidget(judge, 6, 0, 1, 1);
    pageLayout->addWidget(new QLabel("Games, played at a tournament:"), 7, 0, 1, 1);
    pageLayout->addWidget(playedGames, 7, 1, 1, 3);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);
    loadPage();

    connectFormHeader();
}

TournamentsWidget::~TournamentsWidget() {
    
}

void TournamentsWidget::loadPage() {
    loadBasics();
    loadTable();
}

void TournamentsWidget::loadBasics() {
    id->setValue(curInd);
    QSqlQuery query("SELECT tournaments.name, rating_restriction, winner.name, city, country, judges.name"
    " FROM tournaments"
    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
    " INNER JOIN places ON tournaments.place_id = places.place_id"
    " INNER JOIN judges ON judges.judge_id = tournaments.judge_id"
    " WHERE tournament_id = " + QString::number(curInd));

    while (query.next()) {
        name->setText(query.value(0).toString().simplified());
        ratingRestriction->setValue(query.value(1).toInt());
        winner->setText(query.value(2).toString().simplified());
        city->setText(query.value(3).toString().simplified());
        country->setText(query.value(4).toString().simplified());
        judge->setText(query.value(5).toString().simplified());
    }
}

void TournamentsWidget::loadTable() {
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT game_date, format, time_control, result, white.name, black.name, moves"
        " FROM chess_games"
        " INNER JOIN chessplayers AS white ON white.chessplayer_id = white_id"
        " INNER JOIN chessplayers AS black ON black.chessplayer_id = black_id"
        " WHERE tournament_id = " + QString::number(curInd));

    playedGames->setModel(model);
    playedGames->show();

}
