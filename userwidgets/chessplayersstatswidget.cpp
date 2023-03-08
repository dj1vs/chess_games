#include "chessplayersstatswidget.h"

#include <QApplication>
#include <QDebug>
#include <QValueAxis>
#include <QBarCategoryAxis>

#include <QSqlQueryModel>
ChessplayersStatsWidget::ChessplayersStatsWidget(FormWidget *parent):
    FormWidget{parent} {

        formHeader = new FormHeader();
        formHeader->setTitle("Chessplayers Statistics");

        search = new QLineEdit;
        name = new QLineEdit();
        name->setReadOnly(true);

        gamesWhite = new QTableView();
        gamesBlack = new QTableView();
        openingsWhite = new QTableView();
        openingsBlack = new QTableView();
        strongestOponents = new QTableView();


        rating = new QSpinBox();
        rating->setMaximum(5000);
        birthYear = new QSpinBox();
        birthYear->setMaximum(2023);
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

        amount->setReadOnly(true);
        wins->setReadOnly(true);
        loses->setReadOnly(true);
        draws->setReadOnly(true);
        amountWhite->setReadOnly(true);
        winsWhite->setReadOnly(true);
        losesWhite->setReadOnly(true);
        drawsWhite->setReadOnly(true);
        amountBlack->setReadOnly(true);
        winsBlack->setReadOnly(true);
        losesBlack->setReadOnly(true);
        drawsBlack->setReadOnly(true);
        rating->setReadOnly(true);
        birthYear->setReadOnly(true);

        
        whiteOpeningsGraph = new QChartView();
        whiteOpeningsGraph->setMinimumSize(500, 500);
        blackOpeningsGraph = new QChartView();
        blackOpeningsGraph->setMinimumSize(500, 500);

        layout = new QVBoxLayout(this);
        layout->addWidget(formHeader);
        layout->addWidget(new QLabel("Search chessplayers by name:"));
        layout->addWidget(search);
        layout->addWidget(new QLabel("Name:"));
        layout->addWidget(name);
        layout->addWidget(new QLabel("ELO Rating:"));
        layout->addWidget(rating);
        layout->addWidget(new QLabel("Birth year:"));
        layout->addWidget(birthYear);
        layout->addWidget(new QLabel("Games amount:"));
        layout->addWidget(amount);
        layout->addWidget(new QLabel("Wins amount:"));
        layout->addWidget(wins);
        layout->addWidget(new QLabel("Loses amount:"));
        layout->addWidget(loses);
        layout->addWidget(new QLabel("Draws amount:"));
        layout->addWidget(draws);
        layout->addWidget(new QLabel("Games as white:"));
        layout->addWidget(gamesWhite);
        layout->addWidget(new QLabel("Games amount as white:"));
        layout->addWidget(amountWhite);
        layout->addWidget(new QLabel("Wins as white:"));
        layout->addWidget(winsWhite);
        layout->addWidget(new QLabel("Loses as white:"));
        layout->addWidget(losesWhite);
        layout->addWidget(new QLabel("Draws as white:"));
        layout->addWidget(drawsWhite);
        layout->addWidget(new QLabel("Games as black:"));
        layout->addWidget(gamesBlack);
        layout->addWidget(new QLabel("Games amount as black:"));
        layout->addWidget(amountBlack);
        layout->addWidget(new QLabel("Wins as black:"));
        layout->addWidget(winsBlack);
        layout->addWidget(new QLabel("Loses as black:"));
        layout->addWidget(losesBlack);
        layout->addWidget(new QLabel("Draws as black:"));
        layout->addWidget(drawsBlack);
        layout->addWidget(new QLabel("Opnenings as white:"));
        layout->addWidget(openingsWhite);
        layout->addWidget(new QLabel("Openings as black:"));
        layout->addWidget(openingsBlack);
        layout->addWidget(whiteOpeningsGraph);
        layout->addWidget(blackOpeningsGraph);
        layout->addWidget(new QLabel("Strongest opponents:"));
        layout->addWidget(strongestOponents);

        loadPage();

        connectFormHeader();

        searchCompleter = new QCompleter(chessplayers, this);
        search->setCompleter(searchCompleter);

        connect(search, &QLineEdit::returnPressed, this, [this] {
            QSqlQuery query("SELECT chessplayer_id"
                " FROM chessplayers"
                " WHERE name = \'" + search->text() + "\'");
            if (query.next()) {
                curInd = query.value(0).toInt();
                loadPage();
            } else {
                qDebug() << "No such chessplayer";
                search->clear();
            }
        });


}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}

