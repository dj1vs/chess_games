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
    formHeader->setTitle("Статистика по дебютам");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Поиск по названию"));
    layout->addWidget(search);
    layout->addWidget(new QLabel("Название"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Альтернативные названия"));
    layout->addWidget(altName);
    layout->addWidget(new QLabel("Группа"));
    layout->addWidget(group);
    layout->addWidget(new QLabel("Ходы"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Названо в честь"));
    layout->addWidget(namedAfter);
    layout->addWidget(new QLabel("Сыграно игр"));
    layout->addWidget(amount);
    layout->addWidget(new QLabel("Побед за белых"));
    layout->addWidget(whiteWins);
    layout->addWidget(new QLabel("Побед за чёрных"));
    layout->addWidget(blackWins);
    layout->addWidget(new QLabel("Ничьих"));
    layout->addWidget(draws);
    layout->addWidget(new QLabel("Вероятность выпадания"));
    layout->addWidget(probability);
    layout->addWidget(new QLabel("Шахматисты, игравшие дебют за белых"));
    layout->addWidget(chessplayersWhite);
    layout->addWidget(new QLabel("Шахматисты, игравшие дебют за чёрных"));
    layout->addWidget(chessplayersBlack);
    layout->addWidget(chartView);


    connectFormHeader();
    connectWorker();
    emit getOpenings();

    loadPage();

    connect(search, &QLineEdit::returnPressed, this, [this] {
        emit getSearchID(search->text());
    });
}

void OpeningsStatsWidget::loadGamesWithOpeningAmount(quint32 amount) {
    (this->amount)->setValue(amount);
}
void OpeningsStatsWidget::loadWhiteWinsWithOpeningAmount(quint32 amount) {
    whiteWins->setValue(amount);
}
void OpeningsStatsWidget::loadBlackWinsWithOpeningAmount(quint32 amount) {
    blackWins->setValue(amount);
    emit getGamesAmount();
}
void OpeningsStatsWidget::loadGamesAmount(quint32 games) {
    probability->setText(QString::number((static_cast<double>(amount->value())/static_cast<double>(games)) * 100) + '%');
    loadChart();
    loadPage();
}

void OpeningsStatsWidget::processSearchID(QString id) {
        if (id != "") {
            curInd = idList.indexOf(id) + 1; 
            id = idList[curInd - 1];
            loadPage();
        } else {
            showSearchError();
            search->clear();
        }
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

void OpeningsStatsWidget::processOpenings(QStringList openings) {
    searchCompleter = new QCompleter(openings);
    search->setCompleter(searchCompleter);
}

void OpeningsStatsWidget::loadOpeningPlayers(DTable table, QString color) {
    QTableView *view = (color == "white" ? chessplayersWhite : chessplayersBlack);
    view->setModel(DTableToModel(table,\
        {"Шахматист", "Рейтинг", "Партий сыграно"}));
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

    connect(this, &OpeningsStatsWidget::getSearchID, worker, &SQLWorker::getOpeningID);
    connect(worker, &SQLWorker::openingIDReady, this, &OpeningsStatsWidget::processSearchID);
    connect(this, &OpeningsStatsWidget::getOpenings, worker, &SQLWorker::getAllOpeningsNames);
    connect(worker, &SQLWorker::allOpeningsNamesReady, this, &OpeningsStatsWidget::processOpenings);

    connect(this, &OpeningsStatsWidget::getGamesWithOpeningAmount, worker, &SQLWorker::getGamesWithOpeningAmount);
    connect(worker, &SQLWorker::gamesWithOpeningAmountReady, this, &OpeningsStatsWidget::loadGamesWithOpeningAmount);
    connect(this, &OpeningsStatsWidget::getWhiteWinsWithOpeningAmount, worker, &SQLWorker::getWhiteWinsWithOpeningAmount);
    connect(worker, &SQLWorker::whiteWinsWithOpeningAmountReady, this, &OpeningsStatsWidget::loadWhiteWinsWithOpeningAmount);
    connect(this, &OpeningsStatsWidget::getBlackWinsWithOpeningAmount, worker, &SQLWorker::getBlackWinsWithOpeningAmount);
    connect(worker, &SQLWorker::blackWinsWithOpeningAmountReady, this, &OpeningsStatsWidget::loadBlackWinsWithOpeningAmount);
    connect(this, &OpeningsStatsWidget::getGamesAmount, worker, &SQLWorker::getGamesAmount);
    connect(worker, &SQLWorker::gamesAmountReady, this, &OpeningsStatsWidget::loadGamesAmount);
    


    connect(this, &OpeningsStatsWidget::setMaxInd, this, &OpeningsStatsWidget::loadMaxInd);

}

void OpeningsStatsWidget::loadIds(QStringList ids) {
    idList = ids;

    if (curInd > ids.size()) {
        curInd = ids.size();
    }

    id = idList[curInd - 1];



    emit getOpening(id);
    emit getOpeningPlayers(id, "white");
    emit getOpeningPlayers(id, "black");
}

void OpeningsStatsWidget::loadAmounts() {
    emit getGamesWithOpeningAmount(id);
    emit getWhiteWinsWithOpeningAmount(id);
    emit getBlackWinsWithOpeningAmount(id);

}

void OpeningsStatsWidget::loadChart() {
    draws->setValue(amount->value() - blackWins->value() - whiteWins->value());

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    series->append("Побед за белых", whiteWins->value());
    series->append("Побед за чёрных", blackWins->value());
    series->append("Ничьих", draws->value());

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Исходы партий, в которых встретился дебют:");
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
    chartView->setMinimumHeight(300);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void OpeningsStatsWidget::loadPage() {
    emit getAllOpeningsIds();

    loadAmounts();
}