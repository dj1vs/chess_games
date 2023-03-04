#include "placeswidget.h"

#include <QSqlQueryModel>
PlacesWidget::PlacesWidget(FormWidget *parent):
    FormWidget{parent} {

    city = new QLineEdit;
    country = new QLineEdit;
    id = new QSpinBox;
    formHeader = new FormHeader;
    formHeader->setTitle("Places");
    placesTournaments = new QTableView;

    layout = new QGridLayout;
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("City"));
    layout->addWidget(city);
    layout->addWidget(new QLabel("Country"));
    layout->addWidget(country);
    layout->addWidget(new QLabel("Places tournaments:"));
    layout->addWidget(placesTournaments);

    setLayout(layout);

    connectFormHeader();

    loadPage();


}

PlacesWidget::~PlacesWidget() {
    
}


void PlacesWidget::loadPage() {
    id->setValue(curInd);
    QSqlQuery query("SELECT city, country FROM places WHERE place_id = " + QString::number(curInd));
    while (query.next()) {
        city->setText(query.value(0).toString());
        country->setText(query.value(1).toString());
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT tournament_id, tournaments.name, winner.name"
                    " FROM tournaments"
                    " INNER JOIN chessplayers AS winner ON winner_id = winner.chessplayer_id"
                    " WHERE place_id = " + QString::number(curInd));

    placesTournaments->setModel(model);
    placesTournaments->show();
}
