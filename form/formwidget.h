#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include "formheader.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include <QPainter>
#include <QPrinter>

#define TABLE_CELL_SIZE 25

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FormWidget(QWidget *parent = nullptr);
signals:
    void exit();
protected:

    virtual void loadPage() = 0;
    virtual void setMaxInd() = 0;
    void connectFormHeader();
    void printPage();
    void resizeTableView(QTableView *v);

    quint32 curInd = 1;

    FormHeader *formHeader;
    QVBoxLayout *layout;

signals:

};

#endif // FORMWIDGET_H
