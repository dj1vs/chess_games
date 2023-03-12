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
    void setJudge(DMap judge);
    void setOpening(DMap opening);
    void setPlace(DMap place);
    void setTournament(DMap tournament);

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
    void getAllOpeningsNames();
    void getAllTournamentsNames();

    // GET IDS
    void getChessplayerID(QString name);
    void getOpeningID(QString name);
    void getTournamentID(QString name);
    void getJudgeID(QString name);
    void getPlaceID(QString city, QString country);

    //GET MAX IDS
    void getMaxTournamentID();
    void getMaxGameID();
    void getMaxPlaceID();
    void getMaxChessplayerID();
    void getMaxJudgeID();

    //GET AMOUNTS
    void getChessplayerGamesAmount(quint32 ind, QString color);
    void getChessplayerWins(quint32 ind, QString color);
    void getChessplayerLoses(quint32 ind, QString color);
    void getGamesWithOpeningAmount(QString ind);
    void getWhiteWinsWithOpeningAmount(QString ind);
    void getBlackWinsWithOpeningAmount(QString ind);
    void getTournamentGamesAmount(const quint32 ind);
    void getTournamentWinsAmount(const quint32 ind, QString color);
    void getGamesAmount();

    void getChessplayerOpeningCounts(quint32 ind, QString color);
public:
    explicit SQLWorker(QObject *parent = nullptr);
    ~SQLWorker();
private:
    bool chessplayerExists (const quint32 ind);
    bool gameExists(const quint32 ind);
    bool judgeExists(const quint32 ind);
    bool openingExists(const QString ind);
    bool placeExists(const quint32 ind);
    bool tournamentExists(const quint32 ind);
    QStringList allChessplayersNames();

    quint32 chessplayerID(const QString name);
    QString openingID(const QString name);
    quint32 tournamentID(const QString name);
    quint32 judgeID(const QString name);
    quint32 placeID(const QString city, const QString country);

    QSqlDatabase db;
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
    void allOpeningsNamesReady(QStringList names);
    void allTournamentsNamesReady(QStringList names);

    //GET IDS

    void chessplayerIDReady(quint32 id);
    void openingIDReady(QString id);
    void tournamentIDReady(quint32 id);
    void judgeIDReady(quint32 id);
    void placeIDReady(quint32 id);

    //GET MAX IDS
    void maxTournamentIDReady(quint32 id);
    void maxGameIDReady(quint32 id);
    void maxPlaceIDReady(quint32 id);
    void maxChessplayerIDReady(quint32 id);
    void maxJudgeIDReady(quint32 id);

    //GET AMOUNTS

    void chessplayerGamesAmountReady(quint32 amount,QString color);
    void chessplayerWinsReady(quint32 amount,QString color);
    void chessplayerLosesReady(quint32 amount,QString color);
    void gamesWithOpeningAmountReady(quint32 amount);
    void whiteWinsWithOpeningAmountReady(quint32 amount);
    void blackWinsWithOpeningAmountReady(quint32 amount);
    void tournamentGamesAmountReady(quint32 amount);
    void tournamentWinsAmountReady(quint32 amount, QString color);
    void gamesAmountReady(quint32 amount);

    void chessplayerOpeningCountsReady(DMap vec, QString color);

    //SETS

    void chessplayerSet();
    void gameSet();
    void judgeSet();
    void openingSet();
    void placeSet();
    void tournamentSet();

};

#endif // SQLWORKER_H
