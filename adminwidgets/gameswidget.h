#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QTextBrowser>
#include <QFormLayout>


class GamesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit GamesWidget(FormWidget *parent = nullptr);
    ~GamesWidget();
private:
    void loadPage();
    
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournament;
    QTextBrowser *moves;

};
#endif //GAMESWIDGET_H
