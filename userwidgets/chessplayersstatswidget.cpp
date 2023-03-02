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
    loadAmountFields();
    loadGamesTables();
    loadOpeningsTables();
    loadStrongestOpponentsTable();
    loadOpeningsCharts();
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

void ChessplayersStatsWidget::loadColorAmountFields(QString color) {
    QString queryString = "SELECT COUNT(*) from chess_games WHERE " + color + "_id = ";
    queryString += QString::number(currentIndex);
    query = QSqlQuery(queryString);
    while(query.next()) {
        if (color == "white") {
            amountWhite->setValue(query.value(0).toInt());
        } else {
            amountBlack->setValue(query.value(0).toInt());
        }
    }

    QString win = (color == "white" ? "1-0" : "0-1");
    QString lose = (color == "white" ? "0-1" : "1-0");
    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '" + win + "') AND (" + color + "_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        if (color == "white") {
            winsWhite->setValue(query.value(0).toInt());
        } else {
            winsBlack->setValue(query.value(0).toInt());
        }
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '" + lose + "') AND (" + color + "_id = ";
    queryString += QString::number(currentIndex) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        if (color == "white") {
            losesWhite->setValue(query.value(0).toInt());
        } else {
            losesBlack->setValue(query.value(0).toInt());
        }
    }
}

inline void ChessplayersStatsWidget::loadAmountFields() {
    loadColorAmountFields("white");
    loadColorAmountFields("black");
    amount->setValue(amountBlack->value() + amountWhite->value());
    loses->setValue(losesBlack->value() + losesWhite->value());
    wins->setValue(winsWhite->value() + winsBlack->value());
    draws->setValue(amount->value() - wins->value() - loses->value());
    drawsBlack->setValue(amountBlack->value() - winsBlack->value() - losesBlack->value());
    drawsWhite->setValue(amountWhite->value() - winsWhite->value() - losesWhite->value());
}

void ChessplayersStatsWidget::loadColorGamesTable(QString color) {
    QString queryString = "SELECT game_date, white.name, black.name, time_control, format, result, moves"
                  " FROM chess_games"
                  " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
                  " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id";
    queryString += " WHERE " + color + "_id = " + QString::number(currentIndex);
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery(queryString);

    if (color == "white") {
        gamesWhite->setModel(model);
        gamesWhite->show();
    } else {
        gamesBlack->setModel(model);
        gamesBlack->show();
    }
}

inline void ChessplayersStatsWidget::loadGamesTables() {
    loadColorGamesTable("white");
    loadColorGamesTable("black");
}
void ChessplayersStatsWidget::loadColorOpeningsTable(QString color){
    QString queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    queryString += " WHERE " + color + "_id = " + QString::number(currentIndex);
    queryString += " GROUP BY openings.name ORDER BY amount DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);

    if (color == "white") {
        openingsWhite->setModel(model);
        openingsWhite->show();
    } else {
        openingsBlack->setModel(model);
        openingsBlack->show();
    }
}
inline void ChessplayersStatsWidget::loadOpeningsTables() {
    loadColorOpeningsTable("white");
    loadColorOpeningsTable("black");
}
void ChessplayersStatsWidget::loadStrongestOpponentsTable() {
    QString queryString = " SELECT chessplayers.name, chessplayers.elo_rating"
                  " FROM chess_games"
                  " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id";
    queryString += " WHERE black_id = " + QString::number(currentIndex);
    queryString += " UNION DISTINCT"
                   " SELECT chessplayers.name, chessplayers.elo_rating"
                   " FROM chess_games"
                   " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id";
    queryString += " WHERE white_id = " + QString::number(currentIndex);
    queryString += " ORDER BY elo_rating DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);

    strongestOponents->setModel(model);
    strongestOponents->show();
}
void ChessplayersStatsWidget::loadColorOpeningsChart(QString color) {
    QString queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    queryString += " WHERE " + color + "_id = " + QString::number(currentIndex);
    queryString += " GROUP BY openings.name ORDER BY amount DESC";

    query = QSqlQuery(queryString);

    quint32 maxAmount = 0;
    QBarSeries *series = new QBarSeries();
    while (query.next()) {
        QString name = query.value(0).toString();
        quint32 amount = query.value(1).toInt();
        maxAmount = std::max(maxAmount, amount);
        QBarSet *set = new QBarSet(name);
        *set << amount;
        series->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Openings for " + color);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxAmount);
    axisY->setLabelFormat("%d");
    series->attachAxis(axisY);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);
    axisY->setLabelFormat("%d");

    if (color ==  "white") {
        whiteOpeningsGraph->setChart(chart);
    }
    else {
        blackOpeningsGraph->setChart(chart);
    }
}
inline void ChessplayersStatsWidget::loadOpeningsCharts() {
    loadColorOpeningsChart("white");
    loadColorOpeningsChart("black");

}
