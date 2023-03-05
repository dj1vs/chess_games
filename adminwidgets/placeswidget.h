#ifndef PLACESWIDGET_H
#define PLACESWIDGET_H

#include "../form/formwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QSpinBox>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class PlacesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit PlacesWidget(FormWidget *parent = nullptr);
    ~PlacesWidget();
private:
    void loadPage();
    void setupMain();
    void saveChanges();

    QLineEdit *city, *country;
    QSpinBox *id;
    QPushButton *save;

    QTableView *placesTournaments;

    QVBoxLayout *childLayout;

    

};
#endif //PLACESWIDGET_H
