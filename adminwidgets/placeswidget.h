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
private:
    void setMaxInd() {curInd = worker->getMaxPlaceID();};
    void loadPage();
    void setupMain();
    void saveChanges();

    QLineEdit *city, *country;
    QSpinBox *id;
    QPushButton *save;

    QTableView *placesTournaments;
    

};
#endif //PLACESWIDGET_H
