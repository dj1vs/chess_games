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

typedef QMap<QString, QString> DBMap;

class SQLWorker : public QObject
{
    Q_OBJECT
public:
    explicit SQLWorker(QObject *parent = nullptr);
    DBMap getPlace(const quint32 ind);
    DBMap getChessplayer(const quint32 ind);
    DBMap getGame(const quint32 ind);
    DBMap getJudge(const quint32 ind);
    DBMap getOpening(const QString ind);
    DBMap getTournament(const quint32 ind);
    
    QSqlQueryModel* getJudgesTournaments(const quint32 ind);
    QSqlQueryModel* getPlacesTournaments(const quint32 ind);
    QSqlQueryModel* getTournamentGames(const quint32 ind);
    QSqlQueryModel* getChessplayerGames(const quint32 ind, const QString color);
    QSqlQueryModel *getChessplayerOpenings(const quint32 ind, const QString color);
    QSqlQueryModel *getChessplayerStrongestOpponents(const quint32 ind);
    QSqlQueryModel *getOpeningPlayers(QString ind, QString color);
    QSqlQueryModel *getBestTournamentPlayers(quint32 ind, QString color);

    QStandardItemModel *getGamesCrossRequest();

    QStringList getAllChessplayersNames();
    QStringList getAllOpeningsNames();
    QStringList getAllTournamentsNames();
    QStringList getAllOpeningdIds();

    quint32 getChessplayerID(const QString name);
    QString getOpeningID(const QString name);
    quint32 getTournamentID(const QString name);
    quint32 getJudgeID(const QString name);
    quint32 getPlaceID(const QString city, const QString country);

    quint32 getMaxTournamentID();
    quint32 getMaxGameID();
    quint32 getMaxPlaceID();
    quint32 getMaxChessplayerID();
    quint32 getMaxJudgeID();
    quint32 getGamesAmount();

    quint32 getChessplayerGamesAmount(quint32 ind, QString color);
    quint32 getChessplayerWins(quint32 ind, QString color);
    quint32 getChessplayerLoses(quint32 ind, QString color);
    quint32 getGamesWithOpeningAmount(QString ind);
    quint32 getWhiteWinsWithOpeningAmount(QString ind);
    quint32 getBlackWinsWithOpeningAmount(QString ind);
    quint32 getTournamentGamesAmount(const quint32 ind);
    quint32 getTournamentWinsAmount(const quint32 ind, QString color);

    QVector <QPair<QString, quint32>> getChessplayerOpeningCounts(quint32 ind, QString color);

    void setChessplayer(const DBMap player);
    void setGame(const DBMap game);
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

    QSqlQuery query;
    inline QString queryString(const quint32 x);
signals:

};

#endif // SQLWORKER_H
