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

    formHeader = new FormHeader();
    formHeader->setTitle("Openings statistics");

    pageLayout = new QGridLayout();
    pageLayout->addWidget(new QLabel("Search:"), 1, 0, 1, 1);
    pageLayout->addWidget(search, 1, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Name:"), 2, 0, 1, 1);
    pageLayout->addWidget(name, 2, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Alternative names:"), 3, 0, 1, 1);
    pageLayout->addWidget(altName, 3, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Group:"), 4, 0, 1, 1);
    pageLayout->addWidget(group, 4, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Moves:"), 5, 0, 1, 1);
    pageLayout->addWidget(moves, 5, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Named after:"), 6, 0, 1, 1);
    pageLayout->addWidget(namedAfter, 6, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Games amount:"), 7, 0, 1, 1);
    pageLayout->addWidget(amount, 7, 1, 1, 1);
    pageLayout->addWidget(new QLabel("White wins:"), 8, 0, 1, 1);
    pageLayout->addWidget(whiteWins, 8, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Black wins:"), 9, 0, 1, 1);
    pageLayout->addWidget(amount,9, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Draws:"),10, 0, 1, 1);
    pageLayout->addWidget(amount, 10, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Probability:"), 11, 0, 1, 1);
    pageLayout->addWidget(probability, 11, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Chessplayers which played as white:"), 12, 0, 1, 1);
    pageLayout->addWidget(chessplayersWhite, 12, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Chessplayers which played as black:"), 13, 0, 1, 1);
    pageLayout->addWidget(chessplayersBlack, 13, 1, 1, 1);
    pageLayout->addWidget(chartView, 14, 0, 1, 1);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);
    setLayout(mainLayout);
}

OpeningsStatsWidget::~OpeningsStatsWidget() {
    
}
