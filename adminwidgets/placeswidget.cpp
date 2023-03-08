#include "placeswidget.h"

#include <QSqlQueryModel>
PlacesWidget::PlacesWidget(FormWidget *parent):
    FormWidget{parent} {

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
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();


}

PlacesWidget::~PlacesWidget() {
    
}


void PlacesWidget::loadPage() {
    id->setValue(curInd);
    QSqlQuery query("SELECT city, country FROM places WHERE place_id = " + QString::number(curInd));
    while (query.next()) {
        city->setText(query.value(0).toString().simplified());
        country->setText(query.value(1).toString().simplified());
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT tournament_id AS ID, tournaments.name AS Турнир, winner.name AS Победитель"
                    " FROM tournaments"
                    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
                    " WHERE place_id = " + QString::number(curInd));

    placesTournaments->setModel(model);
    resizeTableView(placesTournaments);
    placesTournaments->show();
}

void PlacesWidget::saveChanges() {
    bool exists = QSqlQuery("SELECT * FROM places WHERE place_id = " + QString::number(curInd)).next();
    if (exists) {
        QSqlQuery query;
        query.prepare("UPDATE places SET"
                      " city = :city,"
                      " country = :country"
                      " WHERE place_id = :place_id");

        query.bindValue(":city", city->text());
        query.bindValue(":country", country->text());
        query.bindValue(":place_id", curInd);

        query.exec();
    } else {
        QSqlQuery query;

        query.prepare("INSERT INTO places VALUES("
                      " :place_id,"
                      " :city,"
                      " :country)");

        query.bindValue(":city", city->text());
        query.bindValue(":country", country->text());
        query.bindValue(":place_id", curInd);


        query.exec();
    }
}
