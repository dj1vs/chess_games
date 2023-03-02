#include "chessplayerswidget.h"
ChessplayersWidget::ChessplayersWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chessplayers");

    pageLayout = new QFormLayout;

    id = new QComboBox;
    name = new QLineEdit;
    rating = new QComboBox;
    birthYear = new QComboBox;

    pageLayout->addRow("Chessplayer id", id);
    pageLayout->addRow("Name", name);
    pageLayout->addRow("Rating", rating);
    pageLayout->addRow("Birth year", birthYear);
    
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formHeader);
    mainLayout->addLayout(pageLayout);

    setLayout(mainLayout);
}

ChessplayersWidget::~ChessplayersWidget() {
    
}