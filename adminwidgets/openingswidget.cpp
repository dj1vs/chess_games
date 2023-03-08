#include "openingswidget.h"

#include <QSqlQuery>
OpeningsWidget::OpeningsWidget(FormWidget *parent):
    FormWidget{parent} {
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

    QSqlQuery query("SELECT openings_group, name, moves, alternative_names, named_after FROM openings"
                    " WHERE eco_id = \'" + ecoID + "\' ORDER BY eco_id");
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

    ecoID = ids[curInd - 1];
}

void OpeningsWidget::saveChanges() {
    bool exists = QSqlQuery("SELECT * FROM openings WHERE eco_id = \'" + ecoID + "\'").next();
    if (exists) {
        QSqlQuery query;
        query.prepare("UPDATE openings SET"
                      " openings_group = :openings_group,"
                      " name = :name,"
                      " moves = :moves,"
                      " alternative_names = :alternative_names,"
                      " named_after = :named_after"
                      " WHERE eco_id = :eco_id");

        query.bindValue(":openings_group", group->text());
        query.bindValue(":name", name->text());
        query.bindValue(":moves", moves->text());
        query.bindValue(":alternative_names", altNames->text());
        query.bindValue(":named_after", namedAfter->text());
        query.bindValue(":eco_id", ecoID);

        query.exec();
    } else {
        QSqlQuery query;
        query.prepare("INSERT INTO openings VALUES("
                      ":eco_id,"
                      ":openings_group,"
                      ":name,"
                      ":moves,"
                      ":alternative_names,"
                      " :named_after)");

        query.bindValue(":openings_group", group->text());
        query.bindValue(":name", name->text());
        query.bindValue(":moves", moves->text());
        query.bindValue(":alternative_names", altNames->text());
        query.bindValue(":named_after", namedAfter->text());
        query.bindValue(":eco_id", ecoID);

        query.exec();
    }
}
