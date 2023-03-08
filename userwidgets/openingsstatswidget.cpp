#include "openingsstatswidget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QChartView>

OpeningsStatsWidget::OpeningsStatsWidget(FormWidget *parent):
    FormWidget{parent} {
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

    name->setReadOnly(true);
    altName->setReadOnly(true);
    group->setReadOnly(true);
    moves->setReadOnly(true);
    namedAfter->setReadOnly(true);
    probability->setReadOnly(true);
    amount->setReadOnly(true);
    whiteWins->setReadOnly(true);
    blackWins->setReadOnly(true);
    draws->setReadOnly(true);

    formHeader = new FormHeader();
    formHeader->setTitle("Openings statistics");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Search:"));
    layout->addWidget(search);
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Alternative names:"));
    layout->addWidget(altName);
    layout->addWidget(new QLabel("Group:"));
    layout->addWidget(group);
    layout->addWidget(new QLabel("Moves:"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Named after:"));
    layout->addWidget(namedAfter);
    layout->addWidget(new QLabel("Games amount:"));
    layout->addWidget(amount);
    layout->addWidget(new QLabel("White wins:"));
    layout->addWidget(whiteWins);
    layout->addWidget(new QLabel("Black wins:"));
    layout->addWidget(blackWins);
    layout->addWidget(new QLabel("Draws:"));
    layout->addWidget(draws);
    layout->addWidget(new QLabel("Probability:"));
    layout->addWidget(probability);
    layout->addWidget(new QLabel("Chessplayers which played as white:"));
    layout->addWidget(chessplayersWhite);
    layout->addWidget(new QLabel("Chessplayers which played as black:"));
    layout->addWidget(chessplayersBlack);

    loadPage();

    connectFormHeader();

    searchCompleter = new QCompleter(openings, this);
    search->setCompleter(searchCompleter);
    connect(search, &QLineEdit::returnPressed, this, [this] {
        QString str = "SELECT eco_id FROM openings WHERE name = \'" + search->text() + "\'";
        QSqlQuery query(str);
        if (query.next()) {
            curInd = idList.indexOf(query.value(0).toString().simplified()) + 1; 
            id = idList[curInd - 1];
            loadPage();
        } else {
            qDebug() << query.lastError().text();
            qDebug() << str;
        }
    });
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}

void OpeningsStatsWidget::loadIds() {
    QSqlQuery query("SELECT eco_id FROM openings ORDER BY eco_id");
    idList.clear();
    while(query.next()) {
        idList.push_back(query.value(0).toString().simplified());
    }
    id = idList[curInd - 1];
}
void OpeningsStatsWidget::loadBasicFields() {
    QString queryString = "SELECT name, openings_group, moves, named_after, alternative_names \
    FROM openings WHERE eco_id = \'" + id + "\'";
    
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
     QString str = "SELECT name AS Имя, elo_rating AS Рейтинг, COUNT(*) as cnt FROM chess_games INNER JOIN chessplayers ON white_id = chessplayers.chessplayer_id WHERE opening_id = \'" + id + "\'" + " GROUP BY chessplayers.name, elo_rating ORDER BY cnt DESC";
     whiteModel->setQuery(str);
     whiteModel->setHeaderData(2, Qt::Horizontal, tr("Количество игр"));
     chessplayersWhite->setModel(whiteModel);
     resizeTableView(chessplayersWhite);
     chessplayersWhite->show();


     QSqlQueryModel *blackModel = new QSqlQueryModel;
     str = "SELECT name AS Имя, elo_rating AS Рейтинг, COUNT(*) as cnt FROM chess_games INNER JOIN chessplayers ON black_id = chessplayers.chessplayer_id WHERE opening_id = \'" + id + "\'" + " GROUP BY chessplayers.name, elo_rating ORDER BY cnt DESC";
     blackModel->setQuery(str);
     blackModel->setHeaderData(2, Qt::Horizontal, tr("Количество игр"));
     chessplayersBlack->setModel(blackModel);
     resizeTableView(chessplayersBlack);
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

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    series->append("White wins:", white);
    series->append("Black wins:", black);
    series->append("Draws:", draw);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Results with this opening:");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->legend()->setFont(QFont("Arial", 7));

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void OpeningsStatsWidget::loadPage() {
    if (curInd == idList.size()) {
        --curInd;
    }
    loadOpenings();
    loadIds();
    loadBasicFields();
    loadAmounts();
    loadProbability();
    loadTables();
    loadChart();
}

void OpeningsStatsWidget::loadOpenings() {
    QSqlQuery query("SELECT name FROM openings ORDER BY eco_id");
    while (query.next()) {
        openings.push_back(query.value(0).toString().simplified());
    }
}