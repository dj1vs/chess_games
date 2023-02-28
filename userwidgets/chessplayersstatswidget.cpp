#include "chessplayersstatswidget.h"
ChessplayersStatsWidget::ChessplayersStatsWidget(QWidget *parent):
    QWidget{parent} {
        search = new QLineEdit();
        QLineEdit *name;

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
        
        
        whiteOpeningsGraph = new QWidget();
        blackOpeningsGraph = new QWidget();
        

        layout = new QFormLayout();
        layout->addRow(tr("Search chessplayers by name:"), search);
        layout->addRow(tr("Name:"), name);
        layout->addRow(tr("ELO Rating:"), rating);
        layout->addRow(tr("Birth year:"), birthYear);
        layout->addRow(tr("Games amount:"), amount);
        layout->addRow(tr("Wins amount:"), wins);
        layout->addRow(tr("Loses amount:"), loses);
        layout->addRow(tr("Draws amount:"), draws);
        layout->addRow(tr("Games as white:"), gamesWhite);
        layout->addRow(tr("Games amount as white:"), amountWhite);
        layout->addRow(tr("Wins as white:"), winsWhite);
        layout->addRow(tr("Loses as white:"), losesWhite);
        layout->addRow(tr("Draws as white:"), drawsWhite);
        layout->addRow(tr("Games as black:"), gamesBlack);
        layout->addRow(tr("Wins as black:"), winsBlack);
        layout->addRow(tr("Loses as black:"), losesBlack);
        layout->addRow(tr("Draws as black:"), drawsBlack);
        layout->addRow(tr("Openings as white:"), openingsWhite);
        layout->addRow(tr("Openings as black:"), openingsBlack);
        layout->addRow(whiteOpeningsGraph, blackOpeningsGraph);
        layout->addRow(tr("Stronges opponents:"), strongestOponents);

        setLayout(layout);
}

ChessplayersStatsWidget::~ChessplayersStatsWidget() {
    
}