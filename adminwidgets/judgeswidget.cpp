#include "judgeswidget.h"
JudgesWidget::JudgesWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Judges");

    id = new QSpinBox;
    name = new QLineEdit;
    mail = new QLineEdit;

    tournaments = new QTableView;

    layout = new QGridLayout;
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Mail"));
    layout->addWidget(mail);
    layout->addWidget(tournaments);

    setLayout(layout);

    connectFormHeader();

    loadPage();
}

JudgesWidget::~JudgesWidget() {
    
}

void JudgesWidget::loadPage() {
    QSqlQuery query("SELECT name, email FROM judges WHERE judge_id = " + QString::number(curInd));

    while (query.next()) {
        name->setText(query.value(0).toString());
        mail->setText(query.value(1).toString());
    }


}
