#include "tournamentsstatswidget.h"
TournamentsStatsWidget::TournamentsStatsWidget(QWidget *parent):
    QWidget{parent} {
        formHeader = new FormHeader();
        formHeader->setTitle("Tournaments statistics");

        pageLayout = new QGridLayout();

        search = new QLineEdit();
        tournamentName = new QLineEdit();
        winnersName = new QLineEdit();
        judgesName = new QLineEdit();
        country = new QLineEdit();
        city = new QLineEdit();
        
        ratingRestriction = new QComboBox();
        gamesAmount = new QComboBox();

        results = new QChartView;

        strongestPlayersBlack = new QTableView;
        strongestPlayersWhite = new QTableView;

        pageLayout->addWidget(new QLabel("Search:"), 0, 0, 1, 1);
        pageLayout->addWidget(search, 0, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Tournament name:"), 1, 0, 1, 1);
        pageLayout->addWidget(tournamentName, 1, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Rating restriction:"), 2, 0, 1, 1);
        pageLayout->addWidget(ratingRestriction, 2, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Winner:"), 3, 0, 1, 1);
        pageLayout->addWidget(winnersName, 3, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Judge:"), 4, 0, 1, 1);
        pageLayout->addWidget(judgesName, 4, 1, 1, 1);
        pageLayout->addWidget(new QLabel("Tournament location:"), 5, 0, 1, 4);
        pageLayout->addWidget(new QLabel("Country:"), 6, 0, 1, 1);
        pageLayout->addWidget(country, 6, 1, 1, 1);
        pageLayout->addWidget(new QLabel("City:"), 6, 2, 1, 1);
        pageLayout->addWidget(city, 6, 3, 1, 1);
        pageLayout->addWidget(new QLabel("Games played:"), 7, 0, 1, 1);
        pageLayout->addWidget(gamesAmount, 7, 1, 1, 1);
        pageLayout->addWidget(results, 8, 0, 1, 1);
        pageLayout->addWidget(new QLabel("Strongest players as white:"), 9, 0, 1, 1);
        pageLayout->addWidget(strongestPlayersWhite, 9, 1, 1, 2);
        pageLayout->addWidget(new QLabel("Strongest players as black:"), 10, 0, 1, 1);
        pageLayout->addWidget(strongestPlayersBlack, 10, 1, 1, 2);
        

        mainLayout = new QVBoxLayout();
        mainLayout->addWidget(formHeader);
        mainLayout->addLayout(pageLayout);


        setLayout(mainLayout);
}

TournamentsStatsWidget::~TournamentsStatsWidget() {
    
}