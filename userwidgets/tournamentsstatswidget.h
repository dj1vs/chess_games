#ifndef TOURNAMENTSSTATSWIDGET_H
#define TOURNAMENTSSTATSWIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableView>

#include <QtCharts>

using namespace QtCharts;
class TournamentsStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit TournamentsStatsWidget(QWidget *parent = nullptr);
    ~TournamentsStatsWidget();
private:
    QLineEdit *search, *name, *winnersName, *judgesName, *country, *city;

};
#endif //TOURNAMENTSSTATSWIDGET_H
