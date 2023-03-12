#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QObject>
#include <QSqlQuery>
#include <QMap>
#include <QVariant>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QVector>
#include <QPair>
#include <QSqlDatabase>
#include <QThread>

typedef QMap<QString, QString> DBMap;

#define DMap QMap<QString, QVariant>
#define DTable QVector<QStringList>

#define qstring toString().simplified()

class SQLWorker : public QObject
{
    Q_OBJECT
public slots:
    void connectToDB();
    void authSuccess(const QString login, const QString pass);

    //SETS

    void setChessplayer(DMap player);
    void setGame(DMap game);

    //SIMPLE GETS

    void getChessplayer(const quint32 ind);
    void getGame(quint32 ind);
    void getPlace(quint32 ind);
    void getJudge(quint32 ind);
    void getOpening(QString ind);
    void getTournament(quint32 ind);

    //TABLES

    void getJudgesTournaments(quint32 ind);
    void getPlacesTournaments(quint32 ind);
    void getTournamentGames(quint32 ind);
    void getChessplayerStrongestOpponents(quint32 ind);
    void getChessplayerGames(quint32 ind, QString color);
    void getChessplayerOpenings(quint32 ind, QString color);
    void getOpeningPlayers(QString ind, QString color);
    void getBestTournamentPlayers(quint32 ind, QString color);
    void getGamesCrossRequest();

    //GET ALLS

    void getAllChessplayersNames();

    void getAllOpeningsIds();
public:
    explicit SQLWorker(QObject *parent = nullptr);
    ~SQLWorker();
    QStringList getAllOpeningsNames();
    QStringList getAllTournamentsNames();

    quint32 getMaxTournamentID();
    quint32 getMaxGameID();
    quint32 getMaxPlaceID();
    quint32 getMaxChessplayerID();
    quint32 getMaxJudgeID();
    quint32 getGamesAmount();

    quint32 getChessplayerID(const QString name);
    QString getOpeningID(const QString name);
    quint32 getTournamentID(const QString name);
    quint32 getJudgeID(const QString name);
    quint32 getPlaceID(const QString city, const QString country);

    quint32 getChessplayerGamesAmount(quint32 ind, QString color);
    quint32 getChessplayerWins(quint32 ind, QString color);
    quint32 getChessplayerLoses(quint32 ind, QString color);
    quint32 getGamesWithOpeningAmount(QString ind);
    quint32 getWhiteWinsWithOpeningAmount(QString ind);
    quint32 getBlackWinsWithOpeningAmount(QString ind);
    quint32 getTournamentGamesAmount(const quint32 ind);
    quint32 getTournamentWinsAmount(const quint32 ind, QString color);

    QVector <QPair<QString, quint32>> getChessplayerOpeningCounts(quint32 ind, QString color);

    void setJudge(const DBMap judge);
    void setOpening(const DBMap opening);
    void setPlace(const DBMap place);
    void setTournament(const DBMap tournament);
private:
    bool chessplayerExists (const quint32 ind);
    bool gameExists(const quint32 ind);
    bool judgeExists(const quint32 ind);
    bool openingExists(const QString ind);
    bool placeExists(const quint32 ind);
    bool tournamentExists(const quint32 ind);
    QStringList allChessplayersNames();



    

    QSqlQuery query;
    QSqlDatabase db;

    inline QString queryString(const quint32 x);
signals:
    void authResultReady(bool res);

    //SIMPLE GETS

    void chessplayerReady(const DMap &map);
    void gameReady(const DMap &map);
    void placeReady(const DMap &map);
    void judgeReady(const DMap &map);
    void tournamentReady(const DMap &map);
    void openingReady(const DMap &map);

    //TABLES

    void judgesTournamentsReady(DTable table);
    void placesTournamentsReady(DTable table);
    void tournamentGamesReady(DTable table);
    void chessplayerGamesReady(DTable table, QString color);
    void chessplayerOpeningsReady(DTable table, QString color);
    void chessplayerStrongestOpponentsReady(DTable table);
    void openingPlayersReady(DTable table, QString color);
    void bestTournamentPlayersReady(DTable table, QString color);
    void gamesCrossRequestReady(DTable table);

    //GET ALLS

    void allOpeningsIdsReady(QStringList ids);
    void allChessplayersNamesReady(QStringList names);

    //SETS

    void chessplayerSet();
    void gameSet();

};

#endif // SQLWORKER_H
