#ifndef TOURNAMENTSWIDGET_H
#define TOURNAMENTSWIDGET_H

#include "../formheader.h"

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableView>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QVector>
#include <QLabel>

class TournamentsWidget : public QWidget {
    Q_OBJECT
public:
    explicit TournamentsWidget(QWidget *parent = nullptr);
    ~TournamentsWidget();
signals:
    void exit();
private:
    inline void loadPage();
    void loadBasics();
    void loadTable();
    quint32 curInd = 1;

    FormHeader *formHeader;
    QSpinBox *id, *ratingRestriction;
    QLineEdit *name, *winner, *city, *country, *judge;
    QTableView *playedGames;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;
     
    
};
#endif //TOURNAMENTSWIDGET_H
