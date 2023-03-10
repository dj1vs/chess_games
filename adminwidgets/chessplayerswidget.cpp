#include "chessplayerswidget.h"

#include <QDebug>
ChessplayersWidget::ChessplayersWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    id = new QLineEdit;
    name = new QLineEdit;
    rating = new QLineEdit;
    //rating->setRange(0, 3500);

    birthYear = new QLineEdit;
    //birthYear->setRange(1400, 2023);

    save = new QPushButton("Save");

    layout = new QVBoxLayout(this);


    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Chessplayer id"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Rating"));
    layout->addWidget(rating);
    layout->addWidget(new QLabel("Birth year"));
    layout->addWidget(birthYear);
    layout->addWidget(save);

    initWorker();

    loadPage();

    connectFormHeader();

    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});


}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::loadPage() {
    auto map = worker->getChessplayer(curInd);
    name->setText(map["name"]);
    rating->setText(map["elo_rating"]);
    birthYear->setText(map["birth_year"]);
    id->setText(QString::number(curInd));
}

void ChessplayersWidget::saveChanges() {
    worker->setChessplayer({
        {"name", name->text()},
        {"elo_rating", rating->text()},
        {"birth_year", birthYear->text()},
        {"chessplayer_id", QString::number(curInd)}
    });
}

inline bool ChessplayersWidget::checkIfRecordExists() {
    QSqlQuery query("SELECT * FROM chessplayers WHERE chessplayer_id = " + QString::number(curInd));
    return query.next();
}
