#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../formheader.h"

#include <QWidget>

#include <QLineEdit>
#include <QComboBox>
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
    FormHeader *formHeader;
    QComboBox *id, *result, *opening, *tournamet;
    QLineEdit *format, *timeControl, *date, *white, *black;
    QTextBrowser *moves;

    QFormLayout *layout;

};
#endif //GAMESWIDGET_H
