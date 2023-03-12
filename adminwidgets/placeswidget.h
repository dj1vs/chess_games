#ifndef PLACESWIDGET_H
#define PLACESWIDGET_H

#include "../form/formwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QSpinBox>

class PlacesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit PlacesWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~PlacesWidget();
public slots:
    void loadPlace(DMap map);
    void loadPlacesTournaments(DTable table);
private:
    //void setMaxInd() {curInd = worker->getMaxPlaceID();};
    void loadPage();
    void connectWorker();

    QLineEdit *city, *country;
    QSpinBox *id;
    QPushButton *save;

    QTableView *placesTournaments;
signals:
    void getPlace(quint32 ind);
    void getPlacesTournaments(quint32 ind);

    void setPlace(DMap map);
    

};
#endif //PLACESWIDGET_H
