#ifndef OPENINGSWIDGET_H
#define OPENINGSWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>

#include <QFormLayout>
#include <QVBoxLayout>

class OpeningsWidget : public QWidget {
    Q_OBJECT
public:
    explicit OpeningsWidget(QWidget *parent = nullptr);
   ~OpeningsWidget();
private:
    FormHeader *formHeader;

    QLineEdit *id, *group, *name, *moves, *altNames, *namedAfter;

    QFormLayout *pageLayout;
    QVBoxLayout *mainLayout;
};
#endif //OPENINGSWIDGET_H