#include "openingsstatswidget.h"
OpeningsStatsWidget::OpeningsStatsWidget(QWidget *parent):
    QWidget{parent} {
    search = new QLineEdit();
    name = new QLineEdit();
    altName = new QLineEdit();
    group = new QLineEdit();
    moves = new QLineEdit();
    namedAfter = new QLineEdit();
    probability = new QLineEdit();
    amount = new QComboBox();
    whiteWins = new QComboBox();
    blackWins = new QComboBox();
    draws = new QComboBox();
    chessplayersBlack = new QTableView();
    chessplayersWhite = new QTableView();
    chartView = new QChartView();

    goBack = new QPushButton();
    prev = new QPushButton();
    next = new QPushButton();
    print = new QPushButton();

    layout = new QGridLayout();
    layout->addWidget(goBack, 0, 0, 1, 1);
    layout->addWidget(prev,0,1,1,1);
    layout->addWidget(next, 0, 2, 1, 1);
    layout->addWidget(print, 0, 3, 1, 1);
    layout->addWidget(new QLabel("Search:"), 1, 0, 1, 1);
    layout->addWidget(search, 1, 1, 1, 1);
    layout->addWidget(new QLabel("Name:"), 2, 0, 1, 1);
    layout->addWidget(name, 2, 1, 1, 1);
    layout->addWidget(new QLabel("Alternative names:"), 3, 0, 1, 1);
    layout->addWidget(altName, 3, 1, 1, 1);
    layout->addWidget(new QLabel("Group:"), 4, 0, 1, 1);
    layout->addWidget(group, 4, 1, 1, 1);
    layout->addWidget(new QLabel("Moves:"), 5, 0, 1, 1);
    layout->addWidget(moves, 5, 1, 1, 1);
    layout->addWidget(new QLabel("Named after:"), 6, 0, 1, 1);
    layout->addWidget(namedAfter, 6, 1, 1, 1);
    layout->addWidget(new QLabel("Games amount:"), 7, 0, 1, 1);
    layout->addWidget(amount, 7, 1, 1, 1);
    layout->addWidget(new QLabel("White wins:"), 8, 0, 1, 1);
    layout->addWidget(whiteWins, 8, 1, 1, 1);
    layout->addWidget(new QLabel("Black wins:"), 9, 0, 1, 1);
    layout->addWidget(amount,9, 1, 1, 1);
    layout->addWidget(new QLabel("Draws:"),10, 0, 1, 1);
    layout->addWidget(amount, 10, 1, 1, 1);
    layout->addWidget(new QLabel("Probability:"), 11, 0, 1, 1);
    layout->addWidget(probability, 11, 1, 1, 1);
    layout->addWidget(new QLabel("Chessplayers which played as white:"), 12, 0, 1, 1);
    layout->addWidget(chessplayersWhite, 12, 1, 1, 1);
    layout->addWidget(new QLabel("Chessplayers which played as black:"), 13, 0, 1, 1);
    layout->addWidget(chessplayersBlack, 13, 1, 1, 1);
    layout->addWidget(chartView, 14, 0, 1, 1);

    setLayout(layout);
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}
