#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QTextBrowser>
#include <QFormLayout>


class GamesWidget : public QWidget {
    Q_OBJECT
public:
    explicit GamesWidget(QWidget *parent = nullptr);
    ~GamesWidget();
signals:
    void exit();
private:
    void loadPage();
    
    quint32 curInd = 1;
    FormHeader *formHeader;
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournamet;
    QTextBrowser *moves;

    QFormLayout *layout;

};
#endif //GAMESWIDGET_H
