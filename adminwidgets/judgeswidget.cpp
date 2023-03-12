#include "judgeswidget.h"

JudgesWidget::JudgesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Судьи");

    id = new QSpinBox;
    name = new QLineEdit;
    mail = new QLineEdit;

    save = new QPushButton("Сохранить");

    tournaments = new QTableView;

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Имя"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Почта"));
    layout->addWidget(mail);
    layout->addWidget(tournaments);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {
        emit setJudge({
        {"id", curInd},
        {"name", name->text()},
        {"email", mail->text()}
        });
    });

    loadPage();
}

JudgesWidget::~JudgesWidget() {
    
}

void JudgesWidget::connectWorker() {
    connect(this, &JudgesWidget::getJudge, worker, &SQLWorker::getJudge);
    connect(worker, &SQLWorker::judgeReady, this, &JudgesWidget::loadJudge);
    connect(this, &JudgesWidget::getJudgesTournaments, worker, &SQLWorker::getJudgesTournaments);
    connect(worker, &SQLWorker::judgesTournamentsReady, this, &JudgesWidget::loadJudgesTournaments);

    connect(this, &JudgesWidget::setJudge, worker, &SQLWorker::setJudge);
    connect(worker, &SQLWorker::judgeSet, this, [this] {showSaved();});

    connect(this, &JudgesWidget::setMaxInd, worker, &SQLWorker::getMaxJudgeID);
    connect(worker, &SQLWorker::maxJudgeIDReady, this, &JudgesWidget::loadMaxInd);
}

void JudgesWidget::loadJudgesTournaments(DTable table) {
    tournaments->setModel(DTableToModel(table, \
        {"Турнир", "Победитель", "Город", "Страна"}));
    resizeTableView(tournaments);
    tournaments->show();
}

void JudgesWidget::loadJudge(const DMap &map) {
    id->setValue(curInd);
    name->setText(map["name"].qstring);
    mail->setText(map["mail"].qstring); 
}


void JudgesWidget::loadPage() {
    emit getJudge(curInd);
    emit getJudgesTournaments(curInd);
}

