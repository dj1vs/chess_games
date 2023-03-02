#include "adminwidget.h"
AdminWidget::AdminWidget(QWidget *parent):
    QWidget{parent} {
    title = new QLabel("Admin menu");
    chessplayersButton = new QPushButton("Chessplayers");
    openingsButton = new QPushButton("Openings");
    tournamentsButton = new QPushButton("Tournaments");
    placesButton = new QPushButton("Places");
    judgesButton = new QPushButton("Judges");
    gamesButton = new QPushButton("Chess games");
    backButton = new QPushButton("Go back");

    layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(chessplayersButton);
    layout->addWidget(openingsButton);
    layout->addWidget(tournamentsButton);
    layout->addWidget(placesButton);
    layout->addWidget(judgesButton);
    layout->addWidget(gamesButton);
    layout->addWidget(backButton);

    connect(chessplayersButton, &QPushButton::clicked, this, [this] {emit chessplayers();});
    connect(openingsButton, &QPushButton::clicked, this, [this] {emit openings();});
    connect(tournamentsButton, &QPushButton::clicked, this, [this] {emit tournaments();});
    connect(placesButton, &QPushButton::clicked, this, [this] {emit places();});
    connect(judgesButton, &QPushButton::clicked, this, [this] {emit judges();});
    connect(gamesButton, &QPushButton::clicked, this, [this] {emit games();});
    connect(backButton, &QPushButton::clicked, this, [this] {emit back();});


    setLayout(layout);

}

AdminWidget::~AdminWidget() {
    
}