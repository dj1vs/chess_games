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
#include <QVector>
#include <QSpinBox>
#include <QLabel>

class TournamentsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit TournamentsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~TournamentsWidget();
public:
    void loadTournament(DMap map);
    void loadTournamentGames(DTable table);
private:
    void loadPage();
    void connectWorker();

    QSpinBox *id, *ratingRestriction;
    QLineEdit *name, *winner, *city, *country, *judge;
    QPushButton *save;
    QTableView *playedGames;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;
signals:
    void getTournament(quint32 ind);
    void getTournamentGames(quint32 ind);

    void setTournament(DMap map);
     
    
};
#endif //TOURNAMENTSWIDGET_H
