#include "adminwidget.h"
AdminWidget::AdminWidget(QWidget *parent):
    QWidget{parent} {
    title = new QLabel("Admin menu");
    chessplayers = new QPushButton("Chessplayers");
    openings = new QPushButton("Openings");
    tournaments = new QPushButton("Tournaments");
    places = new QPushButton("Places");
    judges = new QPushButton("Judges");
    games = new QPushButton("Chess games");
    back = new QPushButton("Go back");

    layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(chessplayers);
    layout->addWidget(openings);
    layout->addWidget(tournaments);
    layout->addWidget(places);
    layout->addWidget(judges);
    layout->addWidget(games);
    layout->addWidget(back);

    setLayout(layout);

}

AdminWidget::~AdminWidget() {
    
}