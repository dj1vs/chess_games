#include "sqlworker.h"

#include <QDebug>
#include <QSqlError>
#include <QDate>

SQLWorker::SQLWorker(QObject *parent) : QObject(parent) {
}

SQLWorker::~SQLWorker() {
    db.close();
}

void SQLWorker::authSuccess(const QString login, const QString pass) {
    QSqlQuery query("SELECT pass FROM users WHERE login = \'" + login + "\';");
    int count = 0;
    bool isAuthorized = false;
    while(query.next()) {
        if (query.value(0).qstring == pass) {
            ++count;
            isAuthorized = true;
        }
    }

    emit authResultReady(isAuthorized && count == 1);
}

void SQLWorker::getPlace(quint32 ind)
{
    QSqlQuery query = QSqlQuery("SELECT city, country FROM places WHERE place_id = " + QString::number(ind));
    DMap map;
    if (query.next())
    {
        map["city"] = query.value(0);
        map["country"] = query.value(1);
    }
    
    emit placeReady(map);
}
void SQLWorker::getChessplayer(const quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT name, elo_rating, birth_year FROM chessplayers \
    WHERE chessplayer_id = " + QString::number(ind));

    DMap map;

    if (query.next()) {
        map["name"] = query.value(0);
        map["elo_rating"] = query.value(1);
        map["birth_year"] = query.value(2);
    }

    emit chessplayerReady(map);
}
void SQLWorker::getGame(quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT game_date, white.name, white.elo_rating, black.name, black.elo_rating, format,"
    " time_control, opening.name, chess_games.moves, chess_games.result, tournaments.name"
    " FROM chess_games"
    " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
    " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id"
    " INNER JOIN openings AS opening ON opening_id = opening.eco_id"
    " INNER JOIN tournaments ON tournaments.tournament_id = chess_games.tournament_id"
    " WHERE game_id = " + QString::number(ind));

    DMap map;
    while(query.next()) {
        map["date"] = query.value(0);
        map["white_name"] = query.value(1);
        map["white_rating"] = query.value(2);
        map["black_name"] = query.value(3);
        map["black_rating"] = query.value(4);
        map["format"] = query.value(5);
        map["time_control"] = query.value(6);
        map["opening"] = query.value(7);
        map["moves"] = query.value(8);
        map["result"] = query.value(9);
        map["tournament"] = query.value(10);
    }

    emit gameReady(map);
}
void SQLWorker::getJudge(quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT name, email FROM judges WHERE judge_id = " + QString::number(ind));
    DMap map;
    if (query.next()) {
        map["name"] = query.value(0);
        map["mail"] = query.value(1);
    }

    emit judgeReady(map);
}
void SQLWorker::getOpening(QString ind) {
    QSqlQuery query = QSqlQuery("SELECT openings_group, name, moves, alternative_names, named_after FROM openings"
                    " WHERE eco_id = \'" + ind + "\' ORDER BY eco_id");

    DMap map;
    if (query.next()) {
        map["group"] = query.value(0);
        map["name"] = query.value(1);
        map["moves"] = query.value(2);
        map["alt_names"] = query.value(3);
        map["named_after"] = query.value(4);
    }

    emit openingReady(map);
}
void SQLWorker::getTournament(quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT tournaments.name, rating_restriction, winner.name, places.city, places.country, judges.name"
    " FROM tournaments"
    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
    " INNER JOIN places ON tournaments.place_id = places.place_id"
    " INNER JOIN judges ON judges.judge_id = tournaments.judge_id"
    " WHERE tournament_id = " + QString::number(ind));

    DMap map;
    if (query.next()) {
        map["name"] = query.value(0);
        map["rating_restriction"] = query.value(1);
        map["winner"] = query.value(2);
        map["city"] = query.value(3);
        map["country"] = query.value(4);
        map["judge"] = query.value(5);
    }
    

    emit tournamentReady(map);
}

