#ifndef TOURNAMENTSWIDGET_H
#define TOURNAMENTSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableView>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QVector>
#include <QLabel>

class TournamentsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit TournamentsWidget(FormWidget *parent = nullptr);
    ~TournamentsWidget();
private:
    void loadPage();
    void setMaxInd() {QSqlQuery query("SELECT MAX(tournament_id) FROM tournaments");
    if (query.next()) {
        curInd = query.value(0).toInt();
    }};
    quint32 getWinnerID();
    quint32 getJudgeID();
    quint32 getPlaceID();
    void saveChanges();
    void loadBasics();
    void loadTable();

    QSpinBox *id, *ratingRestriction;
    QLineEdit *name, *winner, *city, *country, *judge;
    QPushButton *save;
    QTableView *playedGames;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;
     
    
};
#endif //TOURNAMENTSWIDGET_H
