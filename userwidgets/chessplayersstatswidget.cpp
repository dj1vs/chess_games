#include "chessplayersstatswidget.h"

#include <QApplication>
#include <QDebug>
#include <QValueAxis>
#include <QBarCategoryAxis>

#include <QSqlQueryModel>
ChessplayersStatsWidget::ChessplayersStatsWidget(QWidget *parent):
    QWidget{parent} {

        goBack = new QPushButton("Go back");
        previous = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowLeft), "");
        next = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowRight), "");
        print = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon), "");
        search = new QLineEdit();
        name = new QLineEdit();

        gamesWhite = new QTableView();
        gamesBlack = new QTableView();
        openingsWhite = new QTableView();
        openingsBlack = new QTableView();
        strongestOponents = new QTableView();

        rating = new QSpinBox();
        rating->setMaximum(5000);
        birthYear = new QSpinBox();
        birthYear->setMaximum(3000);
        amount = new QSpinBox();
        wins = new QSpinBox();
        loses = new QSpinBox();
        draws = new QSpinBox();
        amountWhite = new QSpinBox();
        winsWhite = new QSpinBox();
        losesWhite = new QSpinBox();
        drawsWhite = new QSpinBox();
        amountBlack = new QSpinBox();
        winsBlack = new QSpinBox();
        losesBlack = new QSpinBox();
        drawsBlack = new QSpinBox();
        
        
        whiteOpeningsGraph = new QChartView();
        blackOpeningsGraph = new QChartView();
        

        layout = new QGridLayout();
        layout->addWidget(goBack, 0, 0, 1, 1);
        layout->addWidget(previous, 0, 1, 1, 1);
        layout->addWidget(next, 0, 2, 1, 1);
        layout->addWidget(print, 0, 3, 1, 1);
        layout->addWidget(new QLabel("Search chessplayers by name:"), 1, 0, 1, 1);
        layout->addWidget(search, 1, 1, 1, 1);
        layout->addWidget(new QLabel("Name:"), 2, 0, 1, 1);
        layout->addWidget(name, 2, 1, 1, 1);
        layout->addWidget(new QLabel("ELO Rating:"), 3, 0, 1, 1);
        layout->addWidget(rating, 3, 1, 1, 1);
        layout->addWidget(new QLabel("Birth year:"), 3, 2, 1, 1);
        layout->addWidget(birthYear, 3, 3, 1, 1);
        layout->addWidget(new QLabel("Games amount:"), 4, 0, 1, 1);
        layout->addWidget(amount, 4, 1, 1, 1);
        layout->addWidget(new QLabel("Wins amount:"), 5, 0, 1, 1);
        layout->addWidget(wins, 5, 1, 1, 1);
        layout->addWidget(new QLabel("Loses amount:"), 5, 2, 1, 1);
        layout->addWidget(loses, 5, 3, 1, 1);
        layout->addWidget(new QLabel("Draws amount:"), 6, 0, 1, 1);
        layout->addWidget(draws, 6, 1, 1, 1);
        layout->addWidget(new QLabel("Games as white:"), 7, 0, 1, 1);
        layout->addWidget(gamesWhite, 7, 1, 1, 4);
        layout->addWidget(new QLabel("Games amount as white:"), 8, 0, 1, 1);
        layout->addWidget(amountWhite, 8, 1, 1, 1);
        layout->addWidget(new QLabel("Wins as white:"), 9, 0, 1, 1);
        layout->addWidget(winsWhite, 9, 1, 1, 1);
        layout->addWidget(new QLabel("Loses as white:"), 9, 2, 1, 1);
        layout->addWidget(losesWhite, 9, 3, 1, 1);
        layout->addWidget(new QLabel("Draws as white:"), 10, 0, 1, 1);
        layout->addWidget(drawsWhite, 10, 1, 1, 1);
        layout->addWidget(new QLabel("Games as black:"), 11, 0, 1, 1);
        layout->addWidget(gamesBlack, 11, 1, 1, 4);
        layout->addWidget(new QLabel("Games amount as black:"),12, 0, 1, 1);
        layout->addWidget(amountBlack, 12, 1, 1, 1);
        layout->addWidget(new QLabel("Wins as black:"), 13, 0, 1, 1);
        layout->addWidget(winsBlack, 13, 1, 1, 1);
        layout->addWidget(new QLabel("Loses as black:"), 13, 2, 1, 1);
        layout->addWidget(losesBlack, 13, 3, 1, 1);
        layout->addWidget(new QLabel("Draws as black:"), 14, 0, 1, 1);
        layout->addWidget(drawsBlack, 14, 1, 1, 1);
        layout->addWidget(new QLabel("Opnenings as white:"), 15, 0, 1, 1);
        layout->addWidget(openingsWhite, 15, 1, 1, 1);
        layout->addWidget(new QLabel("Openings as black:"), 16, 0, 1, 1);
        layout->addWidget(openingsBlack, 16, 1, 1, 1);
        layout->addWidget(whiteOpeningsGraph, 17, 0, 1, 4);
        layout->addWidget(blackOpeningsGraph, 18, 0, 1, 4);
        layout->addWidget(new QLabel("Strongest opponents:"), 19, 0, 1, 1);
        layout->addWidget(strongestOponents, 19, 1, 1, 2);

        layout->setSpacing(3);

        setLayout(layout);

        loadStatistics();

        connect(goBack, &QPushButton::clicked, this, [this] {
           emit goBackSignal();
        });
        connect(previous, &QPushButton::clicked, this, [this] {
            if (currentIndex - 1) {
                --currentIndex;
                loadStatistics();
            }
        });
        connect(next, &QPushButton::clicked, this, [this] {
            ++currentIndex;
            loadStatistics();
        });
}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}

