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
    explicit PlacesWidget(FormWidget *parent = nullptr);
    ~PlacesWidget();
private:
    void setMaxInd() {QSqlQuery query("SELECT MAX(place_id) FROM places");
    if (query.next()) {
        curInd = query.value(0).toInt();
    }};
    void loadPage();
    void setupMain();
    void saveChanges();

    QLineEdit *city, *country;
    QSpinBox *id;
    QPushButton *save;

    QTableView *placesTournaments;
    

};
#endif //PLACESWIDGET_H
