#include "formwidget.h"

FormWidget::FormWidget(QWidget *parent)
    : QWidget{parent}
{


}

void FormWidget::connectFormHeader() {
    connect(formHeader, &FormHeader::exit, this, [this] {emit exit();});
    connect(formHeader, &FormHeader::prev, this, [this] {
        if (curInd - 1) {
            --curInd;
            loadPage();
        }
    });
    connect(formHeader, &FormHeader::next, this, [this] {
        ++curInd;
        loadPage();
    });
}
