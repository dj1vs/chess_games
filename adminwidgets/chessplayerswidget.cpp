#include "chessplayerswidget.h"
ChessplayersWidget::ChessplayersWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    pageLayout = new QFormLayout;

    id = new QSpinBox;
    name = new QLineEdit;
    rating = new QSpinBox;
    birthYear = new QSpinBox;

    pageLayout->addRow("Chessplayer id", id);
    pageLayout->addRow("Name", name);
    pageLayout->addRow("Rating", rating);
    pageLayout->addRow("Birth year", birthYear);
    
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);

    fillFields();

    connect(formHeader, &FormHeader::exit, this, [this] {emit exit();});
    connect(formHeader, &FormHeader::prev, this, [this] {
        if (currentIndex - 1) {
            --currentIndex;
            fillFields();
        }
    });
    connect(formHeader, &FormHeader::next, this, [this] {
        ++currentIndex;
        fillFields();
    });
}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::fillFields() {
    QSqlQuery query("SELECT name, elo_rating, birth_year FROM chessplayers \
    WHERE chessplayer_id = " + QString::number(currentIndex));
    while (query.next()) {
        name->setText(query.value(0).toString());
        rating->setValue(query.value(1).toInt());
        birthYear->setValue(query.value(2).toInt());
    }
    id->setValue(currentIndex);

}