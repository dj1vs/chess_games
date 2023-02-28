#include "userwidget.h"
UserWidget::UserWidget(QWidget *parent) :
    QWidget{parent} {
    title = new QLabel("User menu");

    chessplayersStats = new QPushButton("Chessplayers stats");
    openingsStats = new QPushButton("Openings stats");
    tournamentsStats = new QPushButton("Tournaments stats");
    gamesList = new QPushButton("Chess games list");
    backButton = new QPushButton("Go back");

    layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(chessplayersStats);
    layout->addWidget(openingsStats);
    layout->addWidget(tournamentsStats);
    layout->addWidget(gamesList);
    layout->addWidget(backButton);

    setLayout(layout);

    connect(chessplayersStats, &QPushButton::clicked, this, [this] {emit chessplayers();});
    connect(openingsStats, &QPushButton::clicked, this, [this] {emit openings();});
    connect(tournamentsStats, &QPushButton::clicked, this, [this] {emit tournaments();});
    connect(gamesList, &QPushButton::clicked, this, [this] {emit games();});
    connect(backButton, &QPushButton::clicked, this, [this] {emit back();});
}

UserWidget::~UserWidget() {

}