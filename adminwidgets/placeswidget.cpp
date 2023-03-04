#include "placeswidget.h"
PlacesWidget::PlacesWidget(FormWidget *parent):
    FormWidget{parent} {

    city = new QLineEdit;
    country = new QLineEdit;
    id = new QComboBox;
    formHeader = new FormHeader;
    gotoTournaments = new QPushButton();

    pageLayout = new QFormLayout;
    pageLayout->addRow("Places", gotoTournaments);
    pageLayout->addRow("ID", id);
    pageLayout->addRow("City", city);
    pageLayout->addRow("Country",country);
    pageLayout->addWidget(formHeader);

    setLayout(pageLayout);

    connect(gotoTournaments, &QPushButton::clicked, this, [this] {
        placesTournaments = new QTableView;
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(placesTournaments);
        layout->addWidget(formHeader);

        delete pageLayout;
        setLayout(layout);
    });

    connectFormHeader();


}

PlacesWidget::~PlacesWidget() {
    
}
