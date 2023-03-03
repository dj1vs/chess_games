#ifndef TOURNAMENTSSTATSWIDGET_H
#define TOURNAMENTSSTATSWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include <QTableView>

#include <QChart>
#include <QChartView>

#include <QGridLayout>
#include <QVBoxLayout>

using namespace QtCharts;
class TournamentsStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit TournamentsStatsWidget(QWidget *parent = nullptr);
    ~TournamentsStatsWidget();
signals:
    void exit();
private:
    FormHeader *formHeader;
    QLineEdit *search, *tournamentName, *winnersName, *judgesName, *country, *city;
    QComboBox *ratingRestriction, *gamesAmount;
    QTableView *strongestPlayersWhite, *strongestPlayersBlack;
    QChartView *results;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //TOURNAMENTSSTATSWIDGET_H
