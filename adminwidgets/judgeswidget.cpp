#include "judgeswidget.h"
JudgesWidget::JudgesWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Judges");

    id = new QComboBox;
    name = new QLineEdit;
    mail = new QLineEdit;

    tournaments = new QTableView;

    layout = new QFormLayout;
    layout->addWidget(formHeader);
    layout->addRow("ID", id);
    layout->addRow("Name:", name);
    layout->addRow("Mail:", mail);
    layout->addWidget(tournaments);

    setLayout(layout);

    connectFormHeader();
}

JudgesWidget::~JudgesWidget() {
    
}
