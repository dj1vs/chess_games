#ifndef OPENINGSSTATSWIDGET_H
#define OPENINGSSTATSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QSpinBox>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QCompleter>
using namespace QtCharts;


class OpeningsStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit OpeningsStatsWidget(FormWidget *parent = nullptr);
    ~OpeningsStatsWidget();
private:
    void setMaxInd() {curInd = idList.size() - 1;};
    void loadPage();
    void loadAmounts();
    void loadBasicFields();
    void loadProbability();
    void loadTables();
    void loadChart();

    void loadIds();
    void loadOpenings();

    QString id;
    QStringList idList;
    QLineEdit *search, *name, *altName, *group, *moves, *namedAfter, *probability;
    QSpinBox *amount, *whiteWins, *blackWins, *draws;
    QTableView *chessplayersWhite, *chessplayersBlack;
    QChartView *chartView;

    QCompleter *searchCompleter;
    QStringList openings;




};
#endif //OPENINGSSTATSWIDGET_H
