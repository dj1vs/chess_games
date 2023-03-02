#include "openingsstatswidget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
OpeningsStatsWidget::OpeningsStatsWidget(QWidget *parent):
    QWidget{parent} {
    search = new QLineEdit();
    name = new QLineEdit();
    altName = new QLineEdit();
    group = new QLineEdit();
    moves = new QLineEdit();
    namedAfter = new QLineEdit();
    probability = new QLineEdit();
    amount = new QSpinBox();
    whiteWins = new QSpinBox();
    blackWins = new QSpinBox();
    draws = new QSpinBox();
    chessplayersBlack = new QTableView();
    chessplayersWhite = new QTableView();
    chartView = new QChartView();

    formHeader = new FormHeader();
    formHeader->setTitle("Openings statistics");

    pageLayout = new QGridLayout();
    pageLayout->addWidget(new QLabel("Search:"), 1, 0, 1, 1);
    pageLayout->addWidget(search, 1, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Name:"), 2, 0, 1, 1);
    pageLayout->addWidget(name, 2, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Alternative names:"), 3, 0, 1, 1);
    pageLayout->addWidget(altName, 3, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Group:"), 4, 0, 1, 1);
    pageLayout->addWidget(group, 4, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Moves:"), 5, 0, 1, 1);
    pageLayout->addWidget(moves, 5, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Named after:"), 6, 0, 1, 1);
    pageLayout->addWidget(namedAfter, 6, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Games amount:"), 7, 0, 1, 1);
    pageLayout->addWidget(amount, 7, 1, 1, 1);
    pageLayout->addWidget(new QLabel("White wins:"), 8, 0, 1, 1);
    pageLayout->addWidget(whiteWins, 8, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Black wins:"), 9, 0, 1, 1);
    pageLayout->addWidget(blackWins,9, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Draws:"),10, 0, 1, 1);
    pageLayout->addWidget(draws, 10, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Probability:"), 11, 0, 1, 1);
    pageLayout->addWidget(probability, 11, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Chessplayers which played as white:"), 12, 0, 1, 1);
    pageLayout->addWidget(chessplayersWhite, 12, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Chessplayers which played as black:"), 13, 0, 1, 1);
    pageLayout->addWidget(chessplayersBlack, 13, 1, 1, 1);
    pageLayout->addWidget(chartView, 14, 0, 1, 1);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);
    setLayout(mainLayout);

    loadIds();
    loadBasicFields();
    loadAmounts();
    loadProbability();
    loadTables();
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}

void OpeningsStatsWidget::loadIds() {
    QSqlQuery query("SELECT eco_id FROM openings ORDER BY eco_id");
    while(query.next()) {
        idList.push_back(query.value(0).toString().simplified());
    }
    id = idList[1];
    qDebug() << id;
}
void OpeningsStatsWidget::loadBasicFields() {
    QString queryString = "SELECT name, openings_group, moves, named_after, alternative_names \
    FROM openings WHERE eco_id = \'" + id + "\'";

    qDebug() << queryString;
    
    QSqlQuery query(queryString);

    while(query.next()) {
        name->setText(query.value(0).toString().simplified());
        group->setText(query.value(1).toString().simplified());
        moves->setText(query.value(2).toString().simplified());
        namedAfter->setText(query.value(3).toString().simplified());
        altName->setText(query.value(4).toString().simplified());
    }

}

void OpeningsStatsWidget::loadAmounts() {
    QString queryString = "SELECT COUNT(*) FROM chess_games WHERE opening_id = \'" + id + "\'";
    QSqlQuery query(queryString);
    while (query.next()) {
        amount->setValue(query.value(0).toInt());
    }
    
    queryString = "SELECT COUNT(*) FROM chess_games WHERE result = '1-0' AND opening_id = \'" + id + "\'";
    query = QSqlQuery(queryString);
    while (query.next()) {
        whiteWins->setValue(query.value(0).toInt());
    }

    queryString = "SELECT COUNT(*) FROM chess_games WHERE result = '0-1' AND opening_id = \'" + id + "\'";
    query = QSqlQuery(queryString);
    while (query.next()) {
        blackWins->setValue(query.value(0).toInt());
    }

    draws->setValue(amount->value() - blackWins->value() - whiteWins->value());
}

void OpeningsStatsWidget::loadProbability() {
    QString str = "SELECT COUNT(*) FROM chess_games";
    QSqlQuery query(str);
    double allGamesAmount;
    while (query.next()) {
        allGamesAmount = query.value(0).toInt();
    }

    probability->setText(QString::number(static_cast<double>(amount->value())/allGamesAmount * 100) + '%');
}

void OpeningsStatsWidget::loadTables() {
     QSqlQueryModel *whiteModel = new QSqlQueryModel;
     QString str = "SELECT name, elo_rating, COUNT(*) as cnt FROM chess_games INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id WHERE opening_id = \'" + id + "\'" + " GROUP BY chessplayers.name, elo_rating ORDER BY cnt DESC";
     qDebug() << str;
     whiteModel->setQuery(str);
     chessplayersWhite->setModel(whiteModel);
     chessplayersWhite->show();


     QSqlQueryModel *blackModel = new QSqlQueryModel;
     str = "SELECT name, elo_rating, COUNT(*) as cnt FROM chess_games INNER JOIN chessplayers ON black_id = chessplayers.chessplayer_id WHERE opening_id = \'" + id + "\'" + " GROUP BY chessplayers.name, elo_rating ORDER BY cnt DESC";
     qDebug() << str;
     blackModel->setQuery(str);
     chessplayersBlack->setModel(blackModel);
     chessplayersBlack->show();
}

void OpeningsStatsWidget::loadChart() {
    QSqlQuery query("SELECT COUNT(*) FROM chess_games WHERE result = '1-0' AND opening_id=\'" + id + "\'");
    quint32 white = 0, black = 0, draw = 0;
    while(query.next()) {
        white = query.value(0).toInt();
    }
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE result = '0-1' AND opening_id=\'" + id + "\'");
    while(query.next()) {
        black = query.value(0).toInt();
    }
    query = QSqlQuery("SELECT COUNT(*) FROM chess_games WHERE result = '1-1' AND opening_id=\'" + id + "\'");
    while(query.next()) {
        draw = query.value(0).toInt();
    }

    qDebug() << white << black << draw;

    QBarSeries *series = new QBarSeries;
    QBarSet *set = new QBarSet("1-0");
    *set << white; series->append(set);
    set = new QBarSet("0-1"); *set << black; series->append(set);
    set = new QBarSet("1-1"); *set << draw; series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Results");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, std::max(white, std::max(black, draw)));
    axisY->setLabelFormat("%d");
    series->attachAxis(axisY);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);
    axisY->setLabelFormat("%d");

    chartView->setChart(chart);



}
