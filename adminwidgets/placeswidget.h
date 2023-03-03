#ifndef PLACESWIDGET_H
#define PLACESWIDGET_H

#include "../formheader.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class PlacesWidget : public QWidget {
    Q_OBJECT
public:
    explicit PlacesWidget(QWidget *parent = nullptr);
    ~PlacesWidget();
signals:
    void exit();
private:
    FormHeader *formHeader;
    QLineEdit *city, *country;
    QComboBox *id;
    QPushButton *gotoTournaments;

    QTableView *placesTournaments;

    QVBoxLayout *mainLayout;
    QFormLayout *pageLayout;

    

};
#endif //PLACESWIDGET_H
