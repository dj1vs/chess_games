#include "placeswidget.h"

#include "../sqlworker.h"

PlacesWidget::PlacesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;


    city = new QLineEdit;
    country = new QLineEdit;
    id = new QSpinBox;
    formHeader = new FormHeader;
    formHeader->setTitle("Места");
    save = new QPushButton("Сохранить");
    placesTournaments = new QTableView;

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Город"));
    layout->addWidget(city);
    layout->addWidget(new QLabel("Страна"));
    layout->addWidget(country);
    layout->addWidget(new QLabel("Прошедшие в этом месте турниры:"));
    layout->addWidget(placesTournaments);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {
        emit setPlace({
        {"id", curInd},
        {"city", city->text()},
        {"country", country->text()}
        });
    });

    loadPage();


}

PlacesWidget::~PlacesWidget() {
    
}

void PlacesWidget::connectWorker() {
    connect(this, &PlacesWidget::getPlace, worker, &SQLWorker::getPlace);
    connect(worker, &SQLWorker::placeReady, this, &PlacesWidget::loadPlace);
    connect(this, &PlacesWidget::getPlacesTournaments, worker, &SQLWorker::getPlacesTournaments);
    connect(worker, &SQLWorker::placesTournamentsReady, this, &PlacesWidget::loadPlacesTournaments);

    connect(this, &PlacesWidget::setPlace, worker, &SQLWorker::setPlace);
    connect(worker, &SQLWorker::placeSet, this, [this] {showSaved();});

    connect(this, &PlacesWidget::setMaxInd, worker, &SQLWorker::getMaxPlaceID);
    connect(worker, &SQLWorker::maxPlaceIDReady, this, &PlacesWidget::loadMaxInd);
}

void PlacesWidget::loadPlacesTournaments(DTable table) {
    placesTournaments->setModel(DTableToModel(table,\
        {"ID", "Турнир", "Победитель"}));
    resizeTableView(placesTournaments);
    placesTournaments->show();
}

void PlacesWidget::loadPlace(DMap map) {
    id->setValue(curInd);

    city->setText(map["city"].qstring);
    country->setText(map["country"].qstring);
}


void PlacesWidget::loadPage() {
    emit getPlace(curInd);
    emit getPlacesTournaments(curInd);
}