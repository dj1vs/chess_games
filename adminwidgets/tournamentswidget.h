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
#include <QComboBox>
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
    FormHeader *formHeader;
    QComboBox *id, *ratingRestriction;
    QLineEdit *name, *winner, *city, *country;
    QGroupBox *judgeBox;
    QVector <QRadioButton*> judgeButtons;
    QTableView *playedGames;

    QGridLayout *pageLayout;
    QVBoxLayout *mainLayout;
     
    
};
#endif //TOURNAMENTSWIDGET_H
