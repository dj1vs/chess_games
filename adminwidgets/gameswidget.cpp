#include "gameswidget.h"

#include <QDate>

GamesWidget::GamesWidget(FormWidget *parent):
    FormWidget{parent} {
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
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});
    initWorker();

    loadPage();


    chessplayersCompleter = new QCompleter(worker->getAllChessplayersNames(), this);
    openingsCompleter = new QCompleter(worker->getAllOpeningsNames(), this);
    tournamentsCompleter = new QCompleter(worker->getAllTournamentsNames(), this);

    white->setCompleter(chessplayersCompleter);
    black->setCompleter(chessplayersCompleter);
    opening->setCompleter(openingsCompleter);
    tournament->setCompleter(tournamentsCompleter);



}

GamesWidget::~GamesWidget() {
    
}

void GamesWidget::loadPage() {

    auto map = worker->getGame(curInd);
    format->setText(map["format"]);
    moves->setText(map["moves"]);
    result->setText(map["result"]);
    timeControl->setText(map["time_control"]);
    date->setText(map["date"]);
    white->setText(map["white_name"]);
    black->setText(map["black_name"]);
    opening->setText(map["opening"]);
    tournament->setText(map["tournament"]);
    id->setValue(curInd);
}

void GamesWidget::saveChanges() {
    worker->setGame({
        {"format", format->text()},
        {"moves", moves->toPlainText()},
        {"result", result->text()},
        {"time_control", timeControl->text()},
        {"date", date->text()},
        {"white", white->text()},
        {"tournament", tournament->text()},
        {"black", black->text()},
        {"opening", opening->text()},
        {"id", QString::number(curInd)}
    });
    showSaved();

}
