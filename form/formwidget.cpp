#include "formwidget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSizePolicy>
#include <QHeaderView>

FormWidget::FormWidget(QWidget *parent)
    : QWidget{parent}
{


}

void FormWidget::loadMaxInd(quint32 ind) {
    curInd = ind;
    loadPage();
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
        emit setMaxInd();
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
    v->setMinimumSize(v->model()->columnCount() * TABLE_CELL_SIZE, (v->model()->rowCount() + 1) * TABLE_CELL_SIZE);
    v->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    v->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void FormWidget::showSearchError() {
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setText("Таких записей нет!");
    msg.setWindowTitle("Ошибка");
    msg.exec();
}

void FormWidget::showSaved() {
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    msg.setText("Сохранено!");
    msg.setWindowTitle("Сохранение");
    msg.exec();
}

QStandardItemModel* FormWidget::DTableToModel(DTable table, QStringList tableHeader) {
    QStandardItemModel *model = new QStandardItemModel;
    if (tableHeader.size()) {
        model->setHorizontalHeaderLabels(tableHeader);
    }
    if (!table.size())
        return model;

    model->setColumnCount(table[0].size());
    model->setRowCount(table.size());

    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[0].size(); ++j) {
            model->setData(model->index(i, j), table[i][j]);
        }
    }

    return model;
}
