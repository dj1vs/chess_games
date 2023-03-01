#ifndef CHESSPLAYERSSTATSWIDGET_H
#define CHESSPLAYERSSTATSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QSpinBox>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QPushButton>

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>

using namespace QtCharts;


class ChessplayersStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessplayersStatsWidget(QWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
private:
    void loadStatistics();

    qint32 currentIndex = 0;

    QPushButton *goBack;
    QPushButton *previous;
    QPushButton *next;
    QPushButton *print;

    QLineEdit *search;
    QLineEdit *name;
    QSpinBox *rating;
    QSpinBox *birthYear;
    QSpinBox *amount;
    QSpinBox *wins;
    QSpinBox *loses;
    QSpinBox *draws;
    QTableView *gamesWhite;
    QTableView *gamesBlack;
    QSpinBox *amountWhite;
    QSpinBox *winsWhite;
    QSpinBox *losesWhite;
    QSpinBox *drawsWhite;
    QSpinBox *amountBlack;
    QSpinBox *winsBlack;
    QSpinBox *losesBlack;
    QSpinBox *drawsBlack;
    QTableView *openingsWhite;
    QTableView *openingsBlack;
    QChartView *whiteOpeningsGraph;
    QChartView *blackOpeningsGraph;
    QTableView *strongestOponents;

    QGridLayout *layout;

};
#endif //CHESSPLAYERSSTATSWIDGET_H
