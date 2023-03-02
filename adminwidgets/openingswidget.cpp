#include "openingswidget.h"
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

}

OpeningsWidget::~OpeningsWidget() {
    
}