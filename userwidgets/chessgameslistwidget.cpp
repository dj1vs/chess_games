#include "chessgameslistwidget.h"

#include <QDebug>

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

    whiteRating = new QSpinBox;
    blackRating = new QSpinBox;

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

    loadFromDB();
    
}

ChessGamesListWidget::~ChessGamesListWidget() {
    
}

void ChessGamesListWidget::loadFromDB() {
    QString queryString = "SELECT game_date, white.name, white.elo_rating, black.name, black.elo_rating, format,"
    " time_control, opening.name, chess_games.moves"
    " FROM chess_games"
    " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
    " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id"
    " INNER JOIN openings AS opening ON opening_id = opening.eco_id";
    queryString += " WHERE game_id = " + QString::number(curInd);

    qDebug() << queryString;

    QSqlQuery query(queryString);
    while(query.next()) {
        date->setText(query.value(0).toString());
        whiteName->setText(query.value(1).toString());
        whiteRating->setValue(query.value(2).toInt());
        blackName->setText(query.value(3).toString());
        blackRating->setValue(query.value(4).toInt());
        format->setText(query.value(5).toString());
        timeControl->setText(query.value(6).toString());
        opening->setText(query.value(7).toString());
        moves->setText(query.value(8).toString());
    }


}