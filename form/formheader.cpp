#include "formheader.h"

FormHeader::FormHeader(QWidget *parent) :
    QWidget(parent) {
        exitButton = new QPushButton("Exit");
        prevButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowLeft), "");
        nextButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ArrowRight), "");
        printButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon), "");
        beginningButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_MediaSeekBackward), "");
        endingButton = new QPushButton(QApplication::style()->standardIcon(QStyle::SP_MediaSeekForward), "");


        titleLabel = new QLabel("");

        layout = new QHBoxLayout(this);
        layout->addWidget(titleLabel);
        layout->addWidget(exitButton);
        layout->addWidget(beginningButton);
        layout->addWidget(prevButton);
        layout->addWidget(nextButton);
        layout->addWidget(endingButton);
        layout->addWidget(printButton);
        

        connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});
        connect(prevButton, &QPushButton::clicked, this, [this] {emit prev();});
        connect(nextButton, &QPushButton::clicked, this, [this] {emit next();});
        connect(printButton, &QPushButton::clicked, this, [this] {emit print();});
        connect(beginningButton, &QPushButton::clicked, this, [this] {emit beginning();});
        connect(endingButton, &QPushButton::clicked, this, [this] {emit ending();});

}

FormHeader::~FormHeader() {
}
