#include "openingswidget.h"

OpeningsWidget::OpeningsWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;

    formHeader = new FormHeader;
    formHeader->setTitle("Дебюты");

    id = new QLineEdit();
    group = new QLineEdit;
    name = new QLineEdit;
    group = new QLineEdit;
    namedAfter = new QLineEdit;
    altNames = new QLineEdit;
    moves = new QLineEdit;
    save = new QPushButton("Сохранить");

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ECO ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Группа дебютов"));
    layout->addWidget(group);
    layout->addWidget(new QLabel("Имя"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Ходы"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Альтернативные названия"));
    layout->addWidget(altNames);
    layout->addWidget(new QLabel("Названо в честь"));
    layout->addWidget(namedAfter);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {
        emit setOpening({
        {"group", group->text()},
        {"name", name->text()},
        {"moves", moves->text()},
        {"alt_names", altNames->text()},
        {"named_after", namedAfter->text()},
        {"id", ecoID}
        }); 
    });
    connect(this, &OpeningsWidget::idsSet, this, [this] {emit getOpening(ecoID);});

    loadPage();

}

OpeningsWidget::~OpeningsWidget() {
    
}

void OpeningsWidget::loadOpening(DMap map) {
    id->setText(ecoID);

    group->setText(map["group"].qstring);
    name->setText(map["name"].qstring);
    moves->setText(map["moves"].qstring);
    altNames->setText(map["alt_names"].qstring);
    namedAfter->setText(map["named_after"].qstring);
}

void OpeningsWidget::loadMaxInd() {
    curInd = ids.size();
    ecoID = ids.back();

    emit idsSet();
}
void OpeningsWidget::connectWorker() {
    connect(this, &OpeningsWidget::getOpening, worker, &SQLWorker::getOpening);
    connect(worker, &SQLWorker::openingReady, this, &OpeningsWidget::loadOpening);
    connect(this, &OpeningsWidget::getAllOpeningsIds, worker, &SQLWorker::getAllOpeningsIds);\
    connect(worker, &SQLWorker::allOpeningsIdsReady, this, &OpeningsWidget::loadIds);

    connect(this, &OpeningsWidget::setOpening, worker, &SQLWorker::setOpening);
    connect(worker, &SQLWorker::openingSet, this, [this] {showSaved();});

    connect(this, &OpeningsWidget::setMaxInd, this, &OpeningsWidget::loadMaxInd);
}

void OpeningsWidget::loadPage() {

    emit getAllOpeningsIds();
}

void OpeningsWidget::loadIds(QStringList ids) {
    this->ids = ids;
    if (curInd > ids.size()) {
        curInd = ids.size();
    }

    ecoID = ids[curInd - 1];

    emit idsSet();
}
