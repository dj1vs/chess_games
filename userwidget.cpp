#include "userwidget.h"
UserWidget::UserWidget(QWidget *parent) :
    QWidget{parent} {
    title = new QLabel("User menu");

    chessplayersStats = new QPushButton("Chessplayers stats");
    openingsStats = new QPushButton("Openings stats");
    tournamentsStats = new QPushButton("Tournaments stats");
    gamesList = new QPushButton("Chess games list");
    back = new QPushButton("Go back");

    layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(chessplayersStats);
    layout->addWidget(openingsStats);
    layout->addWidget(tournamentsStats);
    layout->addWidget(gamesList);
    layout->addWidget(back);

    setLayout(layout);
}

UserWidget::~UserWidget() {

}