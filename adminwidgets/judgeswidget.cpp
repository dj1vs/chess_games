#include "judgeswidget.h"

JudgesWidget::JudgesWidget(FormWidget *parent):
    FormWidget{parent} {
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
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});
    initWorker();

    loadPage();
}

JudgesWidget::~JudgesWidget() {
    
}

void JudgesWidget::loadPage() {
    id->setValue(curInd);
    auto map = worker->getJudge(curInd);
    name->setText(map["name"]);
    mail->setText(map["mail"]);

    tournaments->setModel(worker->getJudgesTournaments(curInd));
    resizeTableView(tournaments);
    tournaments->show();
}

void JudgesWidget::saveChanges() {
    worker->setJudge({
        {"id", QString::number(curInd)},
        {"name", name->text()},
        {"email", mail->text()}
    });

    showSaved();
}
