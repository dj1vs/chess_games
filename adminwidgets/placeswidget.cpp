#include "placeswidget.h"

#include "../sqlworker.h"

PlacesWidget::PlacesWidget(SQLWorker *w, FormWidget *parent):
    FormWidget{parent} {
        worker = w;


    city = new QLineEdit;
    country = new QLineEdit;
    id = new QSpinBox;
    formHeader = new FormHeader;
    formHeader->setTitle("Places");
    save = new QPushButton("Save");
    placesTournaments = new QTableView;

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("City"));
    layout->addWidget(city);
    layout->addWidget(new QLabel("Country"));
    layout->addWidget(country);
    layout->addWidget(new QLabel("Places tournaments:"));
    layout->addWidget(placesTournaments);
    layout->addWidget(save);

    connectFormHeader();
    connectWorker();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();


}

PlacesWidget::~PlacesWidget() {
    
}

void PlacesWidget::connectWorker() {
    initWorker();

    connect(this, &PlacesWidget::getPlace, worker, &SQLWorker::getPlace);
    connect(worker, &SQLWorker::placeReady, this, &PlacesWidget::loadPlace);
}

void PlacesWidget::loadPlace(DMap map) {
    id->setValue(curInd);

    city->setText(map["city"].toString());
    country->setText(map["country"].toString());

    // placesTournaments->setModel(worker->getPlacesTournaments(curInd));
    // resizeTableView(placesTournaments);
    // placesTournaments->show();
}


void PlacesWidget::loadPage() {
    emit getPlace(curInd);
    // id->setValue(curInd);
    // DBMap map = worker->getPlace(curInd);
    // city->setText(map["city"]);
    // country->setText(map["country"]);

    // placesTournaments->setModel(worker->getPlacesTournaments(curInd));
    // resizeTableView(placesTournaments);
    // placesTournaments->show();
}

void PlacesWidget::saveChanges() {
    worker->setPlace({
        {"id", QString::number(curInd)},
        {"city", city->text()},
        {"country", country->text()}
    });

    showSaved();
}
