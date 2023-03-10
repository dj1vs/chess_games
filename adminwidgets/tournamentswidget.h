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
    explicit TournamentsWidget(FormWidget *parent = nullptr);
    ~TournamentsWidget();
private:
    void loadPage();
    void setMaxInd() {curInd = worker->getMaxTournamentID();};

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
