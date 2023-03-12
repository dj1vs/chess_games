#include "chessplayerswidget.h"

#include <QDebug>
ChessplayersWidget::ChessplayersWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Шахматисты");

    id = new QLineEdit;
    name = new QLineEdit;

    rating = new QSpinBox;
    rating->setRange(0, 4000);
    birthYear = new QSpinBox;
    birthYear->setRange(1400, 2023);

    save = new QPushButton("Сохранить");

    layout = new QVBoxLayout(this);


    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Имя"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Рейтинг"));
    layout->addWidget(rating);
    layout->addWidget(new QLabel("Год рождения"));
    layout->addWidget(birthYear);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();

    connect(save, &QPushButton::clicked, this, [this] {
        emit setChessplayer({
        {"name", QVariant(name->text())},
        {"elo_rating", QVariant(rating->value())},
        {"birth_year", QVariant(birthYear->value())},
        {"chessplayer_id", QVariant(curInd)}});
    });

    loadPage();


}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::connectWorker() {
    connect(this, &ChessplayersWidget::getChessplayer, worker, &SQLWorker::getChessplayer);
    connect(worker, &SQLWorker::chessplayerReady, this, &ChessplayersWidget::load);
    connect(this, &ChessplayersWidget::setChessplayer, worker, &SQLWorker::setChessplayer);
    connect(worker, &SQLWorker::chessplayerSet, this, [this] {showSaved();});

    connect(this, &ChessplayersWidget::setMaxInd, worker, &SQLWorker::getMaxChessplayerID);
    connect(worker, &SQLWorker::maxChessplayerIDReady, this, &ChessplayersWidget::loadMaxInd);
}

void ChessplayersWidget::load(DMap map) {
    name->setText(map["name"].toString().simplified());
    rating->setValue(map["elo_rating"].toInt());
    birthYear->setValue(map["birth_year"].toInt());
    id->setText(QString::number(curInd));
}

void ChessplayersWidget::loadPage() {
    emit getChessplayer(curInd);
}
