#include "chessplayersstatswidget.h"

#include <QApplication>
#include <QDebug>
#include <QValueAxis>
#include <QBarCategoryAxis>

ChessplayersStatsWidget::ChessplayersStatsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent}{

        worker = w;

        formHeader = new FormHeader();
        formHeader->setTitle("Статистика по шахматистам");

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
        layout->addWidget(new QLabel("Поиск по имени"));
        layout->addWidget(search);
        layout->addWidget(new QLabel("Имя"));
        layout->addWidget(name);
        layout->addWidget(new QLabel("Рейтинг"));
        layout->addWidget(rating);
        layout->addWidget(new QLabel("Год рождения"));
        layout->addWidget(birthYear);
        layout->addWidget(new QLabel("Сыграно игр"));
        layout->addWidget(amount);
        layout->addWidget(new QLabel("Побед"));
        layout->addWidget(wins);
        layout->addWidget(new QLabel("Поражений"));
        layout->addWidget(loses);
        layout->addWidget(new QLabel("Ничьих"));
        layout->addWidget(draws);
        layout->addWidget(new QLabel("За белых"));
        layout->addWidget(gamesWhite);
        layout->addWidget(new QLabel("Сыграно игр за белых"));
        layout->addWidget(amountWhite);
        layout->addWidget(new QLabel("Побед за белых"));
        layout->addWidget(winsWhite);
        layout->addWidget(new QLabel("Поражений за белых"));
        layout->addWidget(losesWhite);
        layout->addWidget(new QLabel("Ничьих за белых"));
        layout->addWidget(drawsWhite);
        layout->addWidget(new QLabel("За чёрных"));
        layout->addWidget(gamesBlack);
        layout->addWidget(new QLabel("Сыграно игр за чёрных"));
        layout->addWidget(amountBlack);
        layout->addWidget(new QLabel("Побед за чёрных"));
        layout->addWidget(winsBlack);
        layout->addWidget(new QLabel("Поражений за чёрных"));
        layout->addWidget(losesBlack);
        layout->addWidget(new QLabel("Ничьих за чёрных"));
        layout->addWidget(drawsBlack);
        layout->addWidget(new QLabel("Opnenings as white:"));
        layout->addWidget(openingsWhite);
        layout->addWidget(new QLabel("Openings as black:"));
        layout->addWidget(openingsBlack);
        layout->addWidget(whiteOpeningsGraph);
        layout->addWidget(blackOpeningsGraph);
        layout->addWidget(new QLabel("Сильнейшие соперники"));
        layout->addWidget(strongestOponents);

        connectFormHeader();
        connectWorker();
        connect(this, &ChessplayersStatsWidget::colorAmountsLoaded, this, &ChessplayersStatsWidget::loadAmountFields);

        loadPage();

        emit getChessplayers();

        connect(search, &QLineEdit::returnPressed, this, [this] {
            emit getSearchID(search->text());
        });


}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}

void ChessplayersStatsWidget::loadChessplayers(QStringList names) {
    searchCompleter = new QCompleter(names);
    search->setCompleter(searchCompleter);
}
void ChessplayersStatsWidget::processSearchID(quint32 ind) {
        if (ind != -1) {
            curInd = ind;
            loadPage();
        } else {
            showSearchError();
            search->clear();
        }
}

