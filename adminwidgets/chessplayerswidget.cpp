#include "chessplayerswidget.h"

#include <QDebug>
ChessplayersWidget::ChessplayersWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    id = new QLineEdit;
    name = new QLineEdit;

    rating = new QSpinBox;
    rating->setRange(0, 4000);
    birthYear = new QSpinBox;
    birthYear->setRange(1400, 2023);

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

    connectFormHeader();
    connectWorker();

    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();


}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::connectWorker() {
    initWorker();
    connect(this, &ChessplayersWidget::getChessplayer, worker, &SQLWorker::getChessplayer);
    connect(worker, &SQLWorker::chessplayerReady, this, &ChessplayersWidget::setChessplayer);

    workerThread->start();
}

void ChessplayersWidget::setChessplayer(DMap map) {
    name->setText(map["name"].toString());
    rating->setValue(map["elo_rating"].toInt());
    birthYear->setValue(map["birth_year"].toInt());
    id->setText(QString::number(curInd));
}



void ChessplayersWidget::loadPage() {
    emit getChessplayer(curInd);
}

void ChessplayersWidget::saveChanges() {
    worker->setChessplayer({
        {"name", name->text()},
        {"elo_rating", QString::number(rating->value())},
        {"birth_year", QString::number(birthYear->value())},
        {"chessplayer_id", QString::number(curInd)}
    });

    showSaved();
}