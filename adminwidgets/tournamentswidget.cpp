#include "tournamentswidget.h"

#include <QDebug>

TournamentsWidget::TournamentsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Tournaments");

    layout = new QVBoxLayout(this);
    id = new QSpinBox;
    name = new QLineEdit;
    ratingRestriction = new QSpinBox;
    winner = new QLineEdit;
    city = new QLineEdit;
    country = new QLineEdit;
    judge = new QLineEdit;
    playedGames = new QTableView;
    save = new QPushButton("Save");

    layout->addWidget(formHeader);

    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Tournaments name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Rating restriction"));
    layout->addWidget(ratingRestriction);
    layout->addWidget(new QLabel("Winner"));
    layout->addWidget(winner);
    layout->addWidget(new QLabel("City"));
    layout->addWidget(city);
    layout->addWidget(new QLabel("Country"));
    layout->addWidget(country);
    layout->addWidget(new QLabel("Judge"));
    layout->addWidget(judge);
    layout->addWidget(new QLabel("Games, played at a tournament:"));
    layout->addWidget(playedGames);
    layout->addWidget(save);

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});
    connectWorker();

    loadPage();
}

TournamentsWidget::~TournamentsWidget() {
    
}

void TournamentsWidget::loadTournamentGames(DTable table) {
    playedGames->setModel(DTableToModel(table,\
    {"Дата", "Формат", "Контроль времени", "Результат", "Белые", "Чёрные", "Ходы"}));
    resizeTableView(playedGames);
    playedGames->show();
}

void TournamentsWidget::loadTournament(DMap map) {
    id->setValue(curInd);

    name->setText(map["name"].toString());
    ratingRestriction->setValue(map["rating_restriction"].toInt());
    winner->setText(map["winner"].toString());
    city->setText(map["city"].toString());
    country->setText(map["country"].toString());
    judge->setText(map["judge"].toString());
}

void TournamentsWidget::connectWorker() {
    connect(this, &TournamentsWidget::getTournament, worker, &SQLWorker::getTournament);
    connect(worker, &SQLWorker::tournamentReady, this, &TournamentsWidget::loadTournament);
    connect(this, &TournamentsWidget::getTournamentGames, worker, &SQLWorker::getTournamentGames);
    connect(worker, &SQLWorker::tournamentGamesReady, this, &TournamentsWidget::loadTournamentGames);

    connect(this, &TournamentsWidget::setMaxInd, worker, &SQLWorker::getMaxTournamentID);
    connect(worker, &SQLWorker::maxTournamentIDReady, this, &TournamentsWidget::loadMaxInd);
}


void TournamentsWidget::loadPage() {
    loadBasics();
    loadTable();
}

void TournamentsWidget::loadBasics() {
    emit getTournament(curInd);
}

void TournamentsWidget::loadTable() {
    emit getTournamentGames(curInd);

}

void TournamentsWidget::saveChanges() {
    worker->setTournament({
        {"name", name->text()},
        {"rating_restriction", QString::number(ratingRestriction->value())},
        {"city", city->text()},
        {"country", country->text()},
        {"winner", winner->text()},
        {"judge", judge->text()},
        {"id", QString::number(curInd)}
    });

    showSaved();
}
