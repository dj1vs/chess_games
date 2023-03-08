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

    layout = new QVBoxLayout(this);
    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("ID"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Name"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Mail"));
    layout->addWidget(mail);
    layout->addWidget(tournaments);
    layout->addWidget(save);

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
    model->setQuery("SELECT tournaments.name AS Турнир, winner.name AS Победитель,"
                      "city AS Город, country AS Страна"
                      " FROM tournaments"
                      " INNER JOIN chessplayers AS winner ON winner.chessplayer_id = winner_id"
                      " INNER JOIN places ON places.place_id = tournaments.place_id"
                      " WHERE judge_id = " + QString::number(curInd));


    tournaments->setModel(model);
    resizeTableView(tournaments);
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
