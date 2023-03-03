#ifndef TOURNAMENTSSTATSWIDGET_H
#define TOURNAMENTSSTATSWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

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
    inline void loadPage();
    void loadBasics();
    void loadGameAmount();
    void loadChart();
    void loadTables();
    quint32 curInd = 1;

    FormHeader *formHeader;
    QLineEdit *search, *tournamentName, *winnersName, *judgesName, *country, *city;
    QSpinBox *ratingRestriction, *gamesAmount;
    QTableView *strongestPlayersWhite, *strongestPlayersBlack;
    QChartView *results;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;

};
#endif //TOURNAMENTSSTATSWIDGET_H
