#include "sqlworker.h"

SQLWorker::SQLWorker(QObject *parent) : QObject(parent)
{

}

DBMap SQLWorker::getPlace(quint32 ind) {
    QSqlQuery query("SELECT city, country FROM places WHERE place_id = " + ind);
    DBMap map;
    while (query.next()) {
        map["city"]  = queryString(0);
        map["country"] = queryString(1);
    }

    return map;
}
