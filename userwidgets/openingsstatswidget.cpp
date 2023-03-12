#include "openingsstatswidget.h"

#include <QDebug>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QChartView>

OpeningsStatsWidget::OpeningsStatsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
    worker = w;

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
    layout->addWidget(chartView);


    connectFormHeader();
    connectWorker();

    loadPage();

    // searchCompleter = new QCompleter(openings, this);
    // search->setCompleter(searchCompleter);
    // connect(search, &QLineEdit::returnPressed, this, [this] {
    //     QString str = worker->getOpeningID(search->text());
    //     if (str != "") {
    //         curInd = idList.indexOf(str) + 1; 
    //         id = idList[curInd - 1];
    //         loadPage();
    //     } else {
    //         showSearchError();
    //         search->clear();
    //     }
    // });
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}
void OpeningsStatsWidget::loadOpening(const DMap &map) {
    name->setText(map["name"].toString());
    group->setText(map["group"].toString());
    moves->setText(map["moves"].toString());
    namedAfter->setText(map["named_after"].toString());
    altName->setText(map["alt_names"].toString());
}

void OpeningsStatsWidget::loadOpeningPlayers(DTable table, QString color) {
    QTableView *view = (color == "white" ? chessplayersWhite : chessplayersBlack);
    view->setModel(DTableToModel(table));
    resizeTableView(view);
    view->show();
}

void OpeningsStatsWidget::connectWorker() {
    connect(this, &OpeningsStatsWidget::getOpening, worker, &SQLWorker::getOpening);
    connect(worker, &SQLWorker::openingReady, this, &OpeningsStatsWidget::loadOpening);
    connect(this, &OpeningsStatsWidget::getAllOpeningsIds, worker, &SQLWorker::getAllOpeningsIds);
    connect(worker, &SQLWorker::allOpeningsIdsReady, this, &OpeningsStatsWidget::loadIds);
    connect(this, &OpeningsStatsWidget::getOpeningPlayers, worker, &SQLWorker::getOpeningPlayers);
    connect(worker, &SQLWorker::openingPlayersReady, this, &OpeningsStatsWidget::loadOpeningPlayers);

}

void OpeningsStatsWidget::loadIds(QStringList ids) {
    idList = ids;

    id = idList[curInd - 1];
    emit getOpening(id);
    emit getOpeningPlayers(id, "white");
    emit getOpeningPlayers(id, "black");
}

void OpeningsStatsWidget::loadAmounts() {
    amount->setValue(worker->getGamesWithOpeningAmount(id));
    whiteWins->setValue(worker->getWhiteWinsWithOpeningAmount(id));
    blackWins->setValue(worker->getBlackWinsWithOpeningAmount(id));
    draws->setValue(amount->value() - blackWins->value() - whiteWins->value());
}

void OpeningsStatsWidget::loadProbability() {
    quint32 gamesAmount = worker->getGamesAmount();
    probability->setText(QString::number((static_cast<double>(amount->value())/static_cast<double>(gamesAmount)) * 100) + '%');
}


void OpeningsStatsWidget::loadChart() {
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    series->append("White wins:", whiteWins->value());
    series->append("Black wins:", blackWins->value());
    series->append("Draws:", draws->value());

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Results with this opening:");
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
    chartView->setMinimumHeight(300);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void OpeningsStatsWidget::loadPage() {
    if (curInd == idList.size()) {
        --curInd;
    }
    // loadOpenings();
    // loadIds();
    emit getAllOpeningsIds();
    // loadAmounts();
    // loadProbability();
    // loadChart();
}

void OpeningsStatsWidget::loadOpenings() {
    openings = worker->getAllOpeningsNames();
}