inline void ChessplayersStatsWidget::loadPage() {
    loadChessplayers();
    loadBasicFields();
    loadAmountFields();
    loadGamesTables();
    loadOpeningsTables();
    loadStrongestOpponentsTable();
    loadOpeningsCharts();
}

void ChessplayersStatsWidget::loadBasicFields() {
    QString queryString = "SELECT name, elo_rating, birth_year FROM chessplayers WHERE chessplayer_id = ";

    queryString += QString::number(curInd);

    query = QSqlQuery(queryString);
    while(query.next()) {
        rating->setValue(query.value(1).toInt());
        birthYear->setValue(query.value(2).toInt());
        name->setText(query.value(0).toString().simplified());
    }
}

void ChessplayersStatsWidget::loadColorAmountFields(QString color) {
    QString queryString = "SELECT COUNT(*) from chess_games WHERE " + color + "_id = ";
    queryString += QString::number(curInd);
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
    queryString += QString::number(curInd) + ")";
    query = QSqlQuery(queryString);
    while(query.next()) {
        if (color == "white") {
            winsWhite->setValue(query.value(0).toInt());
        } else {
            winsBlack->setValue(query.value(0).toInt());
        }
    }

    queryString = "SELECT COUNT(*) from chess_games WHERE (result = '" + lose + "') AND (" + color + "_id = ";
    queryString += QString::number(curInd) + ")";
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
    QString queryString = "SELECT game_date AS Дата, white.name AS белые, black.name AS Чёрные, time_control AS \"Контроль времени\", format AS Формат, result AS Результат, moves AS Ходы"
                  " FROM chess_games"
                  " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
                  " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id";
    queryString += " WHERE " + color + "_id = " + QString::number(curInd);
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery(queryString);

    if (color == "white") {
        gamesWhite->setModel(model);
        resizeTableView(gamesWhite);
        gamesWhite->show();
    } else {
        gamesBlack->setModel(model);
        resizeTableView(gamesBlack);
        gamesBlack->show();
    }
}

inline void ChessplayersStatsWidget::loadGamesTables() {
    loadColorGamesTable("white");
    loadColorGamesTable("black");
}
void ChessplayersStatsWidget::loadColorOpeningsTable(QString color){
    QString queryString = "SELECT openings.name AS Дебют, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    queryString += " WHERE " + color + "_id = " + QString::number(curInd);
    queryString += " GROUP BY openings.name ORDER BY amount DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);
    model->setHeaderData(1, Qt::Horizontal, tr("Количество игр"));

    if (color == "white") {
        openingsWhite->setModel(model);
        resizeTableView(openingsWhite);
        openingsWhite->show();
    } else {
        openingsBlack->setModel(model);
        resizeTableView(openingsBlack);
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
    queryString += " WHERE black_id = " + QString::number(curInd);
    queryString += " UNION DISTINCT"
                   " SELECT chessplayers.name, chessplayers.elo_rating"
                   " FROM chess_games"
                   " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id";
    queryString += " WHERE white_id = " + QString::number(curInd);
    queryString += " ORDER BY elo_rating DESC";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryString);
    model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(1, Qt::Horizontal, tr("Рейтинг"));

    strongestOponents->setModel(model);
    resizeTableView(strongestOponents);
    strongestOponents->show();
}
void ChessplayersStatsWidget::loadColorOpeningsChart(QString color) {
    QString queryString = "SELECT openings.name, COUNT(*) AS amount"
                  " FROM chess_games"
                  " INNER JOIN openings ON opening_id = eco_id";
    queryString += " WHERE " + color + "_id = " + QString::number(curInd);
    queryString += " GROUP BY openings.name ORDER BY amount DESC";

    query = QSqlQuery(queryString);

    quint32 maxAmount = 0;
    QBarSeries *series = new QBarSeries();
    while (query.next()) {
        QString name = query.value(0).toString().simplified();
        quint32 amount = query.value(1).toInt();
        maxAmount = std::max(maxAmount, amount);
        QBarSet *set = new QBarSet(name);
        *set << amount;
        series->append(set);
    }

    QChart *chart = new QChart();
    chart->setTitle("Openings for " + color);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxAmount);
    axisY->setLabelFormat("%d");
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);
    axisY->setLabelFormat("%d");

    
    chart->addSeries(series);
    series->attachAxis(axisY);

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

void ChessplayersStatsWidget::loadChessplayers() {
    QSqlQuery query("SELECT name FROM chessplayers");
    while (query.next()) {
        chessplayers.push_back(query.value(0).toString().simplified());
    }
}
