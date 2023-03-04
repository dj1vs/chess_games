#include "gameswidget.h"

#include <QSqlQuery>

GamesWidget::GamesWidget(QWidget *parent):
    QWidget{parent} {
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
    tournamet = new QLineEdit;

    layout = new QFormLayout;
    layout->addWidget(formHeader);
    layout->addRow("ID", id);
    layout->addRow("Format", format);
    layout->addRow("Moves", moves);
    layout->addRow("Result", result);
    layout->addRow("Time control", timeControl);
    layout->addRow("Date", date);
    layout->addRow("White", white);
    layout->addRow("Black", black);
    layout->addRow("Opening", opening);
    layout->addRow("Tournament", tournamet);

    setLayout(layout);

    connect(formHeader, &FormHeader::exit, this, [this] {emit exit();});
    connect(formHeader, &FormHeader::prev, this, [this] {
        if (curInd - 1) {
            --curInd;
            loadPage();
        }
    });
    connect(formHeader, &FormHeader::next, this, [this] {
        ++curInd;
        loadPage();
    });

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
        tournamet->setText(query.value(8).toString().simplified());
    }
}