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
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();

}

OpeningsWidget::~OpeningsWidget() {
    
}

void OpeningsWidget::loadPage() {
    loadIds();

    id->setText(ecoID);
    auto map = worker->getOpening(ecoID);
    group->setText(map["group"]);
    name->setText(map["name"]);
    moves->setText(map["moves"]);
    altNames->setText(map["alt_names"]);
    namedAfter->setText(map["named_after"]);
}

void OpeningsWidget::loadIds() {
    ids = worker->getAllOpeningdIds();

    ecoID = ids[curInd - 1];
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
