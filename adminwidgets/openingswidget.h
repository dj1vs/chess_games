#ifndef OPENINGSWIDGET_H
#define OPENINGSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>

class OpeningsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit OpeningsWidget(FormWidget *parent = nullptr);
   ~OpeningsWidget();
private:
    void loadIds();
    void loadPage();
    void saveChanges();

    QString ecoID;
    QStringList ids;

    QLineEdit *id, *group, *name, *moves, *altNames, *namedAfter;
    QPushButton *save;
};
#endif //OPENINGSWIDGET_H
