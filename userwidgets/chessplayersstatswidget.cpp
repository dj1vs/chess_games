#include "chessplayersstatswidget.h"
ChessplayersStatsWidget::ChessplayersStatsWidget(QWidget *parent):
    QWidget{parent} {
        search = new QLineEdit();
        name = new QLineEdit();

        gamesWhite = new QTableView();
        gamesBlack = new QTableView();
        openingsWhite = new QTableView();
        openingsBlack = new QTableView();
        strongestOponents = new QTableView();

        rating = new QSpinBox();
        birthYear = new QSpinBox();
        amount = new QSpinBox();
        wins = new QSpinBox();
        loses = new QSpinBox();
        draws = new QSpinBox();
        amountWhite = new QSpinBox();
        winsWhite = new QSpinBox();
        losesWhite = new QSpinBox();
        drawsWhite = new QSpinBox();
        amountBlack = new QSpinBox();
        winsBlack = new QSpinBox();
        losesBlack = new QSpinBox();
        drawsBlack = new QSpinBox();
        
        
        whiteOpeningsGraph = new QChartView();
        blackOpeningsGraph = new QChartView();
        

        layout = new QGridLayout();
        layout->addWidget(new QLabel("Search chessplayers by name:"), 0, 0, 1, 1);
        layout->addWidget(search, 0, 1, 1, 1);
        layout->addWidget(new QLabel("Name:"), 1, 0, 1, 1);
        layout->addWidget(new QLabel("ELO Rating:"), 2, 0, 1, 1);
        layout->addWidget(name, 2, 1, 1, 1);
        layout->addWidget(new QLabel("Birth year:"), 2, 2, 1, 1);
        layout->addWidget(birthYear, 2, 3, 1, 1);
        layout->addWidget(new QLabel("Games amount:"), 3, 0, 1, 1);
        layout->addWidget(amount, 3, 1, 1, 1);
        layout->addWidget(new QLabel("Wins amount:"), 4, 0, 1, 1);
        layout->addWidget(wins, 4, 1, 1, 1);
        layout->addWidget(new QLabel("Loses amount:"), 4, 2, 1, 1);
        layout->addWidget(loses, 4, 3, 1, 1);
        layout->addWidget(new QLabel("Draws amount:"), 5, 0, 1, 1);
        layout->addWidget(draws, 5, 1, 1, 1);
        layout->addWidget(new QLabel("Games as white:"), 6, 0, 1, 1);
        layout->addWidget(gamesWhite, 6, 1, 1, 1);
        layout->addWidget(new QLabel("Games amount as white:"), 7, 0, 1, 1);
        layout->addWidget(amountWhite, 7, 1, 1, 1);
        layout->addWidget(new QLabel("Wins as white:"), 8, 0, 1, 1);
        layout->addWidget(winsWhite, 8, 1, 1, 1);
        layout->addWidget(new QLabel("Loses as white:"), 8, 2, 1, 1);
        layout->addWidget(losesWhite, 8, 3, 1, 1);
        layout->addWidget(new QLabel("Draws as white:"), 9, 0, 1, 1);
        layout->addWidget(drawsWhite, 9, 1, 1, 1);
        layout->addWidget(new QLabel("Games as black:"), 10, 0, 1, 1);
        layout->addWidget(gamesBlack, 10, 1, 1, 1);
        layout->addWidget(new QLabel("Games amount as black:"),11, 0, 1, 1);
        layout->addWidget(amountBlack, 11, 1, 1, 1);
        layout->addWidget(new QLabel("Wins as black:"), 12, 0, 1, 1);
        layout->addWidget(winsBlack, 12, 1, 1, 1);
        layout->addWidget(new QLabel("Loses as black:"), 12, 2, 1, 1);
        layout->addWidget(losesBlack, 12, 3, 1, 1);
        layout->addWidget(new QLabel("Draws as black:"), 13, 0, 1, 1);
        layout->addWidget(drawsBlack, 13, 1, 1, 1);
        layout->addWidget(new QLabel("Opnenings as white:"), 14, 0, 1, 1);
        layout->addWidget(openingsWhite, 14, 1, 1, 1);
        layout->addWidget(new QLabel("Openings as black:"), 15, 0, 1, 1);
        layout->addWidget(openingsBlack, 15, 1, 1, 1);
        layout->addWidget(whiteOpeningsGraph, 16, 0, 1, 1);
        layout->addWidget(blackOpeningsGraph, 17, 0, 1, 1);
        layout->addWidget(new QLabel("Strongest opponents:"), 18, 0, 1, 1);
        layout->addWidget(strongestOponents, 18, 1, 1, 1);

        layout->setSpacing(3);

        setLayout(layout);
}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}
