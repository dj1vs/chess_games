#ifndef OPENINGSWIDGET_H
#define OPENINGSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>

class OpeningsWidget : public FormWidget {
    Q_OBJECT
public:
    explicit OpeningsWidget(SQLWorker *w, FormWidget *parent = nullptr);
   ~OpeningsWidget();
public slots:
    void loadOpening(DMap map);
    void loadIds(QStringList ids);
    void loadMaxInd();
private:
    void connectWorker();
    //void setMaxInd() {curInd = ids.size() - 1;};
    void loadPage();

    QString ecoID;
    QStringList ids = {};

    QLineEdit *id, *group, *name, *moves, *altNames, *namedAfter;
    QPushButton *save;
signals:
    void getOpening(QString ind);
    void getAllOpeningsIds();

    void setOpening(DMap map);
    
    void idsSet();
};
#endif //OPENINGSWIDGET_H
