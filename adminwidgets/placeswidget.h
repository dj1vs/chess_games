#ifndef PLACESWIDGET_H
#define PLACESWIDGET_H

#include "../formwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class PlacesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit PlacesWidget(FormWidget *parent = nullptr);
    ~PlacesWidget();
private:
    void loadPage() {}

    QLineEdit *city, *country;
    QComboBox *id;
    QPushButton *gotoTournaments;

    QTableView *placesTournaments;

    QVBoxLayout *mainLayout;
    QFormLayout *pageLayout;

    

};
#endif //PLACESWIDGET_H
