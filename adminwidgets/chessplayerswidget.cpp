#include "chessplayerswidget.h"
ChessplayersWidget::ChessplayersWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    pageLayout = new QFormLayout;

    id = new QSpinBox;
    name = new QLineEdit;
    rating = new QSpinBox;
    birthYear = new QSpinBox;

    layout = new QGridLayout;


    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Chessplayer id"));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Chessplayer id"));
    layout->addWidget(name);
    layout->addWidget(new QLabel("Chessplayer id"));
    layout->addWidget(rating);
    layout->addWidget(new QLabel("Chessplayer id"));
    layout->addWidget(birthYear);

    setLayout(layout);

    loadPage();

    connectFormHeader();


}

ChessplayersWidget::~ChessplayersWidget() {
    
}

void ChessplayersWidget::loadPage() {
    QSqlQuery query("SELECT name, elo_rating, birth_year FROM chessplayers \
    WHERE chessplayer_id = " + QString::number(curInd));
    while (query.next()) {
        name->setText(query.value(0).toString());
        rating->setValue(query.value(1).toInt());
        birthYear->setValue(query.value(2).toInt());
    }
    id->setValue(curInd);

}
