#include "formwidget.h"

#include <QMessageBox>
#include <QFileDialog>

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
    connect(formHeader, &FormHeader::print, this, [this] {printPage();});

    connect(formHeader, &FormHeader::beginning, this, [this] {
        curInd = 1;
        loadPage();
    });

    connect(formHeader, &FormHeader::ending, this, [this] {
        setMaxInd();
        loadPage();
    });
}

void FormWidget::printPage() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QFileDialog::getSaveFileName());
    printer.setFullPage(true);

    QPainter painter(&printer);


    double xscale = printer.pageRect().width() / double(this->width());
    double yscale = printer.pageRect().height() / double(this->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().center());
    painter.scale(scale, scale);
    painter.translate(-this->width()/ 2, -this->height()/ 2);

    this->render(&painter);
}

void FormWidget::resizeTableView(QTableView *v) {
    v->setMinimumSize(v->model()->columnCount() * TABLE_CELL_SIZE, v->model()->rowCount() * TABLE_CELL_SIZE);
}
