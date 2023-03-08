#include "gameswidget.h"

#include <QSqlQuery>
#include <QDate>

GamesWidget::GamesWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chess games");

    id = new QSpinBox;
    format = new QLineEdit;
    moves = new QTextEdit;
    result = new QLineEdit;
    timeControl = new QLineEdit;
    date = new QLineEdit;
    white = new QLineEdit;
    black = new QLineEdit;
    opening = new QLineEdit;
    tournament = new QLineEdit;
    save = new QPushButton("Save");

    layout = new QVBoxLayout(this);
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
    layout->addWidget(tournament);
    layout->addWidget(new QLabel("Black"));
    layout->addWidget(black);
    layout->addWidget(new QLabel("Opening"));
    layout->addWidget(opening);
    layout->addWidget(save);

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();
    loadLists();


    chessplayersCompleter = new QCompleter(chessplayers, this);
    openingsCompleter = new QCompleter(openings, this);
    tournamentsCompleter = new QCompleter(tournaments, this);

    white->setCompleter(chessplayersCompleter);
    black->setCompleter(chessplayersCompleter);
    opening->setCompleter(openingsCompleter);
    tournament->setCompleter(tournamentsCompleter);



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

void GamesWidget::loadChessplayers() {
    QSqlQuery query("SELECT name FROM chessplayers");
    while (query.next()) {
        chessplayers.push_back(query.value(0).toString().simplified());
    }
}
void GamesWidget::loadOpenings() {
    QSqlQuery query("SELECT name FROM openings");
    while (query.next()) {
        openings.push_back(query.value(0).toString().simplified());
    }
}
void GamesWidget::loadTournaments() {
    QSqlQuery query("SELECT name FROM tournaments");
    while (query.next()) {
        tournaments.push_back(query.value(0).toString().simplified());
    }
}

inline void GamesWidget::loadLists() {
    loadChessplayers();
    loadOpenings();
    loadTournaments();
}

void GamesWidget::saveChanges() {
    bool exists = QSqlQuery("SELECT * FROM chess_games WHERE game_id = " + QString::number(curInd)).next();
    if (exists) {
        QSqlQuery query;
        query.prepare("UPDATE chess_games SET"
                      " format = :format,"
                      " moves = :moves,"
                      " result = :result,"
                      " time_control = :time_control,"
                      " game_date = :date,"
                      " white_id = :white_id,"
                      " tournament_id = :tournament_id,"
                      " black_id = :black_id,"
                      " opening_id = :opening_id"
                      " WHERE game_id = :game_id");

        quint32 whiteID = getChessplayerID(white->text()), blackID = getChessplayerID(black->text());
        quint32 tournamentID = getTournamentID();
        QString openingID = getOpeningID();

        query.bindValue(":format", format->text());
        query.bindValue(":moves", moves->toPlainText());
        query.bindValue(":result", result->text());
        query.bindValue(":time_control", timeControl->text());
        query.bindValue(":date", QDate::fromString(date->text()));
        query.bindValue(":white_id", whiteID);
        query.bindValue(":tournament_id", tournamentID);
        query.bindValue(":black_id", blackID);
        query.bindValue(":opening_id", openingID);
        query.bindValue(":game_id", curInd);

        query.exec();
    } else {
        QSqlQuery query;

        query.prepare("INSERT INTO chess_games VALUES("
                      " :game_id,"
                      " :format,"
                      " :moves,"
                      " :result,"
                      " :time_control,"
                      " :date,"
                      " :white_id,"
                      " :black_id,"
                      " :opening_id,"
                      " :game_id)");

        query.bindValue(":format", format->text());
        query.bindValue(":moves", moves->toPlainText());
        query.bindValue(":result", result->text());
        query.bindValue(":time_control", timeControl->text());
        query.bindValue(":date", date->text());
        query.bindValue(":white_id", getChessplayerID(white->text()));
        query.bindValue(":tournament_id", getTournamentID());
        query.bindValue(":black_id", getChessplayerID(black->text()));
        query.bindValue(":opening_id", getOpeningID());
        query.bindValue(":game_id", curInd);

        query.exec();
    }

}

quint32 GamesWidget::getChessplayerID(QString name) {
    QSqlQuery query("SELECT chessplayer_id FROM chessplayers WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
QString GamesWidget::getOpeningID() {
    QSqlQuery query("SELECT eco_id FROM openings WHERE name = \'" + opening->text() + "\'");
    if (query.next()) {
        return query.value(0).toString().simplified();
    } else {
        return "";
    }
}
quint32 GamesWidget::getTournamentID() {
    QSqlQuery query("SELECT tournament_id FROM tournaments WHERE name = \'" + tournament->text() + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
