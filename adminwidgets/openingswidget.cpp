#include "openingswidget.h"

#include <QSqlQuery>
OpeningsWidget::OpeningsWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Openings");

    pageLayout = new QFormLayout;

    id = new QLineEdit();
    group = new QLineEdit;
    name = new QLineEdit;
    group = new QLineEdit;
    namedAfter = new QLineEdit;
    altNames = new QLineEdit;
    moves = new QLineEdit;

    pageLayout->addRow("ECO ID", id);
    pageLayout->addRow("Group", group);
    pageLayout->addRow("Name", name);
    pageLayout->addRow("Moves", moves);
    pageLayout->addRow("Alternative names", altNames);
    pageLayout->addRow("Named after", namedAfter);
    

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);

    connect(formHeader, &FormHeader::exit, this, [this] {emit exit();});
    connect(formHeader, &FormHeader::prev, this, [this] {
        if (curInd) {
            --curInd;
            loadPage();
        }
    });
    connect(formHeader, &FormHeader::next, this, [this] {
        ++curInd;
        loadPage();
    });


    loadPage();

}

OpeningsWidget::~OpeningsWidget() {
    
}

void OpeningsWidget::loadPage() {
    loadIds();

    QSqlQuery query("SELECT openings_group, name, moves, alternative_names, named_after FROM openings"
                    " WHERE eco_id = \'" + ecoID + "\'");
    while (query.next()) {
        id->setText(ecoID);
        group->setText(query.value(0).toString().simplified());
        name->setText(query.value(1).toString().simplified());
        moves->setText(query.value(2).toString().simplified());
        altNames->setText(query.value(3).toString().simplified());
        namedAfter->setText(query.value(4).toString().simplified());
    }
}

void OpeningsWidget::loadIds() {
    QSqlQuery query("SELECT eco_id FROM openings");
    ids.clear();
    while (query.next()) {
        ids.push_back(query.value(0).toString().simplified());
    }

    ecoID = ids[curInd];
}