void SQLWorker::getJudgesTournaments(quint32 ind) {
    DTable table;
    QSqlQuery query = QSqlQuery("SELECT tournaments.name, winner.name, city, country"
                      " FROM tournaments"
                      " INNER JOIN chessplayers AS winner ON winner.chessplayer_id = winner_id"
                      " INNER JOIN places ON places.place_id = tournaments.place_id"
                      " WHERE judge_id = " + QString::number(ind));
    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring, query.value(2).qstring, query.value(3).qstring});
    }

    emit judgesTournamentsReady(table);
}
void SQLWorker::getPlacesTournaments(quint32 ind) {
    DTable table;
    QSqlQuery query = QSqlQuery("SELECT tournament_id, tournaments.name, winner.name"
                    " FROM tournaments"
                    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
                    " WHERE place_id = " + QString::number(ind) +\
                    " ORDER BY tournament_id");
    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring, query.value(2).qstring});
    }

    emit placesTournamentsReady(table);
}
void SQLWorker::getTournamentGames(quint32 ind) {
    DTable table;
    QSqlQuery query = QSqlQuery("SELECT game_date, format, time_control, result, white.name, black.name, moves"
        " FROM chess_games"
        " INNER JOIN chessplayers AS white ON white.chessplayer_id = white_id"
        " INNER JOIN chessplayers AS black ON black.chessplayer_id = black_id"
        " WHERE tournament_id = " + QString::number(ind));
    while(query.next()) {
        QStringList line;
        for (int i = 0; i < 7; ++i) {
            line.push_back(query.value(i).qstring);
        }
        table.push_back(line);
    }
    

    emit tournamentGamesReady(table);
}
void SQLWorker::getChessplayerGames(quint32 ind, QString color) {
    QSqlQuery query = QSqlQuery("SELECT game_date, white.name, black.name, time_control, format, result, moves"
                  " FROM chess_games"
                  " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
                  " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id"
                  " WHERE " + color + "_id = " + QString::number(ind));
    DTable table;
    while(query.next()) {
        QStringList line;
        for (int i = 0; i < 7; ++i) {
            line.push_back(query.value(i).qstring);
        }
        table.push_back(line);
    }

    emit chessplayerGamesReady(table, color);
}
void SQLWorker::getChessplayerOpenings(quint32 ind, QString color) {
    QSqlQuery query = QSqlQuery("SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id"
                  " WHERE " + color + "_id = " + QString::number(ind) +\
                  " GROUP BY openings.name ORDER BY amount DESC");

    DTable table;
    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring});
    }

    emit chessplayerOpeningsReady(table, color);
}
void SQLWorker::getChessplayerStrongestOpponents(quint32 ind) {
    QSqlQuery query = QSqlQuery(" SELECT chessplayers.name, chessplayers.elo_rating"
                  " FROM chess_games"
                  " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id"
                  " WHERE black_id = " + QString::number(ind) +\
                  " UNION DISTINCT"
                  " SELECT chessplayers.name, chessplayers.elo_rating"
                  " FROM chess_games"
                  " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id"
                  " WHERE white_id = " + QString::number(ind) +\
                  " ORDER BY elo_rating DESC");
    DTable table;
    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring});
    }

    emit chessplayerStrongestOpponentsReady(table);
}
void SQLWorker::getOpeningPlayers(QString ind, QString color) {
    DTable table;

    QSqlQuery query = QSqlQuery("SELECT name, elo_rating, COUNT(*) as cnt"
        " FROM chess_games"
        " INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id"
        " WHERE opening_id = \'" + ind + "\'" +\
        " GROUP BY chessplayers.name, elo_rating"
        " ORDER BY cnt DESC");

    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring, query.value(2).qstring});
    }

    emit openingPlayersReady(table, color);
}
void SQLWorker::getBestTournamentPlayers(quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");

    QSqlQuery query = QSqlQuery("SELECT chessplayers.name, chessplayers.elo_rating, COUNT(*) AS cnt"
            " FROM chess_games"
            " INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id"
            " WHERE tournament_id = " + QString::number(ind) + " AND result=\'" + win + "\'"
            " GROUP BY chessplayers.name, chessplayers.elo_rating"
            " ORDER BY cnt DESC");

    DTable table;
    while (query.next()) {
        table.push_back({query.value(0).qstring, query.value(1).qstring, query.value(2).qstring});
    }

    emit bestTournamentPlayersReady(table, color);
}


