#include "chessgameslistwidget.h"
ChessGamesListWidget::ChessGamesListWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader();
    formHeader->setTitle("Chess games list");

    pageLayout = new QGridLayout();

    date = new QLineEdit();
    whiteName = new QLineEdit();
    blackName = new QLineEdit();
    format = new QLineEdit();
    timeControl = new QLineEdit();
    opening = new QLineEdit();

    whiteRating = new QComboBox;
    blackRating = new QComboBox;

    moves = new QTextBrowser();

    ratingDifs = new QTableView;

    pageLayout->addWidget(new QLabel("Date:"), 0, 0, 1, 1);
    pageLayout->addWidget(date, 0, 1, 1, 1);
    pageLayout->addWidget(new QLabel("White:"), 1, 0, 1, 1);
    pageLayout->addWidget(new QLabel("Name:"), 2, 0, 1, 1);
    pageLayout->addWidget(whiteName, 2, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Rating:"), 2, 2, 1, 1);
    pageLayout->addWidget(whiteRating, 2, 3, 1, 1);
    pageLayout->addWidget(new QLabel("Black:"), 3, 0, 1, 1);
    pageLayout->addWidget(new QLabel("Name:"), 4, 0, 1, 1);
    pageLayout->addWidget(blackName, 4, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Rating:"), 4, 2, 1, 1);
    pageLayout->addWidget(blackRating, 4, 3, 1, 1);
    pageLayout->addWidget(new QLabel("Format:"), 5, 0, 1, 1);
    pageLayout->addWidget(format, 5, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Time control:"), 6, 0, 1, 1);
    pageLayout->addWidget(timeControl, 6, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Played opening:"), 7, 0, 1, 1);
    pageLayout->addWidget(opening, 7, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Moves:"), 8, 0, 1, 1);
    pageLayout->addWidget(moves, 8, 1, 1, 1);
    pageLayout->addWidget(new QLabel("Rating differences in games:"), 9, 0, 1, 1);
    pageLayout->addWidget(ratingDifs, 9, 1, 1, 1);
    

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);
}

ChessGamesListWidget::~ChessGamesListWidget() {
    
}