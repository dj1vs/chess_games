#include "tournamentswidget.h"
TournamentsWidget::TournamentsWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Tournaments");

    pageLayout = new QGridLayout;
    id = new QComboBox;
    name = new QLineEdit;
    ratingRestriction = new QComboBox;
    winner = new QLineEdit;
    city = new QLineEdit;
    country = new QLineEdit;
    judgeBox = new QGroupBox;
    playedGames = new QTableView;

    pageLayout->addWidget(new QLabel("ID"), 0, 0, 1, 1);
    pageLayout->addWidget(id, 0, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Tournaments name"), 1, 0, 1, 1);
    pageLayout->addWidget(id, 1, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Rating restriction"), 2, 0, 1, 1);
    pageLayout->addWidget(id, 2, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Winner"), 3, 0, 1, 1);
    pageLayout->addWidget(id, 3, 1, 1, 1);
    pageLayout->addWidget(new QLabel("City"), 4, 0, 1, 1);
    pageLayout->addWidget(id, 4, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Country"), 4, 2, 1, 1);
    pageLayout->addWidget(id, 4, 3, 1, 1);
    pageLayout->addWidget(judgeBox, 5, 0, 1, 1);
    pageLayout->addWidget(new QLabel("Games, played at a tournament:"), 6, 0, 1, 1);
    pageLayout->addWidget(playedGames, 6, 1, 1, 1);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);
}

TournamentsWidget::~TournamentsWidget() {
    
}