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


    loadPage();

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});
}

TournamentsWidget::~TournamentsWidget() {
    
}

void TournamentsWidget::loadPage() {
    loadBasics();
    loadTable();
}

void TournamentsWidget::loadBasics() {
    // id->setValue(curInd);
    // auto map = worker->getTournament(curInd);
    // name->setText(map["name"]);
    // ratingRestriction->setValue(map["rating_restriction"].toInt());
    // winner->setText(map["winner"]);
    // city->setText(map["city"]);
    // country->setText(map["country"]);
    // judge->setText(map["judge"]);
}

void TournamentsWidget::loadTable() {
    playedGames->setModel(worker->getTournamentGames(curInd));
    resizeTableView(playedGames);
    playedGames->show();

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