void ChessplayersStatsWidget::loadChessplayerOpeningCounts(DMap map, QString color) {
    QBarSeries *series = new QBarSeries();
    quint32 maxAmount = 0;
    for (auto &i : map.toStdMap()) {
        maxAmount = std::max(static_cast<int>(maxAmount), i.second.toInt());
        QBarSet *set = new QBarSet(i.first);
        *set << i.second.toInt();
        series->append(set);
    }

    QChart *chart = new QChart();
    QString colorRus = (color == "white" ? "белых" : "чёрных");
    chart->setTitle("Дебюты за " + colorRus);
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
void ChessplayersStatsWidget::loadChessplayer(DMap map) {
    rating->setValue(map["elo_rating"].toInt());
    birthYear->setValue(map["birth_year"].toInt());
    name->setText(map["name"].toString());
}

void ChessplayersStatsWidget::loadChessplayerGames(DTable table, QString color) {
    QTableView *view = (color == "white" ? gamesWhite : gamesBlack);

    view->setModel(DTableToModel(table,\
        {"Дата", "Белые", "Чёрные", "Контроль времени", "Формат", "Исход", "Ходы"}));
    resizeTableView(view);
    view->show();
}
void ChessplayersStatsWidget::loadChessplayerOpenings(DTable table, QString color) {
    QTableView *view = (color == "white" ? openingsWhite : openingsBlack);

    view->setModel(DTableToModel(table,\
        {"Дебют", "Количество партий"}));
    resizeTableView(view);
    view->show();
}
void ChessplayersStatsWidget::loadChessplayerStrongestOpponents(DTable table) {
    strongestOponents->setModel(DTableToModel(table,\
        {"Шахматист", "Рейтинг"}));
    resizeTableView(strongestOponents);
    strongestOponents->show();
}

void ChessplayersStatsWidget::connectWorker() {
    connect(this, &ChessplayersStatsWidget::getChessplayer, worker, &SQLWorker::getChessplayer);
    connect(worker, &SQLWorker::chessplayerReady, this, &ChessplayersStatsWidget::loadChessplayer);
    connect(this, &ChessplayersStatsWidget::getChessplayerGames, worker, &SQLWorker::getChessplayerGames);
    connect(worker, &SQLWorker::chessplayerGamesReady, this, &ChessplayersStatsWidget::loadChessplayerGames);
    connect(this, &ChessplayersStatsWidget::getChessplayerOpenings, worker, &SQLWorker::getChessplayerOpenings);
    connect(worker, &SQLWorker::chessplayerOpeningsReady, this, &ChessplayersStatsWidget::loadChessplayerOpenings);
    connect(this, &ChessplayersStatsWidget::getChessplayerStrongestOpponents, worker, &SQLWorker::getChessplayerStrongestOpponents);
    connect(worker, &SQLWorker::chessplayerStrongestOpponentsReady, this, &ChessplayersStatsWidget::loadChessplayerStrongestOpponents);
    connect(this, &ChessplayersStatsWidget::getChessplayerOpeningCounts, worker, &SQLWorker::getChessplayerOpeningCounts);
    connect(worker, &SQLWorker::chessplayerOpeningCountsReady, this, &ChessplayersStatsWidget::loadChessplayerOpeningCounts);

    connect(this, &ChessplayersStatsWidget::getAmount, worker, &SQLWorker::getChessplayerGamesAmount);
    connect(worker, &SQLWorker::chessplayerGamesAmountReady,this, &ChessplayersStatsWidget::loadAmount);
    connect(this, &ChessplayersStatsWidget::getWins, worker, &SQLWorker::getChessplayerWins);
    connect(worker, &SQLWorker::chessplayerWinsReady,this, &ChessplayersStatsWidget::loadWins);
    connect(this, &ChessplayersStatsWidget::getLoses, worker, &SQLWorker::getChessplayerLoses);
    connect(worker, &SQLWorker::chessplayerLosesReady,this, &ChessplayersStatsWidget::loadLoses);

    connect(this, &ChessplayersStatsWidget::getChessplayers, worker, &SQLWorker::getAllChessplayersNames);
    connect(worker, &SQLWorker::allChessplayersNamesReady, this, &ChessplayersStatsWidget::loadChessplayers);

    connect(this, &ChessplayersStatsWidget::getSearchID, worker, &SQLWorker::getChessplayerID);
    connect(worker, &SQLWorker::chessplayerIDReady, this, &ChessplayersStatsWidget::processSearchID);


    connect(this, &ChessplayersStatsWidget::setMaxInd, worker, &SQLWorker::getMaxChessplayerID);
    connect(worker, &SQLWorker::maxChessplayerIDReady, this, &ChessplayersStatsWidget::loadMaxInd);
}

void ChessplayersStatsWidget::loadPage() {
    emit getChessplayer(curInd);
    emit getChessplayerGames(curInd, "white");
    emit getChessplayerGames(curInd, "black");

    emit getChessplayerOpenings(curInd, "white");
    emit getChessplayerOpenings(curInd, "black");

    emit getChessplayerStrongestOpponents(curInd);

    emit getChessplayerOpeningCounts(curInd, "white");
    emit getChessplayerOpeningCounts(curInd, "black");

    loadColorAmountFields();
}

void ChessplayersStatsWidget::loadAmount(quint32 amount, QString color) {
    (color == "white" ? amountWhite : amountBlack)->setValue(amount);
}
void ChessplayersStatsWidget::loadWins(quint32 amount, QString color) {
    (color == "white" ? winsWhite : winsBlack)->setValue(amount);
}
void ChessplayersStatsWidget::loadLoses(quint32 amount, QString color) {
    (color == "white" ? losesWhite : losesBlack)->setValue(amount);
    if (color == "black") {
        emit colorAmountsLoaded();
    }
}

void ChessplayersStatsWidget::loadColorAmountFields() {
    emit getAmount(curInd, "white");
    emit getAmount(curInd, "black");

    emit getWins(curInd, "white");
    emit getWins(curInd, "black");

    emit getLoses(curInd, "white");
    emit getLoses(curInd, "black");
}

inline void ChessplayersStatsWidget::loadAmountFields() {
    amount->setValue(amountBlack->value() + amountWhite->value());

    wins->setValue(winsWhite->value() + winsBlack->value());
    loses->setValue(losesWhite->value() + losesBlack->value());
    draws->setValue(amount->value() - wins->value() - loses->value());

    drawsBlack->setValue(amountBlack->value() - winsBlack->value() - losesBlack->value());
    drawsWhite->setValue(amountWhite->value() - winsWhite->value() - losesWhite->value());
}