void SQLWorker::getGamesCrossRequest() {

    DTable table;

    QStringList names = allChessplayersNames();

    QString queryString;

    for (int i = 0; i < names.size(); ++i) {
        QStringList line;
        for (int i = 0; i < names.size() + 2; ++i) {
            line.push_back("");
        }

        int ind = 0;
        line[ind++] = names[i];

        QString str = QString::number(i);
        queryString = "SELECT chessplayers.name, me.elo_rating-chessplayers.elo_rating"
        " FROM chess_games"
        " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id"
        " INNER JOIN chessplayers AS me ON black_id = me.chessplayer_id "
        " WHERE black_id = " + str;
        queryString += " UNION DISTINCT"
        " SELECT chessplayers.name, me.elo_rating-chessplayers.elo_rating"
        " FROM chess_games"
        " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id"
        " INNER JOIN chessplayers AS me ON white_id = me.chessplayer_id "
        " WHERE white_id = " + str;

        ++++ind;
        QSqlQuery query = QSqlQuery(queryString);
        int sum = 0;
        while(query.next()) {
            ind = names.indexOf(query.value(0).qstring);
            line[ind + 2] = query.value(1).qstring;
            sum += query.value(1).toInt();
        }
        line[1] = QString::number(sum);

        table.push_back(line);
    }

    emit gamesCrossRequestReady(table);
}

void SQLWorker::getAllChessplayersNames() {
    QStringList names = allChessplayersNames();
    emit allChessplayersNamesReady(names);
}


QStringList SQLWorker::allChessplayersNames() {
    QSqlQuery query = QSqlQuery("SELECT name FROM chessplayers");
    QStringList names;
    while (query.next()) {
        names.push_back(query.value(0).qstring);
    }

    return names;
}
void SQLWorker::getAllOpeningsNames() {
    QStringList names;
    QSqlQuery query = QSqlQuery("SELECT name FROM openings");
    while (query.next()) {
        names.push_back(query.value(0).qstring);
    }

    emit allOpeningsNamesReady(names);
}
void SQLWorker::getAllTournamentsNames() {
    QStringList names;
    QSqlQuery query = QSqlQuery("SELECT name FROM tournaments");
    while (query.next()) {
        names.push_back(query.value(0).qstring);
    }

    emit allTournamentsNamesReady(names);
}
void SQLWorker::getAllOpeningsIds() {
    QSqlQuery query = QSqlQuery("SELECT eco_id FROM openings");
    QStringList ids;
    while (query.next()) {
        ids.push_back(query.value(0).qstring);
    }

    emit allOpeningsIdsReady(ids);
}

void SQLWorker::getChessplayerID(QString name){
    emit chessplayerIDReady(chessplayerID(name));
}
void SQLWorker::getOpeningID(QString name) {
    emit openingIDReady(openingID(name));
}
void SQLWorker::getTournamentID(QString name) {
    emit tournamentIDReady(tournamentID(name));
}
void SQLWorker::getJudgeID(QString name) {
    emit judgeIDReady(judgeID(name));
}
void SQLWorker::getPlaceID(QString city, QString country) {
    emit placeIDReady(placeID(city, country));
}

