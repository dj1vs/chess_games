#ifndef OPENINGSWIDGET_H
#define OPENINGSWIDGET_H

#include "../formwidget.h"

#include <QWidget>

#include <QLineEdit>

#include <QFormLayout>
#include <QVBoxLayout>

class OpeningsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit OpeningsWidget(FormWidget *parent = nullptr);
   ~OpeningsWidget();
private:
    void loadIds();
    void loadPage();

    QString ecoID;
    QStringList ids;

    QLineEdit *id, *group, *name, *moves, *altNames, *namedAfter;

    QFormLayout *pageLayout;
    QVBoxLayout *mainLayout;
};
#endif //OPENINGSWIDGET_H
