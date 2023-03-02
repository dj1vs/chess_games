#include "gameswidget.h"
GamesWidget::GamesWidget(QWidget *parent):
    QWidget{parent} {
    formHeader = new FormHeader;
    formHeader->setTitle("Chess games");

    id = new QComboBox;
    format = new QLineEdit;
    moves = new QTextBrowser;
    result = new QComboBox;
    timeControl = new QLineEdit;
    date = new QLineEdit;
    white = new QLineEdit;
    black = new QLineEdit;
    opening = new QComboBox;
    tournamet = new QComboBox;

    layout = new QFormLayout;
    layout->addWidget(formHeader);
    layout->addRow("ID", id);
    layout->addRow("Format", format);
    layout->addRow("Moves", moves);
    layout->addRow("Result", result);
    layout->addRow("Time control", timeControl);
    layout->addRow("Date", date);
    layout->addRow("White", white);
    layout->addRow("Black", black);
    layout->addRow("Opening", opening);
    layout->addRow("Tournament", tournamet);

    setLayout(layout);
}

GamesWidget::~GamesWidget() {
    
}