quint32 SQLWorker::chessplayerID(const QString name) {
    QSqlQuery query = QSqlQuery("SELECT chessplayer_id FROM chessplayers WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
QString SQLWorker::openingID(const QString name) {
    QSqlQuery query = QSqlQuery("SELECT eco_id FROM openings WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).qstring;
    } else {
        return "";
    }
}
quint32 SQLWorker::tournamentID(const QString name) {
    QSqlQuery query = QSqlQuery("SELECT tournament_id FROM tournaments WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
quint32 SQLWorker::judgeID(const QString name) {
    QSqlQuery query = QSqlQuery("SELECT judge_id FROM judges WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
quint32 SQLWorker::placeID(const QString city, const QString country) {
    QSqlQuery query = QSqlQuery("SELECT place_id FROM places WHERE city = \'" + city + "\'"
            "AND country = \'" + country + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}

void SQLWorker::getMaxTournamentID() {
    QSqlQuery query = QSqlQuery("SELECT MAX(tournament_id) FROM tournaments");
    if (query.next()) {
        emit maxTournamentIDReady(query.value(0).toInt());
        return;
    }

    emit maxTournamentIDReady(-1);
}
void SQLWorker::getMaxGameID() {
    QSqlQuery query = QSqlQuery("SELECT MAX(game_id) FROM chess_games");
    if (query.next()) {
        emit maxGameIDReady(query.value(0).toInt());
        return;
    }

    emit maxGameIDReady(-1);
}
void SQLWorker::getMaxPlaceID() {
    QSqlQuery query = QSqlQuery("SELECT MAX(place_id) FROM places");
    if (query.next()) {
        emit maxPlaceIDReady(query.value(0).toInt());
        return;
    }

    emit maxPlaceIDReady(-1);
}
void SQLWorker::getMaxChessplayerID() {
    QSqlQuery query = QSqlQuery("SELECT MAX(chessplayer_id) FROM chessplayers");
    if (query.next()) {
        emit maxChessplayerIDReady(query.value(0).toInt());
        return;
    }

    emit maxChessplayerIDReady(-1);
}
void SQLWorker::getMaxJudgeID() {
    QSqlQuery query = QSqlQuery("SELECT MAX(judge_id) FROM judges");
    if (query.next()) {
        emit maxJudgeIDReady(query.value(0).toInt());
        return;
    }

    emit maxJudgeIDReady(-1);
}
void SQLWorker::getGamesAmount() {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) FROM chess_games");
    if (query.next()) {
        emit gamesAmountReady(query.value(0).toInt());
        return;
    }

    emit gamesAmountReady(-1);
}


void SQLWorker::getChessplayerGamesAmount(quint32 ind, QString color) {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) from chess_games WHERE " + color + "_id = "\
        + QString::number(ind));

    if(query.next()) {
        emit chessplayerGamesAmountReady(query.value(0).toInt(),color);
        return;
    }

    emit chessplayerGamesAmountReady(-1,color);
}
void SQLWorker::getChessplayerWins(quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");
    QSqlQuery query = QSqlQuery("SELECT COUNT(*)"
        " FROM chess_games"
        " WHERE (result = '" + win + "') AND (" + color + "_id = " + QString::number(ind) + ")");
    
    if (query.next()) {
        emit chessplayerWinsReady(query.value(0).toInt(),color);
        return;
    }

    emit chessplayerWinsReady(-1,color);
}
void SQLWorker::getChessplayerLoses(quint32 ind, QString color) {
    QString lose = (color == "white" ? "0-1" : "1-0");
    QSqlQuery query = QSqlQuery("SELECT COUNT(*)"
        " FROM chess_games"
        " WHERE (result = '" + lose + "') AND (" + color + "_id = " + QString::number(ind) + ")");
    if(query.next()) {
        emit chessplayerLosesReady(query.value(0).toInt(),color);
        return;
    }

    emit chessplayerLosesReady(-1,color);
}
void SQLWorker::getGamesWithOpeningAmount(QString ind) {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'");
    if (query.next()) {
        emit gamesWithOpeningAmountReady(query.value(0).toInt());
        return;
    }

    emit gamesWithOpeningAmountReady(-1);
}
void SQLWorker::getWhiteWinsWithOpeningAmount(QString ind) {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'"
        " AND result = \'1-0\'");
    if (query.next()) {
        emit whiteWinsWithOpeningAmountReady(query.value(0).toInt());
        return;
    }

    emit whiteWinsWithOpeningAmountReady(-1);
}
void SQLWorker::getBlackWinsWithOpeningAmount(QString ind) {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'"
        " AND result = \'0-1\'");
    if (query.next()) {
        emit blackWinsWithOpeningAmountReady(query.value(0).toInt());
        return;
    }

    emit blackWinsWithOpeningAmountReady(-1);
}
void SQLWorker::getTournamentGamesAmount(const quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(ind));
    if(query.next()) {
        emit tournamentGamesAmountReady(query.value(0).toInt());
        return;
    }

    emit tournamentGamesAmountReady(-1);
}
void SQLWorker::getTournamentWinsAmount(const quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");
    QSqlQuery query = QSqlQuery("SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(ind) +\
            " AND result = \'" + win + "\'");
    
    if (query.next()) {
        emit tournamentWinsAmountReady(query.value(0).toInt(), color);
        return;
    }
    emit tournamentWinsAmountReady(-1, color);
    
}

void SQLWorker::getChessplayerOpeningCounts(quint32 ind, QString color) {
    QSqlQuery query = QSqlQuery("SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id"
                  " WHERE " + color + "_id = " + QString::number(ind) +\
                  " GROUP BY openings.name ORDER BY amount DESC");

    DMap result;
    while (query.next()) {
        result[query.value(0).qstring] = query.value(1);
    }

    emit chessplayerOpeningCountsReady(result, color);
}

void SQLWorker::setChessplayer(DMap player) {
    QSqlQuery query;
    if (chessplayerExists(player["chessplayer_id"].toInt())) {
        query.prepare("UPDATE chessplayers SET"
                      " name = :name,"
                      " elo_rating = :elo_rating,"
                      " birth_year = :birth_year"
                      " WHERE chessplayer_id = :chessplayer_id");
    } else {
        query.prepare("INSERT INTO chessplayers"
                      "VALUES ("
                      ":chessplayer_id,"
                      ":name,"
                      ":elo_rating,"
                      ":birth_year)");
    }

    query.bindValue(":name", player["name"].toString());
    query.bindValue(":elo_rating", player["elo_rating"].toInt());
    query.bindValue(":birth_year", player["birth_year"].toInt());
    query.bindValue(":chessplayer_id", player["chessplayer_id"].toInt());

    query.exec();

    emit chessplayerSet();
}
void SQLWorker::setGame(DMap game) {
    QSqlQuery query;
    if (gameExists(game["id"].toInt())) {
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
    } else {
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
    }

    query.bindValue(":format", game["format"]);
    query.bindValue(":moves", game["moves"]);
    query.bindValue(":result", game["result"]);
    query.bindValue(":time_control", game["time_control"]);
    query.bindValue(":date",game["date"].toString());
    query.bindValue(":white_id", chessplayerID(game["white"].toString()));
    query.bindValue(":tournament_id", tournamentID(game["tournament"].toString()));
    query.bindValue(":black_id", chessplayerID(game["black"].toString()));
    query.bindValue(":opening_id", openingID(game["opening"].toString()));
    query.bindValue(":game_id", game["id"]);

    query.exec();

    emit gameSet();
}
void SQLWorker::setJudge(const DMap judge) {
    QSqlQuery query;
    if (judgeExists(judge["id"].toInt())) {
        query.prepare("UPDATE judges SET"
                      " name = :name,"
                      " email = :email"
                      " WHERE judge_id = :judge_id");
    } else {
        query.prepare("INSERT INTO judges VALUES("
                      " :judge_id,"
                      " :name,"
                      " :email");
    }
    query.bindValue(":name", judge["name"]);
    query.bindValue(":email", judge["email"]);
    query.bindValue(":judge_id", judge["id"]);

    query.exec();

    emit judgeSet();
}
void SQLWorker::setOpening(const DMap opening) {
    QSqlQuery query;
    if (openingExists(opening["id"].toString())) {
        query.prepare("UPDATE openings SET"
                      " openings_group = :openings_group,"
                      " name = :name,"
                      " moves = :moves,"
                      " alternative_names = :alternative_names,"
                      " named_after = :named_after"
                      " WHERE eco_id = :eco_id");
    } else {
        query.prepare("INSERT INTO openings VALUES("
                      ":eco_id,"
                      ":openings_group,"
                      ":name,"
                      ":moves,"
                      ":alternative_names,"
                      " :named_after)");
    }

    query.bindValue(":openings_group", opening["group"]);
    query.bindValue(":name", opening["name"]);
    query.bindValue(":moves", opening["moves"]);
    query.bindValue(":alternative_names", opening["alt_names"]);
    query.bindValue(":named_after", opening["named_after"]);
    query.bindValue(":eco_id", opening["id"]);
    
    query.exec();

    emit openingSet();
}
void SQLWorker::setPlace(const DMap place) {
    QSqlQuery query;
    if (placeExists(place["id"].toInt())) {
        query.prepare("UPDATE places SET"
                      " city = :city,"
                      " country = :country"
                      " WHERE place_id = :place_id");
    } else {
        query.prepare("INSERT INTO places VALUES("
                      " :place_id,"
                      " :city,"
                      " :country)");
    }

    query.bindValue(":city", place["city"]);
    query.bindValue(":country", place["country"]);
    query.bindValue(":place_id", place["id"]);

    query.exec();

    emit placeSet();
}
void SQLWorker::setTournament(DMap tournament) {
    QSqlQuery query;
    if (tournamentExists(tournament["id"].toInt())) {
        QSqlQuery query;
        query.prepare("UPDATE tournaments SET"
                      " name = :name,"
                      " rating_restriction = :rating_restriction,"
                      " place_id = :place_id,"
                      " winner_id = :winner_id,"
                      " judge_id = :judge_id"
                      " WHERE tournament_id = :tournament_id");
    } else {
        QSqlQuery query;

        query.prepare("INSERT INTO tournaments VALUES("
                      ":tournament_id,"
                      " :name,"
                      " :rating_restriction,"
                      " :winner_id,"
                      " :place_id,"
                      " :judge_id)");
    }

    query.bindValue(":tournament_id", tournament["id"]);
    query.bindValue(":name", tournament["name"]);
    query.bindValue(":rating_restriction", tournament["rating_restriction"]);
    query.bindValue(":place_id", placeID(tournament["city"].toString(), tournament["country"].toString()));
    query.bindValue(":winner_id", chessplayerID(tournament["winner"].toString()));
    query.bindValue(":judge_id", judgeID(tournament["judge"].toString()));

    query.exec();

    emit tournamentSet();
}

bool SQLWorker::chessplayerExists (const quint32 ind) {
    QSqlQuery query = QSqlQuery("SELECT * FROM chessplayers WHERE chessplayer_id = " + QString::number(ind));
    return query.next();
}
bool SQLWorker::gameExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM chess_games WHERE game_id = " + QString::number(ind)).next();
}
bool SQLWorker::judgeExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM judges WHERE judge_id = " + QString::number(ind)).next();
}
bool SQLWorker::openingExists(const QString ind) {
    return QSqlQuery("SELECT * FROM openings WHERE eco_id = \'" + ind + "\'").next();
}
bool SQLWorker::placeExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM places WHERE place_id = " + QString::number(ind)).next();
}
bool SQLWorker::tournamentExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM tournaments WHERE tournament_id = " + QString::number(ind)).next();
}
void SQLWorker::connectToDB() {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("chess_games");
    db.setUserName("postgres");
    db.setPassword("123");

    if (db.open()) {
        qDebug() << "Database successfully opened";
    } else {
        qDebug() << "Can't connect to database";
    }
}
