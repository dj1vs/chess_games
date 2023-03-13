#include "gameswidget.h"

#include <QDate>

GamesWidget::GamesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Шахматные партии");

    id = new QSpinBox;
    format = new QLineEdit;
    moves = new QTextEdit;
    result = new QGroupBox;
    win = new QRadioButton("1-0");
    lose = new QRadioButton("0-1");
    draw = new QRadioButton("1-1");
    QVBoxLayout *resultLayout = new QVBoxLayout;
    resultLayout->addWidget(win);
    resultLayout->addWidget(lose);
    resultLayout->addWidget(draw);

    result->setLayout(resultLayout);
    result->setTitle("Исход");
    timeControl = new QLineEdit;
    date = new QDateEdit;
    white = new QLineEdit;
    black = new QLineEdit;
    opening = new QLineEdit;
    tournament = new QLineEdit;
    save = new QPushButton("Сохранить");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Формат"));
    layout->addWidget(format);
    layout->addWidget(new QLabel("Ходы"));
    layout->addWidget(moves);
    layout->addWidget(result);
    layout->addWidget(new QLabel("Контроль времени"));
    layout->addWidget(timeControl);
    layout->addWidget(new QLabel("Дата"));
    layout->addWidget(date);
    layout->addWidget(new QLabel("Белые"));
    layout->addWidget(white);
    layout->addWidget(new QLabel("Чёрные"));
    layout->addWidget(black);
    layout->addWidget(new QLabel("Турнир"));
    layout->addWidget(tournament);
    layout->addWidget(new QLabel("Дебют"));
    layout->addWidget(opening);
    layout->addWidget(save);

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {
        emit setGame({
        {"format", format->text()},
        {"moves", moves->toPlainText()},
        {"result", (win->isChecked() ? "1-0" : (lose->isChecked() ? "0-1" : "1-1"))},
        {"time_control", timeControl->text()},
        {"date", date->date()},
        {"white", white->text()},
        {"tournament", tournament->text()},
        {"black", black->text()},
        {"opening", opening->text()},
        {"id", curInd}
        });
    });
    connectWorker();

    loadPage();

    emit getChessplayers();
    emit getOpenings();
    emit getTournaments();
}

void GamesWidget::connectWorker() {
    connect(this, &GamesWidget::getGame, worker, &SQLWorker::getGame);
    connect(worker, &SQLWorker::gameReady, this, &GamesWidget::load);
    connect(this, &GamesWidget::setGame, worker, &SQLWorker::setGame);
    connect(worker, &SQLWorker::gameSet, this, [this] {showSaved();});
    connect(this, &GamesWidget::getChessplayers, worker, &SQLWorker::getAllChessplayersNames);
    connect(worker, &SQLWorker::allChessplayersNamesReady, this, &GamesWidget::loadChessplayers);
    connect(this, &GamesWidget::getOpenings, worker, &SQLWorker::getAllOpeningsNames);
    connect(worker, &SQLWorker::allOpeningsNamesReady, this, &GamesWidget::loadOpenings);
    connect(this, &GamesWidget::getTournaments, worker, &SQLWorker::getAllTournamentsNames);
    connect(worker, &SQLWorker::allTournamentsNamesReady, this, &GamesWidget::loadTournaments);

    connect(this, &GamesWidget::setMaxInd, worker, &SQLWorker::getMaxGameID);
    connect(worker, &SQLWorker::maxGameIDReady, this, &GamesWidget::loadMaxInd);
}

GamesWidget::~GamesWidget() {
    
}

void GamesWidget::loadChessplayers(QStringList names) {
    chessplayersCompleter = new QCompleter(names);

    white->setCompleter(chessplayersCompleter);
    black->setCompleter(chessplayersCompleter);
}

void GamesWidget::loadOpenings(QStringList names) {
    openingsCompleter = new QCompleter(names);

    opening->setCompleter(openingsCompleter);
}
void GamesWidget::loadTournaments(QStringList names) {
    tournamentsCompleter = new QCompleter(names);

    tournament->setCompleter(tournamentsCompleter);
}

void GamesWidget::load(const DMap &map) {
    format->setText(map["format"].qstring);
    moves->setText(map["moves"].qstring);
    QString gameResult = map["result"].qstring;
    if (gameResult == "1-0") {
        win->setChecked(true);
    } else if (gameResult == "0-1") {
        lose->setChecked(true);
    } else {
        draw->setChecked(true);
    }
    timeControl->setText(map["time_control"].qstring);
    date->setDate(map["date"].toDate());
    white->setText(map["white_name"].qstring);
    black->setText(map["black_name"].qstring);
    opening->setText(map["opening"].qstring);
    tournament->setText(map["tournament"].qstring);
    id->setValue(curInd);
}

void GamesWidget::loadPage() {
    emit getGame(curInd);
}
