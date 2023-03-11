#include "chessplayersstatswidget.h"

#include <QApplication>
#include <QDebug>
#include <QValueAxis>
#include <QBarCategoryAxis>

ChessplayersStatsWidget::ChessplayersStatsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent}{

        worker = w;

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
        birthYear = new QSpinBox();
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

        rating->setRange(0, 4000);
        birthYear->setRange(1400, 2023);
        amount->setRange(0, 99999); 
        wins->setRange(0, 99999); 
        loses->setRange(0, 99999); 
        draws->setRange(0, 99999); 
        amountWhite->setRange(0, 99999); 
        winsWhite->setRange(0, 99999); 
        losesWhite->setRange(0, 99999);
        drawsWhite->setRange(0, 99999); 
        amountBlack->setRange(0, 99999); 
        winsBlack->setRange(0, 99999); 
        losesBlack->setRange(0, 99999); 
        drawsBlack->setRange(0, 99999);

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
        whiteOpeningsGraph->setMinimumHeight(300);
        blackOpeningsGraph = new QChartView();
        blackOpeningsGraph->setMinimumHeight(300);

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

        searchCompleter = new QCompleter(worker->getAllChessplayersNames(), this);
        search->setCompleter(searchCompleter);

        connect(search, &QLineEdit::returnPressed, this, [this] {
            quint32 id = worker->getChessplayerID(search->text());
            if (id != -1) {
                curInd = id;
                loadPage();
            } else {
                showSearchError();
                search->clear();
            }
        });


}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}

inline void ChessplayersStatsWidget::loadPage() {
    loadBasicFields();
    loadAmountFields();
    loadGamesTables();
    loadOpeningsTables();
    loadStrongestOpponentsTable();
    loadOpeningsCharts();
}

void ChessplayersStatsWidget::loadBasicFields() {
    // auto map = worker->getChessplayer(curInd);
    // rating->setValue(map["elo_rating"].toInt());
    // birthYear->setValue(map["birth_year"].toInt());
    // name->setText(map["name"]);
}

void ChessplayersStatsWidget::loadColorAmountFields() {
    amountWhite->setValue(worker->getChessplayerGamesAmount(curInd, "white"));
    amountBlack->setValue(worker->getChessplayerGamesAmount(curInd, "black"));

    winsWhite->setValue(worker->getChessplayerWins(curInd, "white"));
    winsBlack->setValue(worker->getChessplayerWins(curInd, "black"));

    losesWhite->setValue(worker->getChessplayerLoses(curInd, "white"));
    losesBlack->setValue(worker->getChessplayerLoses(curInd, "black"));
}

inline void ChessplayersStatsWidget::loadAmountFields() {
    loadColorAmountFields();

    amount->setValue(amountBlack->value() + amountWhite->value());
    loses->setValue(losesBlack->value() + losesWhite->value());
    wins->setValue(winsWhite->value() + winsBlack->value());
    draws->setValue(amount->value() - wins->value() - loses->value());
    drawsBlack->setValue(amountBlack->value() - winsBlack->value() - losesBlack->value());
    drawsWhite->setValue(amountWhite->value() - winsWhite->value() - losesWhite->value());
}

inline void ChessplayersStatsWidget::loadGamesTables() {
    gamesWhite->setModel(worker->getChessplayerGames(curInd, "white"));
    gamesBlack->setModel(worker->getChessplayerGames(curInd, "black"));

    resizeTableView(gamesWhite);
    resizeTableView(gamesBlack);

    gamesWhite->show();
    gamesBlack->show();
}

inline void ChessplayersStatsWidget::loadOpeningsTables() {
    openingsWhite->setModel(worker->getChessplayerOpenings(curInd, "white"));
    openingsBlack->setModel(worker->getChessplayerOpenings(curInd, "black"));

    resizeTableView(openingsWhite);
    resizeTableView(openingsBlack);

    openingsBlack->show();
    openingsWhite->show();
}
void ChessplayersStatsWidget::loadStrongestOpponentsTable() {
    strongestOponents->setModel(worker->getChessplayerStrongestOpponents(curInd));
    resizeTableView(strongestOponents);
    strongestOponents->show();
}
void ChessplayersStatsWidget::loadColorOpeningsChart(QString color) {
    auto pairs = worker->getChessplayerOpeningCounts(curInd, color);

    QBarSeries *series = new QBarSeries();
    quint32 maxAmount = 0;
    for (auto &i : pairs) {
        maxAmount = std::max(maxAmount, i.second);
        QBarSet *set = new QBarSet(i.first);
        *set << i.second;
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

