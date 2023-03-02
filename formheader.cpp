#include "formheader.h"

FormHeader::FormHeader(QWidget *parent) :
    QWidget(parent) {
        exitButton = new QPushButton("Exit");
        prevButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowLeft), "");
        nextButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowRight), "");
        printButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon), "");

        titleLabel = new QLabel("");

        layout = new QHBoxLayout();
        layout->addWidget(titleLabel);
        layout->addWidget(exitButton);
        layout->addWidget(prevButton);
        layout->addWidget(nextButton);
        layout->addWidget(printButton);

        setLayout(layout);

        connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});
        connect(prevButton, &QPushButton::clicked, this, [this] {emit prev();});
        connect(nextButton, &QPushButton::clicked, this, [this] {emit next();});
        connect(printButton, &QPushButton::clicked, this, [this] {emit print();});

}

FormHeader::~FormHeader() {
}
