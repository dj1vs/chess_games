#ifndef PLACESWIDGET_H
#define PLACESWIDGET_H

#include <QWidget>

class PlacesWidget : public QWidget {
    Q_OBJECT
public:
    explicit PlacesWidget(QWidget *parent = nullptr);
    ~PlacesWidget();
};
#endif //PLACESWIDGET_H