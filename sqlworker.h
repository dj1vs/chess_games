#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QObject>
#include <QSqlQuery>
#include <QMap>

typedef QMap<QString, QString> DBMap;
#define queryString(x) query.value(x).toString().simplified()

class SQLWorker : public QObject
{
    Q_OBJECT
public:
    explicit SQLWorker(QObject *parent = nullptr);
    DBMap getPlace(quint32 ind);
private:
signals:

};

#endif // SQLWORKER_H
