#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include "formheader.h"
#include "../sqlworker.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QDebug>
#include <QPainter>
#include <QPrinter>
#include <QThread>
#include <QMessageBox>

#define TABLE_CELL_SIZE 25

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FormWidget(QWidget *parent = nullptr);
signals:
    void exit();
protected slots:
    virtual void loadPage() = 0;
    void launchPageLoading();
protected:
    virtual void setMaxInd() = 0;
    void connectFormHeader();
    void printPage();
    void resizeTableView(QTableView *v);
    void showSearchError();
    void showSaved();

    quint32 curInd = 1;

    SQLWorker *worker;
    QThread *workerThread;

    FormHeader *formHeader;
    QVBoxLayout *layout;

signals:

};

#endif // FORMWIDGET_H
