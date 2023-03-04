#include "gameswidget.h"

#include <QSqlQuery>

GamesWidget::GamesWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chess games");

    id = new QSpinBox;
    format = new QLineEdit;
    moves = new QTextBrowser;
    result = new QLineEdit;
    timeControl = new QLineEdit;
    date = new QLineEdit;
    white = new QLineEdit;
    black = new QLineEdit;
    opening = new QLineEdit;
    tournament = new QLineEdit;

    layout = new QGridLayout;
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Format"));
    layout->addWidget(format);
    layout->addWidget(new QLabel("Moves"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Result"));
    layout->addWidget(result);
    layout->addWidget(new QLabel("TimeControl"));
    layout->addWidget(timeControl);
    layout->addWidget(new QLabel("Date"));
    layout->addWidget(date);
    layout->addWidget(new QLabel("White"));
    layout->addWidget(white);
    layout->addWidget(new QLabel("Tournament"));
    layout->addWidget(new QLabel("Black"));
    layout->addWidget(black);
    layout->addWidget(new QLabel("Opening"));
    layout->addWidget(opening);
    layout->addWidget(tournament);

    for (int i = 0; i < layout->rowCount(); ++i) {
        layout->setRowStretch(i, 1);
    }

    for (int i = 0; i < layout->columnCount(); ++i) {
        layout->setColumnStretch(i, 1);
    }

    setLayout(layout);

    connectFormHeader();

    loadPage();

}

GamesWidget::~GamesWidget() {
    
}

void GamesWidget::loadPage() {
    id->setValue(curInd);
    QSqlQuery query("SELECT format, chess_games.moves, result, time_control, game_date, white.name, black.name, openings.name, tournaments.name"
    " FROM chess_games"
    " INNER JOIN chessplayers AS white ON white.chessplayer_id = white_id"
    " INNER JOIN chessplayers AS black ON black.chessplayer_id = black_id"
    " INNER JOIN openings ON openings.eco_id = opening_id"
    " INNER JOIN tournaments ON tournaments.tournament_id = chess_games.tournament_id"
    " WHERE chess_games.game_id = " + QString::number(curInd));

    while(query.next()) {
        format->setText(query.value(0).toString().simplified());
        moves->setText(query.value(1).toString().simplified());
        result->setText(query.value(2).toString().simplified());
        timeControl->setText(query.value(3).toString().simplified());
        date->setText(query.value(4).toString().simplified());
        white->setText(query.value(5).toString().simplified());
        black->setText(query.value(6).toString().simplified());
        opening->setText(query.value(7).toString().simplified());
        tournament->setText(query.value(8).toString().simplified());
    }
}
