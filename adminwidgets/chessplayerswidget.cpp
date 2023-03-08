#include "chessplayerswidget.h"

#include <QDebug>
#include <QSqlError>
ChessplayersWidget::ChessplayersWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    id = new QLCDNumber;
    name = new QLineEdit;
    rating = new QLCDNumber;
    //rating->setRange(0, 3500);

    birthYear = new QLCDNumber;
    //birthYear->setRange(1400, 2023);

    save = new QPushButton("Save");

    layout = new QGridLayout(this);


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

    loadPage();

    connectFormHeader();

    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});


}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::loadPage() {
    QSqlQuery query("SELECT name, elo_rating, birth_year FROM chessplayers \
    WHERE chessplayer_id = " + QString::number(curInd));

    if (query.next()) {
        name->setText(query.value(0).toString().simplified());
        rating->display(query.value(1).toInt());
        birthYear->display(query.value(2).toInt());
        // rating->setValue(query.value(1).toInt());
        // birthYear->setValue(query.value(2).toInt());
    }
    id->display(static_cast<int>(curInd));
    //id->setValue(curInd);

}

void ChessplayersWidget::saveChanges() {
    bool exists = checkIfRecordExists();

    if (exists) {
        QSqlQuery query;
        query.prepare("UPDATE chessplayers SET"
                      " name = :name,"
                      " elo_rating = :elo_rating,"
                      " birth_year = :birth_year"
                      " WHERE chessplayer_id = :chessplayer_id");

        query.bindValue(":name", name->text());
        query.bindValue(":elo_rating", rating->value());
        query.bindValue(":birth_year", birthYear->value());
        query.bindValue(":chessplayer_id", curInd);

        query.exec();
    } else {
        QSqlQuery query;
        query.prepare("INSERT INTO chessplayers"
                      "VALUES ("
                      ":chessplayer_id,"
                      ":name,"
                      ":elo_rating,"
                      ":birth_year)");
        query.bindValue(":chessplayer_id", curInd);
        query.bindValue(":name", name->text());
        query.bindValue(":elo_rating", rating->value());
        query.bindValue(":birth_year", birthYear->value());

        query.exec();
    }
}

inline bool ChessplayersWidget::checkIfRecordExists() {
    QSqlQuery query("SELECT * FROM chessplayers WHERE chessplayer_id = " + QString::number(curInd));
    return query.next();
}
