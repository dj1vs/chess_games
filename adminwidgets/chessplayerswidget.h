#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QLCDNumber>
class ChessplayersWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(FormWidget *parent = nullptr);
    ~ChessplayersWidget();
private:
    void loadPage();
    void setMaxInd() {QSqlQuery query("SELECT MAX(chessplayer_id) FROM chessplayers");
    if (query.next()) {
        curInd = query.value(0).toInt();
    }};
    void saveChanges();
    inline bool checkIfRecordExists();

    QLineEdit *name;
    QLCDNumber *id, *rating, *birthYear;
    QPushButton *save;
};
#endif //CHESSPLAYERSWIDGET_H
