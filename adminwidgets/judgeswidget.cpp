#include "judgeswidget.h"

JudgesWidget::JudgesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Judges");

    id = new QSpinBox;
    name = new QLineEdit;
    mail = new QLineEdit;

    save = new QPushButton("Save");

    tournaments = new QTableView;

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Mail"));
    layout->addWidget(mail);
    layout->addWidget(tournaments);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();
}

JudgesWidget::~JudgesWidget() {
    
}

void JudgesWidget::connectWorker() {
    connect(this, &JudgesWidget::getJudge, worker, &SQLWorker::getJudge);
    connect(worker, &SQLWorker::judgeReady, this, &JudgesWidget::loadJudge);
    connect(this, &JudgesWidget::getJudgesTournaments, worker, &SQLWorker::getJudgesTournaments);
    connect(worker, &SQLWorker::judgesTournamentsReady, this, &JudgesWidget::loadJudgesTournaments);
}

void JudgesWidget::loadJudgesTournaments(DTable table) {
    tournaments->setModel(DTableToModel(table, \
        {"Турнир", "Победитель", "Город", "Страна"}));
    resizeTableView(tournaments);
    tournaments->show();
}

void JudgesWidget::loadJudge(const DMap &map) {
    id->setValue(curInd);
    name->setText(map["name"].toString());
    mail->setText(map["mail"].toString()); 
}


void JudgesWidget::loadPage() {
    emit getJudge(curInd);
    emit getJudgesTournaments(curInd);
}

void JudgesWidget::saveChanges() {
    worker->setJudge({
        {"id", QString::number(curInd)},
        {"name", name->text()},
        {"email", mail->text()}
    });

    showSaved();
}
