#include "gameswidget.h"

#include <QDate>

GamesWidget::GamesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Chess games");

    id = new QSpinBox;
    format = new QLineEdit;
    moves = new QTextEdit;
    result = new QLineEdit;
    timeControl = new QLineEdit;
    date = new QLineEdit;
    white = new QLineEdit;
    black = new QLineEdit;
    opening = new QLineEdit;
    tournament = new QLineEdit;
    save = new QPushButton("Save");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Format"));
    layout->addWidget(format);
    layout->addWidget(new QLabel("Moves"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Result"));
    layout->addWidget(result);
    layout->addWidget(new QLabel("TimeControl"));
    layout->addWidget(timeControl);
    layout->addWidget(new QLabel("Date"));
    layout->addWidget(date);
    layout->addWidget(new QLabel("White"));
    layout->addWidget(white);
    layout->addWidget(new QLabel("Tournament"));
    layout->addWidget(tournament);
    layout->addWidget(new QLabel("Black"));
    layout->addWidget(black);
    layout->addWidget(new QLabel("Opening"));
    layout->addWidget(opening);
    layout->addWidget(save);

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {
        worker->setGame({
        {"format", QVariant(format->text())},
        {"moves", QVariant(moves->toPlainText())},
        {"result", QVariant(result->text())},
        {"time_control", QVariant(timeControl->text())},
        {"date", QVariant(date->text())},
        {"white", QVariant(white->text())},
        {"tournament", QVariant(tournament->text())},
        {"black", QVariant(black->text())},
        {"opening", QVariant(opening->text())},
        {"id", QVariant(curInd)}
        });
    });
    connectWorker();

    loadPage();

    emit getChessplayers();

    // openingsCompleter = new QCompleter(worker->getAllOpeningsNames(), this);
    // tournamentsCompleter = new QCompleter(worker->getAllTournamentsNames(), this);
    // opening->setCompleter(openingsCompleter);
    // tournament->setCompleter(tournamentsCompleter);



}

void GamesWidget::connectWorker() {
    connect(this, &GamesWidget::getGame, worker, &SQLWorker::getGame);
    connect(worker, &SQLWorker::gameReady, this, &GamesWidget::load);
    connect(this, &GamesWidget::setGame, worker, &SQLWorker::setGame);
    connect(worker, &SQLWorker::gameSet, this, [this] {showSaved();});
    connect(this, &GamesWidget::getChessplayers, worker, &SQLWorker::getAllChessplayersNames);
    connect(worker, &SQLWorker::allChessplayersNamesReady, this, &GamesWidget::loadChessplayers);
}

GamesWidget::~GamesWidget() {
    
}

void GamesWidget::loadChessplayers(QStringList names) {
    chessplayers = names;
    chessplayersCompleter = new QCompleter(chessplayers);

    white->setCompleter(chessplayersCompleter);
    black->setCompleter(chessplayersCompleter);
}

void GamesWidget::load(const DMap &map) {
    format->setText(map["format"].qstring);
    moves->setText(map["moves"].qstring);
    result->setText(map["result"].qstring);
    timeControl->setText(map["time_control"].qstring);
    date->setText(map["date"].qstring);
    white->setText(map["white_name"].qstring);
    black->setText(map["black_name"].qstring);
    opening->setText(map["opening"].qstring);
    tournament->setText(map["tournament"].qstring);
    id->setValue(curInd);
}

void GamesWidget::loadPage() {
    emit getGame(curInd);
}