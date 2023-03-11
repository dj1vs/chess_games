#include "sqlworker.h"

#include <QDebug>
#include <QSqlError>
#include <QDate>

SQLWorker::SQLWorker(QObject *parent) : QObject(parent) {
    connectToDB();
}

SQLWorker::~SQLWorker() {
    db.close();
}

void SQLWorker::authSuccess(const QString login, const QString pass) {
    QSqlQuery query("SELECT pass FROM users WHERE login = \'" + login + "\';");
    int count = 0;
    bool isAuthorized = false;
    while(query.next()) {
        if (query.value(0).toString() == pass) {
            ++count;
            isAuthorized = true;
        }
    }

    emit authResultReady(isAuthorized && count == 1);
}

void SQLWorker::getPlace(quint32 ind)
{
    query = QSqlQuery("SELECT city, country FROM places WHERE place_id = " + QString::number(ind));
    DMap map;
    if (query.next())
    {
        map["city"] = query.value(0);
        map["country"] = query.value(1);
    }
    
    emit placeReady(map);
}
void SQLWorker::getChessplayer(const quint32 ind) {
    query = QSqlQuery("SELECT name, elo_rating, birth_year FROM chessplayers \
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
    query = QSqlQuery("SELECT game_date, white.name, white.elo_rating, black.name, black.elo_rating, format,"
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
    query = QSqlQuery("SELECT name, email FROM judges WHERE judge_id = " + QString::number(ind));
    DMap map;
    if (query.next()) {
        map["name"] = query.value(0);
        map["mail"] = query.value(1);
    }

    emit judgeReady(map);
}
void SQLWorker::getOpening(QString ind) {
    query = QSqlQuery("SELECT openings_group, name, moves, alternative_names, named_after FROM openings"
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
    query = QSqlQuery("SELECT tournaments.name, rating_restriction, winner.name, places.city, places.country, judges.name"
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
    // QSqlQueryModel *model = new QSqlQueryModel;
    // model->setQuery("SELECT tournaments.name AS Турнир, winner.name AS Победитель,"
    //                   "city AS Город, country AS Страна"
    //                   " FROM tournaments"
    //                   " INNER JOIN chessplayers AS winner ON winner.chessplayer_id = winner_id"
    //                   " INNER JOIN places ON places.place_id = tournaments.place_id"
    //                   " WHERE judge_id = " + QString::number(ind));

    DTable table;
    emit judgesTournamentsReady(table);
}
QSqlQueryModel* SQLWorker::getPlacesTournaments(const quint32 ind) {
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT tournament_id AS ID, tournaments.name AS Турнир, winner.name AS Победитель"
                    " FROM tournaments"
                    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
                    " WHERE place_id = " + QString::number(ind));
    return model;
}
QSqlQueryModel* SQLWorker::getTournamentGames(const quint32 ind) {
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT game_date AS Дата, format AS Формат, time_control AS \"Контроль времени\", result AS Результат, white.name AS Белые, black.name AS Чёрные, moves as Ходы"
        " FROM chess_games"
        " INNER JOIN chessplayers AS white ON white.chessplayer_id = white_id"
        " INNER JOIN chessplayers AS black ON black.chessplayer_id = black_id"
        " WHERE tournament_id = " + QString::number(ind));

    return model;
}
QSqlQueryModel* SQLWorker::getChessplayerGames(const quint32 ind, const QString color) {
    QString queryString = "SELECT game_date AS Дата, white.name AS белые, black.name AS Чёрные, time_control AS \"Контроль времени\", format AS Формат, result AS Результат, moves AS Ходы"
                  " FROM chess_games"
                  " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
                  " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id";
    queryString += " WHERE " + color + "_id = " + QString::number(ind);
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery(queryString);

    return model;
}
QSqlQueryModel* SQLWorker::getChessplayerOpenings(const quint32 ind, const QString color) {
    QString queryString = "SELECT openings.name AS Дебют, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    queryString += " WHERE " + color + "_id = " + QString::number(ind);
    queryString += " GROUP BY openings.name ORDER BY amount DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);
    model->setHeaderData(1, Qt::Horizontal, tr("Количество игр"));

    return model;
}
QSqlQueryModel* SQLWorker::getChessplayerStrongestOpponents(const quint32 ind) {
    QString queryString = " SELECT chessplayers.name, chessplayers.elo_rating"
                  " FROM chess_games"
                  " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id";
    queryString += " WHERE black_id = " + QString::number(ind);
    queryString += " UNION DISTINCT"
                   " SELECT chessplayers.name, chessplayers.elo_rating"
                   " FROM chess_games"
                   " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id";
    queryString += " WHERE white_id = " + QString::number(ind);
    queryString += " ORDER BY elo_rating DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);
    model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(1, Qt::Horizontal, tr("Рейтинг"));

    return model;
}
QSqlQueryModel* SQLWorker::getOpeningPlayers(QString ind, QString color) {
    QSqlQueryModel *model = new QSqlQueryModel;
    QString str = "SELECT name AS Имя, elo_rating AS Рейтинг, COUNT(*) as cnt"
        " FROM chess_games"
        " INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id"
        " WHERE opening_id = \'" + ind + "\'" +\
        " GROUP BY chessplayers.name, elo_rating"
        " ORDER BY cnt DESC";
    model->setQuery(str);
    model->setHeaderData(2, Qt::Horizontal, tr("Количество игр"));

    return model;
}
QSqlQueryModel* SQLWorker::getBestTournamentPlayers(quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");
    QString str = "SELECT chessplayers.name AS Имя, chessplayers.elo_rating AS Рейтинг, COUNT(*) AS cnt FROM chess_games"
            " INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id"
            " WHERE tournament_id = " + QString::number(ind) + " AND result=\'" + win + "\'"
            " GROUP BY chessplayers.name, chessplayers.elo_rating"
            " ORDER BY cnt DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(str);
    model->setHeaderData(2, Qt::Horizontal, tr("Количество побед"));

    return model;
}


QStandardItemModel* SQLWorker::getGamesCrossRequest() {
    QStringList names = getAllChessplayersNames();

    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(names.size());
    model->setColumnCount(names.size() + 2);
    model->setHeaderData(1, Qt::Horizontal, tr("Сумма"));

    QString queryString;

    for (int i = 1; i <= names.size(); ++i) {
        model->setHeaderData(i+1, Qt::Horizontal, QString(names[i-1]));
        int ind = 0;
        model->setData(model->index(i-1, ind++), names[i-1]);
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
        query = QSqlQuery(queryString);
        int sum = 0;
        while(query.next()) {
            ind = names.indexOf(query.value(0).toString().simplified());
            model->setData(model->index(i-1, ind + 2), query.value(1));
            sum += query.value(1).toInt();
        }
        model->setData(model->index(i-1, 1), QVariant(sum));
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Шахматист"));

    return model;
}


QStringList SQLWorker::getAllChessplayersNames() {
    query = QSqlQuery("SELECT name FROM chessplayers");
    QStringList names;
    while (query.next()) {
        names.push_back(queryString(0));
    }

    return names;
}
QStringList SQLWorker::getAllOpeningsNames() {
    QStringList names;
    query = QSqlQuery("SELECT name FROM openings");
    while (query.next()) {
        names.push_back(queryString(0));
    }

    return names;
}
QStringList SQLWorker::getAllTournamentsNames() {
    QStringList names;
    query = QSqlQuery("SELECT name FROM tournaments");
    while (query.next()) {
        names.push_back(queryString(0));
    }

    return names;
}
void SQLWorker::getAllOpeningsIds() {
    query = QSqlQuery("SELECT eco_id FROM openings");
    QStringList ids;
    while (query.next()) {
        ids.push_back(queryString(0));
    }

    emit allOpeningsIdsReady(ids);
}

quint32 SQLWorker::getChessplayerID(const QString name) {
    query = QSqlQuery("SELECT chessplayer_id FROM chessplayers WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
QString SQLWorker::getOpeningID(const QString name) {
    query = QSqlQuery("SELECT eco_id FROM openings WHERE name = \'" + name + "\'");
    if (query.next()) {
        return queryString(0);
    } else {
        return "";
    }
}
quint32 SQLWorker::getTournamentID(const QString name) {
    query = QSqlQuery("SELECT tournament_id FROM tournaments WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
quint32 SQLWorker::getJudgeID(const QString name) {
    query = QSqlQuery("SELECT judge_id FROM judges WHERE name = \'" + name + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
quint32 SQLWorker::getPlaceID(const QString city, const QString country) {
    query = QSqlQuery("SELECT place_id FROM places WHERE city = \'" + city + "\'"
            "AND country = \'" + country + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}

quint32 SQLWorker::getMaxTournamentID() {
    query = QSqlQuery("SELECT MAX(tournament_id) FROM tournaments");
    if (query.next()) {
        return query.value(0).toInt();
    }
}
quint32 SQLWorker::getMaxGameID() {
    query = QSqlQuery("SELECT MAX(game_id) FROM chess_games");
    if (query.next()) {
        return query.value(0).toInt();
    }
}
quint32 SQLWorker::getMaxPlaceID() {
    query = QSqlQuery("SELECT MAX(place_id) FROM places");
    if (query.next()) {
        return query.value(0).toInt();
    }
}
quint32 SQLWorker::getMaxChessplayerID() {
    query = QSqlQuery("SELECT MAX(chessplayer_id) FROM chessplayers");
    if (query.next()) {
        return query.value(0).toInt();
    }
}
quint32 SQLWorker::getMaxJudgeID() {
    query = QSqlQuery("SELECT MAX(judge_id) FROM judges");
    if (query.next()) {
        return query.value(0).toInt();
    }
}
quint32 SQLWorker::getGamesAmount() {
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games");
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}


quint32 SQLWorker::getChessplayerGamesAmount(quint32 ind, QString color) {
    query = QSqlQuery("SELECT COUNT(*) from chess_games WHERE " + color + "_id = "\
        + QString::number(ind));

    if(query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getChessplayerWins(quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");
    query = QSqlQuery("SELECT COUNT(*)"
        " FROM chess_games"
        " WHERE (result = '" + win + "') AND (" + color + "_id = " + QString::number(ind) + ")");
    
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getChessplayerLoses(quint32 ind, QString color) {
    QString lose = (color == "white" ? "0-1" : "1-0");
    query = QSqlQuery("SELECT COUNT(*)"
        " FROM chess_games"
        " WHERE (result = '" + lose + "') AND (" + color + "_id = " + QString::number(ind) + ")");
    if(query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getGamesWithOpeningAmount(QString ind) {
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'");
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getWhiteWinsWithOpeningAmount(QString ind) {
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'"
        " AND result = \'1-0\'");
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getBlackWinsWithOpeningAmount(QString ind) {
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + ind + "\'"
        " AND result = \'0-1\'");
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getTournamentGamesAmount(const quint32 ind) {
    query = QSqlQuery("SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(ind));
    if(query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
quint32 SQLWorker::getTournamentWinsAmount(const quint32 ind, QString color) {
    QString win = (color == "white" ? "1-0" : "0-1");
    query = QSqlQuery("SELECT COUNT(*)"
            " FROM chess_games"
            " WHERE tournament_id = " + QString::number(ind) +\
            " AND result = \'" + win + "\'");
    
    if (query.next()) {
        return query.value(0).toInt();
    }
    
    
}

QVector <QPair<QString, quint32>> SQLWorker::getChessplayerOpeningCounts(quint32 ind, QString color) {
    query = QSqlQuery("SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id"
                  " WHERE " + color + "_id = " + QString::number(ind) +\
                  " GROUP BY openings.name ORDER BY amount DESC");

    QVector <QPair<QString, quint32>> result;
    while (query.next()) {
        result.push_back({queryString(0), query.value(1).toInt()});
    }

    return result;
}

void SQLWorker::setChessplayer(DMap player) {
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

    query.bindValue(":format", game["format"].toString());
    query.bindValue(":moves", game["moves"].toString());
    query.bindValue(":result", game["result"].toString());
    query.bindValue(":time_control", game["time_control"].toString());
    query.bindValue(":date",game["date"].toDate());
    query.bindValue(":white_id", getChessplayerID(game["white"].toString()));
    query.bindValue(":tournament_id", getTournamentID(game["tournament"].toString()));
    query.bindValue(":black_id", getChessplayerID(game["black"].toString()));
    query.bindValue(":opening_id", getOpeningID(game["opening"].toString()));
    query.bindValue(":game_id", game["id"].toInt());

    query.exec();

    emit gameSet();
}
void SQLWorker::setJudge(const DBMap judge) {

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
    query.bindValue(":judge_id", judge["id"].toInt());

    query.exec();

    qDebug() << query.lastError().text();
}
void SQLWorker::setOpening(const DBMap opening) {
    if (openingExists(opening["id"])) {
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
}
void SQLWorker::setPlace(const DBMap place) {
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
    query.bindValue(":place_id", place["id"].toInt());

    query.exec();
}
void SQLWorker::setTournament(const DBMap tournament) {
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

    query.bindValue(":tournament_id", tournament["id"].toInt());
    query.bindValue(":name", tournament["name"]);
    query.bindValue(":rating_restriction", tournament["rating_restriction"]);
    query.bindValue(":place_id", getPlaceID(tournament["city"], tournament["country"]));
    query.bindValue(":winner_id", getChessplayerID(tournament["winner"]));
    query.bindValue(":judge_id", getJudgeID(tournament["judge"]));

    query.exec();
}

bool SQLWorker::chessplayerExists (const quint32 ind) {
    query = QSqlQuery("SELECT * FROM chessplayers WHERE chessplayer_id = " + QString::number(ind));
    return query.next();
}
bool SQLWorker::gameExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM chess_games WHERE game_id = " + QString::number(ind)).next();
}
bool SQLWorker::judgeExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM judges WHERE judge_id = " + QString::number(ind)).next();
}
bool SQLWorker::openingExists(const QString ind) {
    QSqlQuery("SELECT * FROM openings WHERE eco_id = \'" + ind + "\'").next();
}
bool SQLWorker::placeExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM places WHERE place_id = " + QString::number(ind)).next();
}
bool SQLWorker::tournamentExists(const quint32 ind) {
    return QSqlQuery("SELECT * FROM tournaments WHERE tournament_id = " + QString::number(ind)).next();
}

inline QString SQLWorker::queryString(const quint32 x)
{
    return query.value(x).toString().simplified();
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
