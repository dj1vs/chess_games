#ifndef OPENINGSSTATSWIDGET_H
#define OPENINGSSTATSWIDGET_H

#include "../formheader.h"

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

#include <QGridLayout>
#include <QVBoxLayout>

using namespace QtCharts;


class OpeningsStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit OpeningsStatsWidget(QWidget *parent = nullptr);
    ~OpeningsStatsWidget();
private:
    void loadBasicFields();
    void loadAmounts();
    void loadProbability();
    void loadTables();
    void loadChart();

    void loadIds();

    QString id;
    QStringList idList;
    FormHeader *formHeader;
    QLineEdit *search, *name, *altName, *group, *moves, *namedAfter, *probability;
    QSpinBox *amount, *whiteWins, *blackWins, *draws;
    QTableView *chessplayersWhite, *chessplayersBlack;
    QChartView *chartView;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;




};
#endif //OPENINGSSTATSWIDGET_H