void ChessplayersStatsWidget::loadStatistics() {
    loadBasicFields();

    QString queryString = "SELECT COUNT(*) from chess_games WHERE white_id = ";
    queryString += QString::number(currentIndex);
    query = QSqlQuery(queryString);
    while(query.next()) {
        amountWhite->setValue(query.value(0).toInt());
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE black_id = ";
    queryString += QString::number(currentIndex);
    query = QSqlQuery(queryString);
    while(query.next()) {
        amountBlack->setValue(query.value(0).toInt());
    }

    amount->setValue(amountBlack->value() + amountWhite->value());

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '1-0') AND (white_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        winsWhite->setValue(query.value(0).toInt());
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '0-1') AND (black_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        winsBlack->setValue(query.value(0).toInt());
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '1-0') AND (black_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        losesBlack->setValue(query.value(0).toInt());
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '0-1') AND (white_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        losesWhite->setValue(query.value(0).toInt());
    }

    loses->setValue(losesBlack->value() + losesWhite->value());

    wins->setValue(winsWhite->value() + winsBlack->value());

    draws->setValue(amount->value() - wins->value() - loses->value());

    drawsBlack->setValue(amountBlack->value() - winsBlack->value() - losesBlack->value());
    drawsWhite->setValue(amountWhite->value() - winsWhite->value() - losesWhite->value());

    queryString = "SELECT game_date, white.name, black.name, time_control, format, result, moves"
                  " FROM chess_games"
                  " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
                  " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id";
    QString white = " WHERE white_id = " + QString::number(currentIndex);
    QSqlQueryModel *modelWhite = new QSqlQueryModel;

    qDebug() << queryString + white;
    modelWhite->setQuery(queryString + white);

    gamesWhite->setModel(modelWhite);
    gamesWhite->show();

    QString black = " WHERE black_id = " + QString::number(currentIndex);
    QSqlQueryModel *modelBlack = new QSqlQueryModel;
    modelBlack->setQuery(queryString + black);

    gamesBlack->setModel(modelBlack);
    gamesBlack->show(); 

    queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    QString ending = " GROUP BY openings.name ORDER BY amount DESC";
    white = " WHERE white_id = " + QString::number(currentIndex);

    QSqlQueryModel *opModelWhite = new QSqlQueryModel();
    opModelWhite->setQuery(queryString + white + ending);

    openingsWhite->setModel(opModelWhite);
    openingsWhite->show();

    QSqlQueryModel *opModelBlack = new QSqlQueryModel();
    black = " WHERE black_id = " + QString::number(currentIndex);
    opModelBlack->setQuery(queryString + black + ending);

    openingsBlack->setModel(opModelBlack);
    openingsBlack->show();

    queryString = " SELECT chessplayers.name, chessplayers.elo_rating"
                  " FROM chess_games"
                  " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id";
    queryString += " WHERE black_id = " + QString::number(currentIndex);
    queryString += " UNION DISTINCT"
                   " SELECT chessplayers.name, chessplayers.elo_rating"
                   " FROM chess_games"
                   " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id";
    queryString += " WHERE white_id = " + QString::number(currentIndex);
    queryString += " ORDER BY elo_rating DESC";

    QSqlQueryModel *opponentsModel = new QSqlQueryModel();
    opponentsModel->setQuery(queryString);

    strongestOponents->setModel(opponentsModel);
    strongestOponents->show();

    queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    ending = " GROUP BY openings.name ORDER BY amount DESC";
    white = " WHERE white_id = " + QString::number(currentIndex);

    query = QSqlQuery(queryString + white + ending);

    quint32 maxAmount = 0;
    QBarSeries *whiteSeries = new QBarSeries();
    while (query.next()) {
        QString name = query.value(0).toString();
        quint32 amount = query.value(1).toInt();
        maxAmount = std::max(maxAmount, amount);
        QBarSet *set = new QBarSet(name);
        *set << amount;
        whiteSeries->append(set);
    }



//    QBarCategoryAxis *axisX = new QBarCategoryAxis();

    QChart *whiteChart = new QChart();
    whiteChart->addSeries(whiteSeries);
    whiteChart->setTitle("White openings");
    whiteChart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxAmount);
    axisY->setLabelFormat("%d");
    whiteSeries->attachAxis(axisY);
    whiteChart->addAxis(axisY, Qt::AlignLeft);
    whiteChart->legend()->setAlignment(Qt::AlignBottom);
    axisY->setLabelFormat("%d");

    queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    ending = " GROUP BY openings.name ORDER BY amount DESC";
    black = " WHERE black_id = " + QString::number(currentIndex);

    query = QSqlQuery(queryString + black + ending);

    maxAmount = 0;
    QBarSeries *blackSeries = new QBarSeries();
    while (query.next()) {
        QString name = query.value(0).toString();
        quint32 amount = query.value(1).toInt();
        maxAmount = std::max(maxAmount, amount);
        QBarSet *set = new QBarSet(name);
        *set << amount;
        blackSeries->append(set);
    }

    QChart *blackChart = new QChart();
    blackChart->addSeries(blackSeries);
    blackChart->setTitle("Black openings");
    blackChart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY2 = new QValueAxis();
    axisY2 ->setRange(0, maxAmount);
    axisY2->setLabelFormat("%d");
    blackSeries->attachAxis(axisY2);
    blackChart->addAxis(axisY2, Qt::AlignLeft);
    blackChart->legend()->setAlignment(Qt::AlignBottom);
    axisY2->setLabelFormat("%d");



    whiteOpeningsGraph->setChart(whiteChart);
    blackOpeningsGraph->setChart(blackChart);



}

void ChessplayersStatsWidget::loadBasicFields() {
    QString queryString = "SELECT name, elo_rating, birth_year FROM chessplayers WHERE chessplayer_id = ";

    queryString += QString::number(currentIndex);

    query = QSqlQuery(queryString);
    while(query.next()) {
        rating->setValue(query.value(1).toInt());
        birthYear->setValue(query.value(2).toInt());
        name->setText(query.value(0).toString());
    }
}
