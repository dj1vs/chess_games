#include "openingswidget.h"

OpeningsWidget::OpeningsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Openings");

    id = new QLineEdit();
    group = new QLineEdit;
    name = new QLineEdit;
    group = new QLineEdit;
    namedAfter = new QLineEdit;
    altNames = new QLineEdit;
    moves = new QLineEdit;
    save = new QPushButton("Save");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ECO ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Group"));
    layout->addWidget(group);
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Moves"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Alternative names"));
    layout->addWidget(altNames);
    layout->addWidget(new QLabel("Named after"));
    layout->addWidget(namedAfter);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});
    connect(this, &OpeningsWidget::idsSet, this, [this] {emit getOpening(ecoID);});

    loadPage();

}

OpeningsWidget::~OpeningsWidget() {
    
}

void OpeningsWidget::loadOpening(DMap map) {
    id->setText(ecoID);

    group->setText(map["group"].toString());
    name->setText(map["name"].toString());
    moves->setText(map["moves"].toString());
    altNames->setText(map["alt_names"].toString());
    namedAfter->setText(map["named_after"].toString());
}

void OpeningsWidget::connectWorker() {
    connect(this, &OpeningsWidget::getOpening, worker, &SQLWorker::getOpening);
    connect(worker, &SQLWorker::openingReady, this, &OpeningsWidget::loadOpening);
    connect(this, &OpeningsWidget::getAllOpeningsIds, worker, &SQLWorker::getAllOpeningsIds);\
    connect(worker, &SQLWorker::allOpeningsIdsReady, this, &OpeningsWidget::loadIds);
}

void OpeningsWidget::loadPage() {
    emit getAllOpeningsIds();
}

void OpeningsWidget::loadIds(QStringList ids) {
    this->ids = ids;

    ecoID = ids[curInd - 1];

    emit idsSet();
}

void OpeningsWidget::saveChanges() {
    worker->setOpening({
        {"group", group->text()},
        {"name", name->text()},
        {"moves", moves->text()},
        {"alt_names", altNames->text()},
        {"named_after", namedAfter->text()},
        {"id", ecoID}
    });

    showSaved();
}
