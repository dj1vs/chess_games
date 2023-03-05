#include "judgeswidget.h"

#include <QSqlQueryModel>
JudgesWidget::JudgesWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Judges");

    id = new QSpinBox;
    name = new QLineEdit;
    mail = new QLineEdit;

    save = new QPushButton("Save");

    tournaments = new QTableView;

    layout = new QGridLayout;
    layout->addWidget(formHeader, 0, 0, 1, 1);
    layout->addWidget(new QLabel("ID"), 1, 0, 1, 1);
    layout->addWidget(id, 2, 0, 1, 1);
    layout->addWidget(new QLabel("Name"), 3, 0, 1, 1);
    layout->addWidget(name, 4, 0, 1, 1);
    layout->addWidget(new QLabel("Mail"), 5, 0, 1, 1);
    layout->addWidget(mail, 6, 0, 1, 1);
    layout->addWidget(tournaments, 7, 0, 5, 5);
    layout->addWidget(save, 13, 0, 1, 1);

    setLayout(layout);

    connectFormHeader();
    connect(save, &QPushButton::clicked, this, [this] {saveChanges();});

    loadPage();
}

JudgesWidget::~JudgesWidget() {
    
}

void JudgesWidget::loadPage() {
    id->setValue(curInd);
    QSqlQuery query("SELECT name, email FROM judges WHERE judge_id = " + QString::number(curInd));

    while (query.next()) {
        name->setText(query.value(0).toString().simplified());
        mail->setText(query.value(1).toString().simplified());
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT tournaments.name, winner.name, city, country"
                      " FROM tournaments"
                      " INNER JOIN chessplayers AS winner ON winner.chessplayer_id = winner_id"
                      " INNER JOIN places ON places.place_id = tournaments.place_id"
                      " WHERE judge_id = " + QString::number(curInd));

    tournaments->setModel(model);
    tournaments->show();
}

void JudgesWidget::saveChanges() {
    bool exists = QSqlQuery("SELECT * FROM judges WHERE judge_id = " + QString::number(curInd)).next();
    if (exists) {
        QSqlQuery query;
        query.prepare("UPDATE judges SET"
                      " name = :name,"
                      " email = :mail"
                      " WHERE judge_id = :judge_id");

        query.bindValue(":name", name->text());
        query.bindValue(":email", mail->text());
        query.bindValue(":judge_id", curInd);

        query.exec();
    } else {
        QSqlQuery query;

        query.prepare("INSERT INTO judges VALUES("
                      " :judge_id,"
                      " :name,"
                      " :email");

        query.bindValue(":judge_id", curInd);
        query.bindValue(":name", name->text());
        query.bindValue(":mail", mail->text());

        query.exec();
    }
}
