#include "userwidget.h"
UserWidget::UserWidget(QWidget *parent) :
    QWidget{parent} {
    title = new QLabel("Меню пользователя");
    title->setFont(QFont("Consolas", 20, QFont::Bold));

    chessplayersStats = new QPushButton("Статистика по шахматистам");
    openingsStats = new QPushButton("Статистика по дебютам");
    tournamentsStats = new QPushButton("Статистика по турнирам");
    gamesList = new QPushButton("Список шахматных партий");
    backButton = new QPushButton("Обратно");

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