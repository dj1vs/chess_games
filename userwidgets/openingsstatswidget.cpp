#include "openingsstatswidget.h"

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
    layout->addWidget(chartView);

    initWorker();

    loadPage();

    connectFormHeader();

    searchCompleter = new QCompleter(openings, this);
    search->setCompleter(searchCompleter);
    connect(search, &QLineEdit::returnPressed, this, [this] {
        QString str = worker->getOpeningID(search->text());
        if (str != "") {
            curInd = idList.indexOf(str) + 1; 
            id = idList[curInd - 1];
            loadPage();
        } else {
            showSearchError();
            search->clear();
        }
    });
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}

void OpeningsStatsWidget::loadIds() {
    idList = worker->getAllOpeningdIds();

    id = idList[curInd - 1];
}
void OpeningsStatsWidget::loadBasicFields() {
    auto map = worker->getOpening(id);
    name->setText(map["name"]);
    group->setText(map["group"]);
    moves->setText(map["moves"]);
    namedAfter->setText(map["named_after"]);
    altName->setText(map["alt_names"]);
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

void OpeningsStatsWidget::loadTables() {
     chessplayersWhite->setModel(worker->getOpeningPlayers(id, "white"));
     resizeTableView(chessplayersWhite);
     chessplayersWhite->show();

     chessplayersBlack->setModel(worker->getOpeningPlayers(id, "black"));
     resizeTableView(chessplayersBlack);
     chessplayersBlack->show();
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
    loadOpenings();
    loadIds();
    loadBasicFields();
    loadAmounts();
    loadProbability();
    loadTables();
    loadChart();
}

void OpeningsStatsWidget::loadOpenings() {
    openings = worker->getAllOpeningsNames();
}