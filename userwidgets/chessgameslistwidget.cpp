#include "chessgameslistwidget.h"

#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QHeaderView>
#include <QDate>

ChessGamesListWidget::ChessGamesListWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader();
    formHeader->setTitle("Chess games list");

    date = new QLineEdit();
    whiteName = new QLineEdit();
    blackName = new QLineEdit();
    format = new QLineEdit();
    timeControl = new QLineEdit();
    opening = new QLineEdit();
    result = new QLineEdit;

    date->setReadOnly(true);
    whiteName->setReadOnly(true);
    blackName->setReadOnly(true);
    format->setReadOnly(true);
    timeControl->setReadOnly(true);
    opening->setReadOnly(true);
    result->setReadOnly(true);

    whiteRating = new QLineEdit;
    blackRating = new QLineEdit;

    whiteRating->setReadOnly(true);
    blackRating->setReadOnly(true);

    moves = new QTextBrowser();

    ratingDifs = new QTableView;
    ratingDifs->setMinimumHeight(300);

    layout = new QVBoxLayout(this);

    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(date);
    layout->addWidget(new QLabel("White:"));
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(whiteName);
    layout->addWidget(new QLabel("Rating:"));
    layout->addWidget(whiteRating);
    layout->addWidget(new QLabel("Black:"));
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(blackName);
    layout->addWidget(new QLabel("Rating:"));
    layout->addWidget(blackRating);
    layout->addWidget(new QLabel("Result:"));
    layout->addWidget(result);
    layout->addWidget(new QLabel("Format:"));
    layout->addWidget(format);
    layout->addWidget(new QLabel("Time control:"));
    layout->addWidget(timeControl);
    layout->addWidget(new QLabel("Played opening:"));
    layout->addWidget(opening);
    layout->addWidget(new QLabel("Moves:"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Rating differences in games:"));
    layout->addWidget(ratingDifs);

    connectFormHeader();
    initWorker();

    loadPage();
    
}

ChessGamesListWidget::~ChessGamesListWidget() {
    
}

void ChessGamesListWidget::loadPage() {

    auto map = worker->getGame(curInd);
    date->setText(map["date"]);
    whiteName->setText(map["white_name"]);
    whiteRating->setText(map["white_rating"]);
    blackName->setText(map["black_name"]);
    blackRating->setText(map["black_rating"]);
    format->setText(map["format"]);
    timeControl->setText(map["time_control"]);
    opening->setText(map["opening"]);
    moves->setText(map["moves"]);
    result->setText(map["result"]);

    ratingDifs->setModel(worker->getGamesCrossRequest());
    resizeTableView(ratingDifs);
    ratingDifs->show();


}
