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

#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QCompleter>
using namespace QtCharts;


class OpeningsStatsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit OpeningsStatsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~OpeningsStatsWidget();
public slots:
    void loadIds(QStringList ids);
    void loadOpening(const DMap &map);
    void loadOpeningPlayers(DTable table, QString color);
private:
    void setMaxInd() {curInd = idList.size() - 1;};
    void loadPage();
    void connectWorker();
    void loadAmounts();
    void loadProbability();
    void loadChart();

    void loadOpenings();

    QString id;
    QStringList idList;
    QLineEdit *search, *name, *altName, *group, *moves, *namedAfter, *probability;
    QSpinBox *amount, *whiteWins, *blackWins, *draws;
    QTableView *chessplayersWhite, *chessplayersBlack;
    QChartView *chartView;

    QCompleter *searchCompleter;
    QStringList openings;
signals:
    void getAllOpeningsIds();
    void getOpening(QString ind);
    void getOpeningPlayers(QString ind, QString color);

    void idsSet();


};
#endif //OPENINGSSTATSWIDGET_H
