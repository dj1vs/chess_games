#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include "formheader.h"

#include <QWidget>
#include <QVBoxLayout>

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FormWidget(QWidget *parent = nullptr);
signals:
    void exit();
protected:

    virtual void loadPage() = 0;
    void connectFormHeader();
    quint32 curInd = 1;

    FormHeader *formHeader;
    QGridLayout *layout;

signals:

};

#endif // FORMWIDGET_H
